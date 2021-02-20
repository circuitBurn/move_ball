#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#include "Commands.h"

#define SERIAL_TX 0
#define SERIAL_RX 1
#define LED_PIN 3
#define LED_COUNT 6
#define BRIGHTNESS 255

// Individual LED addresses
#define LED_HP 0
#define LED_PSI 1
#define FRONT_LOGIC_1 2
#define FRONT_LOGIC_2 3
#define REAR_LOGIC_1 4
#define REAR_LOGIC_2 5

SoftwareSerial Bluetooth(SERIAL_RX, SERIAL_TX);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	// Connect to bluetooth
	Bluetooth.begin(9600);

	// Neopixel setup
	pixels.begin();
	pixels.setBrightness(BRIGHTNESS);
	pixels.show();

	// HP
	pixels.setPixelColor(LED_HP, pixels.Color(0, 0, 255));

	// PSI
	pixels.setPixelColor(LED_PSI, pixels.Color(255, 255, 255));

	// Front Logic
	pixels.setPixelColor(FRONT_LOGIC_1, pixels.Color(255, 255, 255));
	pixels.setPixelColor(FRONT_LOGIC_2, pixels.Color(255, 255, 255));

	// Read Logic
	pixels.setPixelColor(REAR_LOGIC_1, pixels.Color(0, 0, 255));
	pixels.setPixelColor(REAR_LOGIC_2, pixels.Color(0, 0, 255));

	pixels.show();
}

void loop()
{
	// Process bluetooth command
	if (Bluetooth.available() > 0)
	{
		char data = (char)Bluetooth.read();

		switch (data)
		{
		case CMD_BATTERY_LOW:
			enterLowBatteryMode();
			break;
		case CMD_PSI_OFF:
			psiOff();
			break;
		case CMD_PSI_ON:
			psiOn();
			break;
		}
	}
}

/**
 * Turn the front logic lights red to indicate low body battery
 */
void enterLowBatteryMode()
{
	pixels.setPixelColor(FRONT_LOGIC_1, pixels.Color(255, 0, 0));
	pixels.setPixelColor(FRONT_LOGIC_2, pixels.Color(255, 0, 0));
	pixels.show();
}

void psiOn()
{
	pixels.setPixelColor(LED_PSI, 255, 255, 255, BRIGHTNESS);
	pixels.show();
}

void psiOff()
{
	pixels.setPixelColor(LED_PSI, 255, 255, 255, 0);
	pixels.show();
}
