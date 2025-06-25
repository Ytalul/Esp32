# 📶 ESP32 Ping Tester

Este projeto implementa um **testador de latência Wi-Fi** utilizando um **ESP32**. Ele mede periodicamente a latência (ping) entre o ESP32 e o roteador (gateway) da rede Wi-Fi conectada, exibindo os resultados em uma interface web acessível via navegador.

---

## 🔧 Funcionalidades

- Conexão automática à rede Wi-Fi.
- Ping periódico (a cada 5 segundos) para o roteador.
- Exibição em tempo real da **latência em milissegundos** e do **status** do ping.
- Interface web leve e responsiva.
- Página HTML recarrega automaticamente a cada 5 segundos.

---

## 📷 Interface Web

A interface mostra:

- **Latência atual** (em ms)
- **Status** da última tentativa de ping (Sucesso ou Falha)

---

## 🧰 Tecnologias Utilizadas

- [ESP32](https://www.espressif.com/en/products/socs/esp32)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ESP32Ping](https://github.com/marian-craciunescu/ESP32Ping)
- C++ com PlatformIO ou Arduino IDE

---

## 🛠️ Instalação e Uso

1. **Clone o projeto** ou copie o código para sua IDE.
2. Instale as bibliotecas necessárias:
   - `ESPAsyncWebServer`
   - `AsyncTCP`
   - `ESP32Ping`
3. Altere os dados da rede Wi-Fi no topo do código:

   ```cpp
   const char* ssid = "SUA_REDE";
   const char* password = "SUA_SENHA";
   ```

4. **Faça upload** do código para o ESP32.
5. Abra o **Monitor Serial** (baud rate 115200).
6. Acesse o IP mostrado no terminal via navegador (ex: `http://192.168.0.101`).

---

## 💡 Exemplo de Uso

Imagine que você está testando a qualidade da conexão entre o ESP32 e o roteador local. Este projeto mostra se a rede está instável com base na latência e falhas de resposta. Ideal para testes de conectividade em automações residenciais ou robótica.

---

## 📁 Estrutura do Projeto

```plaintext
ESP32_Ping_Tester/
├── ESP32Ping.h
├── WiFi.h
├── ESPAsyncWebServer.h
├── AsyncTCP.h
├── main.ino
```

---

## 📜 Licença

Este projeto é livre para uso educacional e pessoal. Sinta-se à vontade para modificá-lo e melhorá-lo!