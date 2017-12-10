#include <utils.hpp>
#include <Arduino.h>

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
