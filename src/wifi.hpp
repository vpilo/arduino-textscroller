#pragma once

#include <ESP8266WiFi.h>

#include <list>
#include <stdint.h>
#include <config.h>

class Wifi {
public:
  static const uint16_t LISTEN_PORT = 10666;
  using CommandCallback = std::function< bool(std::list<String>, String&) >;

private:
  // Drawings can be very long.
  static const uint16_t MAX_INPUT_BUFFER = MAX_MESSAGE_LENGTH * 6;

private:
  WiFiServer server { Wifi::LISTEN_PORT };
  WiFiClient client;
  bool hasClient = false;

  CommandCallback callback;

  // Data store for text data
  char inputBuffer[MAX_INPUT_BUFFER];
  uint16_t inputBufferIndex = 0;

  wl_status_t lastStatus = WL_IDLE_STATUS;

public:
  wl_status_t Connect(String ssid, String password);
  void SetCommandCallback(CommandCallback callback);

  bool GetStatus(wl_status_t& status, bool& changed);
  void Loop();

  String GetIp();
};
