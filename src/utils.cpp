#include <utils.hpp>

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
