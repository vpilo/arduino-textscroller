#include <utils.hpp>
#include <logger.hpp>

uint32_t Utils::lastFrame = millis();
uint32_t Utils::frames = 0;

void Utils::SetRandomSeed() {
    // random works best with a seed that can use 31 bits
    // analogRead on a unconnected pin tends toward less than four bits
    uint32_t seed = analogRead(0);
    delay(1);

    for (int shifts = 3; shifts < 31; shifts += 3) {
        seed ^= analogRead(0) << shifts;
        delay(1);
    }

    // lg->Print("New random seed: " + String(seed));
    randomSeed(seed);
}

bool Utils::Tokenize(const String line, std::list<String>& args) {
  int begin = 0;
  int end;
  int length = line.length();

  if (length < 1) {
    return false;
  }

  while ((end = line.indexOf(' ', begin)) != -1) {
    args.push_back(line.substring(begin, end));
    //lg->Print("Token " + String(begin) + "-" + String(end) + ": " + args.back());
    begin = end + 1;
  }
  args.push_back(line.substring(begin, length));
  //lg->Print("Token " + String(begin) + "-end: " + args.back());

  return true;
}

void Utils::LogFPS() {
  uint32_t now = millis();
  uint32_t diff = now - lastFrame;
  frames++;

  if (diff > 1000) {
    lg->Print("Frame time: " + String(1000.0/(double)frames, 4));
    frames = 0;
    lastFrame = now;
  }
}

uint8_t Utils::GetHexDigit(const char* ch) {
  uint8_t it = 2;
  uint8_t res = 0;

  while(it-- > 0) {
    char cur = *ch - '0';
    if (cur > 9) {
      cur -= 7;
    }
    if (cur > 15) {
      cur -= 32;
    }
    if (cur < 0 || cur > 15) {
      lg->Print("Illegal hex char " + String(cur, DEC) + " in input! (char " + String(*ch, DEC)+ ")");
      return 0;
    }
    res += cur << (it*4);
    ch++;
  }
  return res;
}
