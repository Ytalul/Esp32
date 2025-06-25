#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ESP32Ping.h>

// --- CONFIGURE AQUI ---
const char* ssid = "note11";     // Coloque o nome da sua rede Wi-Fi
const char* password = "54671234"; // Coloque a senha da sua rede

// Variáveis Globais
AsyncWebServer server(80); // Cria o servidor na porta 80 (padrão HTTP)
IPAddress ipAlvo;          // IP do alvo do ping (será o seu roteador)
float latenciaAtual = 0;   // Armazena a última latência medida
String statusAtual = "Aguardando..."; // Armazena o status do último ping

// HTML da nossa página web
// O %LATENCIA% e %STATUS% serão substituídos pelos valores reais
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Ping Tester</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="5">
  <style>
    body { font-family: Arial, sans-serif; text-align: center; background-color: #282c34; color: white; }
    h1 { color: #61dafb; }
    .card { background-color: #20232a; padding: 20px; border-radius: 10px; display: inline-block; box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2); }
    .latency { font-size: 4em; color: #61dafb; font-weight: bold; }
    .status { font-size: 1.5em; margin-top: 10px; }
  </style>
</head>
<body>
  <h1>Testador de Latência Wi-Fi</h1>
  <div class="card">
    <div class="latency">%LATENCIA% <span style="font-size:0.4em;">ms</span></div>
    <div class="status">Status: %STATUS%</div>
  </div>
  <p style="margin-top: 20px;">Esta página atualiza a cada 5 segundos.</p>
</body>
</html>
)rawliteral";

// Função para substituir os placeholders no HTML
String processador(const String& var){
  if(var == "LATENCIA"){
    return String(latenciaAtual, 0); // Retorna a latência sem casas decimais
  }
  if(var == "STATUS"){
    return statusAtual;
  }
  return String();
}

void setup(){
  Serial.begin(115200); // Inicia a comunicação serial para debug

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");

  // Imprime o endereço IP do ESP32
  Serial.print("Acesse a página em: http://");
  Serial.println(WiFi.localIP());

  // O alvo do nosso ping será o gateway (roteador) da rede
  ipAlvo = WiFi.gatewayIP();
  Serial.print("O alvo do ping é o roteador: ");
  Serial.println(ipAlvo);

  // Configura a rota do servidor web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processador);
  });

  // Inicia o servidor
  server.begin();
}

void loop(){
  // Realiza o ping no alvo a cada 5 segundos
  bool sucesso = Ping.ping(ipAlvo, 1); // Envia 1 pacote de ping

  if(sucesso) {
    latenciaAtual = Ping.averageTime();
    statusAtual = "Sucesso";
    Serial.printf("Ping para %s bem-sucedido! Latência: %.2f ms\n", ipAlvo.toString().c_str(), latenciaAtual);
  } else {
    latenciaAtual = 0;
    statusAtual = "Falha / Sem Resposta";
    Serial.printf("Falha no ping para %s\n", ipAlvo.toString().c_str());
  }

  delay(5000); // Espera 5 segundos antes do próximo teste
}