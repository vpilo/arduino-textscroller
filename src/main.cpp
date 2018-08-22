#include <Arduino.h>
#include <screen.hpp>
#include <text.hpp>
#include <wifi.hpp>
#include <logger.hpp>
#include <utils.hpp>

#include <textscroller.hpp>

Screen *screen;
Text *text;
Logger *lg = Logger::Instance();

TextScroller scroll;
Wifi wifi;

String currentMessage;

void setup() {
  screen = new Screen();
  text = new Text();
  Utils::SetRandomSeed();

  wifi.Init(WIFI_SSID, WIFI_PASSWORD);

  scroll.SetText("This looks like a message!");
}

void loop() {
  if (!wifi.IsReady()) {
    scroll.SetText("**Getting wifi**");
    scroll.ScrollTextRainbow(TextScroller::Left);
  } else {
    std::string newMessage = wifi.GetMessage();
    if (currentMessage.length() == 0) {
      scroll.SetText("Send me a message @ " + wifi.GetIp());
    } else {
      scroll.SetText(currentMessage.c_str());
    }
  }

  scroll.Scroll(true /* rainbow */);

  wifi.Loop();
}
