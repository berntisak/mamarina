// the setup function runs once when you press reset or power the board

int startTime;
int led_on;
int blink_time;
String buffer;
bool blink_on;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(115200);
  startTime = millis();
  blink_time = 1000;
  blink_on = true;
}

int buttonState = 0;
// the loop function runs over and over again forever
void loop() {
  int currentMillis = millis();
  buttonState = digitalRead(2);
  //Serial.println(buttonState);
  if (buttonState == HIGH ) {
    blink_on = true;
  }
  else if (buttonState == LOW) {
    blink_on = false;
  }
  if (blink_on) {
    if ((currentMillis - startTime) >= blink_time) {
      if (led_on == 0) {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        led_on = 1;   
      }
      else {
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        led_on = 0;      
      }
      startTime = currentMillis;
    }
  }
  if (Serial.available()) {
    char inByte = Serial.read();
    if (inByte != '\n') {
      buffer += inByte;
    }
    else {
      blink_time = buffer.toInt();
      buffer = "";
      Serial.println(blink_time);
    }
  }
}
