#include <Pincode.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#define OLED_DC     5
#define OLED_CS     2
#define OLED_RESET  15

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
Encoder myEnc(20, 21);

byte pin[] = {1,2,3,4};

void setup() {

	display.begin(SSD1306_SWITCHCAPVCC);

	//pinMode(BUTTON, INPUT_PULLUP);           // set pin to input

	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.setTextWrap(false);
	display.setFont(&FreeSans24pt7b);
}

void loop() {

	boolean ok = true;

	Pincode pincode(&display, &myEnc, 4);
	pincode.setRandomSeed(analogRead(A0));
	pincode.setDialSpeed(10);

	byte inputPin[4];

	pincode.reqPin(inputPin);
	
	for (int i=0; i<4; i++) {
		if(inputPin[i] != pin[i]) {
			ok = false;
			break;
		}
	}

	display.clearDisplay();
	display.setCursor(0, 40);

	if (ok) {
		display.print("OK");
	} else {
		display.print("NO");
	}
	display.display();

	delay(1000);
}