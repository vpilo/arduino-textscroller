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

bool draw = false;
bool rainbow = true;

bool ParseCommand(const String commandLine, String& answer) {
  std::list<String> args;

  if (!Utils::Tokenize(commandLine, args) || args.size() < 1) {
    answer = "No command given.";
    return false;
  }

  String cmd = args.front();
  args.pop_front();

  if (cmd == "TEXT") {
    String msg;
    while (!args.empty()) {
      if (msg.length() == 0) {
        msg = args.front();
      } else {
        msg += " " + args.front();
      }
      args.pop_front();
    }
    msg.trim();

    if (msg.length() < 1) {
      answer = "TEXT needs a text, dumbass.";
      return false;
    } else if (text->StringLength(msg) > MAX_MESSAGE_LENGTH) {
      answer = "Your message is too long.";
      return false;
    }
    draw = false;
    scroll.SetText(msg);
  } else if (cmd == "SPEED") {
    if (args.size() < 1) {
      answer = "SPEED needs a range between 1 (fast) and 10 (slow).";
      return false;
    }
    scroll.SetSpeed(args.front().toInt());
  } else if (cmd == "COLOR") {
    if (args.size() != 3) {
      answer = "COLOR needs three 0-255 values for R, G, B channels.";
      return false;
    }
    uint8_t R = args.front().toInt();
    args.pop_front();
    uint8_t G = args.front().toInt();
    args.pop_front();
    uint8_t B = args.front().toInt();
    lg->Print("Color channels: " + String(R) + ", " + String(G) + ", " + String(B));
    scroll.SetScrollColor(RgbColor(R, G, B));
    rainbow = false;
  } else if (cmd == "RAINBOW") {
    rainbow = true;
  } else if (cmd == "PIXELS") {
    if (args.size() != 1) {
      answer = "PIXELS needs one argument.";
      return false;
    }

    const String &hex = args.front();
    const char *rawHex = hex.c_str();
    uint16_t pixelCount = hex.length() / 6;

    if (pixelCount != Screen::PIXELS) {
      answer = "PIXELS needs a single hex-encoded string containing 24bpp RGB pixel data for "
        + String(SCREEN_WIDTH) + " by " + String(SCREEN_HEIGHT) + " pixels (expected "
        + String(Screen::PIXELS) + ", got " + String(pixelCount) + ").";
      return false;
    }

    uint8_t idx = 0;
    uint32_t pixelBuffer[Screen::PIXELS];
    for (uint16_t pixel = 0 ; pixel < pixelCount ; ++pixel, ++idx, rawHex += 6) {
      pixelBuffer[idx] = Utils::GetHexDigit(rawHex) << 16 | Utils::GetHexDigit(rawHex+2) << 8 |  Utils::GetHexDigit(rawHex+4);
    }

    draw = true;
    return screen->SetAllPixels(pixelBuffer, pixelCount);
  } else if (cmd == "BYE") {
    if (draw) {
		  scroll.SetText("Send messages @ " + wifi.GetIp());
      draw = false;
    }
  } else {
    answer = cmd + " is not a valid command.";
    return false;
  }

  return true;
}

void setup() {
  screen = new Screen();
  text = new Text();
  Utils::SetRandomSeed();

	scroll.SetSpeed(1);

  wifi.Connect(WIFI_SSID, WIFI_PASSWORD);
  wifi.SetCommandCallback(ParseCommand);
}

void loop() {
	bool wifiStateChanged;
	wl_status_t currentStatus;
	bool online = wifi.GetStatus(currentStatus, wifiStateChanged);

	if (wifiStateChanged) {
		if (!online) {
			scroll.SetText("**Getting wifi**");
		} else {
			scroll.SetText("Send messages @ " + wifi.GetIp());
		}
	}

  if (!draw) {
    scroll.Scroll(rainbow);
  }
  wifi.Loop();
  Utils::LogFPS();
}
