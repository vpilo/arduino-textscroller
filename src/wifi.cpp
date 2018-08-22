#include <wifi.hpp>
#include <logger.hpp>
#include <utils.hpp>
#include <Arduino.h>

wl_status_t Wifi::Init(std::string ssid, std::string password) {
  lg->Print("Connecting to wifi SSID '" + String(ssid.c_str()) + "'");

  wl_status_t status = WiFi.begin(ssid.c_str(), password.c_str());
  if (status != WL_CONNECTED) {
    lg->Print("Connection failed: error " + String(status));
    return status;
  }

  return status;
}

String Wifi::GetIp() {
  return WiFi.localIP().toString();
}

bool Wifi::IsReady() {
  if (WiFi.status() != WL_CONNECTED) {
    if (!loading) {
      loading = true;
    }
    return false;
  } else {
    if (loading) {
      loading = false;
    }
    server.begin();
    return true;
  }
}
    
void Wifi::Loop() {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  if (!client.connected()) {
    client = server.available();
    return;
  }

  if (client.available()) {
    char ch = (char)client.read();

    inputBuffer[inputBufferIndex++] = ch;

    if (ch == '\n' || inputBufferIndex >= MAX_INPUT_BUFFER) {
      if (inputBufferIndex >= MAX_INPUT_BUFFER) {
        lg->Print("WARNING: Input buffer was too long");
      }

      inputBuffer[inputBufferIndex - 1] = '\0';

      message = inputBuffer;
      lg->Print("Received command: <<" + String(message.c_str()) + ">>");

      inputBufferIndex = 0;
    }
  }
}

std::string Wifi::GetMessage() {
  std::string other{message};
  message.clear();
  return other;
}