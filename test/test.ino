/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
int pin=2; //pin 2 EQUAL TO LED_BUILD_IN
int relay1 = 16;
int relay2 = 15
void setup() {
  pinMode(pin, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pin, 0); // 0 --> make LED open
  digitalWrite(pin2, 0);
  delay(1000);                      // Wait for a second
  digitalWrite(pin, 1);  // Turn the LED off by making the voltage HIGH
  digitalWrite(pin2, 1);
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
