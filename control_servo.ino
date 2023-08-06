#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

String s;
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50
// our servo # counter
uint8_t servonum = 0;
String result = "";
void setup() {
  Serial.begin(115200);
  pwm.setPWM(0, 0, pulseWidth(0));
  pwm.setPWM(1, 0, pulseWidth(0));
  pwm.setPWM(2, 0, pulseWidth(0));
  pwm.setPWM(3, 0, pulseWidth(0));
  //Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
}

int a;
void loop() {
  while (Serial.available() == 0) {
    pinMode(13, OUTPUT);
  }
  while (true) {

    s = Serial.readStringUntil('\r');
    //a=Serial.parseInt();
    //Serial.println(s);
    if (s[0] == '1') {
      digitalWrite(13, HIGH);
      pwm.setPWM(0, 0, pulseWidth(80));
    }
    if (s[0] == '0') {
      digitalWrite(13, LOW);
      pwm.setPWM(0, 0, pulseWidth(0));
    }
    if (s[1] == '1') {
      pwm.setPWM(1, 0, pulseWidth(80));
    }
    if (s[1] == '0') {
      pwm.setPWM(1, 0, pulseWidth(0));
    }
    if (s[2] == '1') {
      pwm.setPWM(2, 0, pulseWidth(80));
    }
    if (s[2] == '0') {
      pwm.setPWM(2, 0, pulseWidth(0));
    }
    if (s[3] == '1') {
      pwm.setPWM(3, 0, pulseWidth(80));
    }
    if (s[3] == '0') {
      pwm.setPWM(3, 0, pulseWidth(0));
    }
  }

  
}

int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}