/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
int pin=2; //pin 2 EQUAL TO LED_BUILD_IN
int pin2 = 16;
void setup() {
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin, LOW); // 0==LOW --> make LED open
  digitalWrite(pin2, LOW);
  Serial.println("Test Start");
}

// the loop function runs over and over again forever
void loop() {
  String s = "";
  while (Serial.available()) {
    char c = Serial.read();
    // println()之後會接上一個回車('\r')及換行
    if(c!='\n' and c!='\r'){
      //Serial.println(c,DEC);
      s += c;
    }
    delay(10);    // 沒有延遲的話 UART 串口速度會跟不上Arduino的速度，會導致資料不完整
  }
  if(s!=""){
    if (s=="close") {
      digitalWrite(pin, 1);
      digitalWrite(pin2, 1);
    }else if(s=="open"){
      digitalWrite(pin, 0);
      digitalWrite(pin2, 0);
    }else{
      Serial.print("repeat: ");
      Serial.println(s);
    }
  }
  /* very slow!!!
  while (Serial.available()) {
    Serial.println(Serial.readString());
  }
 */
  /*
  digitalWrite(pin, 0);
  digitalWrite(pin2, 0);
  delay(1000);
  digitalWrite(pin, 1);
  digitalWrite(pin2, 1);
  delay(2000);        
  */              
}
