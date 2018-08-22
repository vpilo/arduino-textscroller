#pragma once

#include <ESP8266WiFi.h>

#include <stdint.h>
#include <string>

class Wifi {
private:
  static const uint16_t LISTEN_PORT = 10666;
  static const uint8_t MAX_INPUT_BUFFER = 255;
  
private:
  WiFiServer server {Wifi::LISTEN_PORT};
  WiFiClient client;

  // Data store for text data
  char inputBuffer[MAX_INPUT_BUFFER];
  int inputBufferIndex = 0;
  std::string message;
  
  bool loading = true;

public:
  wl_status_t Init(std::string ssid, std::string password);
  bool IsReady();
  void Loop();
  std::string GetMessage();

  String GetIp();
};
