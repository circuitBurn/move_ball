#include "Arduino.h"
#include "SBUS.h"
#include "libs/Configuration.h"
#include "libs/Sound.h"

// SBUS
SBUS x8r(Serial2);
uint16_t channels[16];
bool failSafe;
bool lostFrame;

Sound sound;

void setup()
{
    Serial.begin(115200);

    x8r.begin();

    sound.setup();
}

void loop()
{
    // look for a good SBUS packet from the receiver
    if (x8r.read(&channels[0], &failSafe, &lostFrame))
    {
        sound.process(channels);

        Serial.print(channels[0]);
        Serial.print("\t");
        Serial.print(channels[1]);
        Serial.print("\t");
        Serial.print(channels[THROTTLE]);
        Serial.print("\t");
        Serial.print(channels[3]);
        Serial.print("\t");
        Serial.println(channels[VOLUME]);
    }
}
