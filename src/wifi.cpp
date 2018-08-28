#include <wifi.hpp>
#include <logger.hpp>
#include <utils.hpp>
#include <Arduino.h>


wl_status_t Wifi::Connect(String ssid, String password) {
  lg->Print("Connecting to wifi SSID '" + ssid + "'");

  wl_status_t status = WiFi.begin(ssid.c_str(), password.c_str());

  return status;
}

String Wifi::GetIp() {
  return WiFi.localIP().toString();
}

bool Wifi::GetStatus(wl_status_t &status, bool &changed) {
  status = WiFi.status();
  changed = (status != lastStatus);
  lastStatus = status;

  bool result = status == WL_CONNECTED;
  if (changed) {
    if (result) {
      server.begin();
    } else {
      server.stop();
    }
  }

  return result;
}

void Wifi::SetCommandCallback(CommandCallback callback) {
  this->callback = callback;
}

void Wifi::Loop() {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  if (!client.connected()) {
    if (hasClient) {
      hasClient = false;
      if (callback) {
        String args;
        callback(String("BYE"), args);
      }
    }
    client = server.available();
    return;
  }

  hasClient = true;

  while (client.available()) {
    char ch = (char)client.read();

    inputBuffer[inputBufferIndex++] = ch;

    if (ch == '\n' || ch == '\0' || inputBufferIndex >= MAX_INPUT_BUFFER) {
      if (inputBufferIndex >= MAX_INPUT_BUFFER) {
        lg->Print("WARNING: Input buffer was too long, truncated to " + String(MAX_INPUT_BUFFER));
      }

      inputBuffer[inputBufferIndex - 1] = '\0';

      String command = { inputBuffer };

      lg->Print("Client " + client.remoteIP().toString() + " sent command: " + command);

      if (callback) {
        String answer;
        bool ok = callback(command, answer);
        if (!ok) {
          lg->Print("> Error: " + answer);
          client.print(answer + '\n');
          client.stop();
        } else {
          client.print("OK\n");
        }
      }

      memset(inputBuffer, '\0', MAX_INPUT_BUFFER);
      inputBufferIndex = 0;
      break;
    }
  }
}
