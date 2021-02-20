#include "Arduino.h"
#include "Sound.h"
#include "Configuration.h"
#include "DFRobotDFPlayerMini.h"

Sound::Sound()
{
}

void Sound::setup()
{
    Serial1.begin(9600);

    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(Serial1))
    { //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while (true)
        {
            delay(0); // Code to compatible with ESP8266 watch dog.
        }
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.volume(10); //Set volume value. From 0 to 30
    myDFPlayer.play(1);    //Play the first mp3
}

void Sound::process(uint16_t *channels)
{
    uint16_t rawVol = channels[THROTTLE];
    long vol = map(rawVol, 210, 1811, 0, 30);
    Serial.print("Volume: ");
    Serial.println(vol);
}

