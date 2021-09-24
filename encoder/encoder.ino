#include <Encoder.h>
#include <HID-Project.h>
#include <HID-Settings.h>

/* Pins:
 * CLK - 6
 * DT  - 5
 * SW  - 12
 * +   - VCC
 * GND - GND
 */


Encoder myEnc(5,6);
const int pinButton = 12;
boolean muted = 0;
long set = 0;
int is = 0;
int diff = 0;


void setup() {
  // Serial.begin(9600);
  pinMode(pinButton, INPUT_PULLUP);
  Consumer.begin();
  delay(1000);
}


void loop() {
  set = myEnc.read();
  set = set / 4;
  diff = set - is;
  if (diff != 0) {
    // Serial.println(set);
    noInterrupts();
    if (diff < 0) {
      Consumer.write(MEDIA_VOLUME_DOWN);
      is--;
    } else if (diff > 0) {
      Consumer.write(MEDIA_VOLUME_UP);
      is++;
    }
    interrupts();
    delay(10);
  }
  if (!digitalRead(pinButton)) {
    Consumer.write(MEDIA_VOLUME_MUTE);
    muted = !muted;
    delay(300);
  }
}
