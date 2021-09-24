/* TODO
 * More de-jitter:
 * https://www.arduino.cc/en/Tutorial/Smoothing
 * or Exponential Moving Average:
 * https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/
 *
 * On Linux a shell command could be run to set absolute volume levels instead of trying to figure
 * out increments that may get out of sync:
 * https://www.arduino.cc/en/Tutorial/LibraryExamples/ShellCommands
 */


#include <HID-Project.h>
#include <HID-Settings.h>


int rawValue;
int oldValue;
byte set;
byte oldPercentage;

byte is;
int diff;


void setup() {
  // Serial.begin(9600);
  rawValue = analogRead(A0);
  rawValue = constrain(rawValue, 8, 1015);
  is = map(oldValue, 8, 1008, 0, 100);
}


void loop() {
  // read input twice
  rawValue = analogRead(A0);
  rawValue = analogRead(A0); // double read
  // ignore bad hop-on region of a pot by removing 8 values at both extremes
  rawValue = constrain(rawValue, 0, 1015);
  // add some deadband
  if (rawValue < (oldValue - 4) || rawValue > (oldValue + 4)) {
    oldValue = rawValue;
    // convert to percentage
    set = map(oldValue, 8, 1008, 0, 100);
  }

  diff = set - is;
/*
 * Serial.print("Set: ");
 * Serial.print(set);
 * Serial.print(" Is: ");
 * Serial.print(is);
 * Serial.print(" ");
 * Serial.println(diff);
 */
  if (diff < 0) {
    // Serial.println("DOWN");
    Consumer.write(MEDIA_VOLUME_DOWN);
    is--;
  } else if  (diff > 0) {
    // Serial.println("UP");
    Consumer.write(MEDIA_VOLUME_UP);
    is++;
  }
  delay(10);
}
