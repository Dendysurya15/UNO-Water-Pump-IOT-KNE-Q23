#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial3(8, 9);
const int relay[6] = {0, 2, 3, 4, 5, 6};
bool testRelay =  false;
bool debugMode = true;

void debug();

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  //test relay
  int i = 1;

  //fixed
  if (testRelay) {
    while (i <= sizeof(relay) ) {
      if (i != 6) {
        if (i == 1) {
          Serial.println("On Genset");
          digitalWrite(relay[i], HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(2000);
        }
        else if (i == 2) {
          Serial.println("Start Genset");
          digitalWrite(relay[i], HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(1000);                    // wait for a second
          digitalWrite(relay[i], LOW);    // turn the LED off by making the voltage LOW
          delay(1000);
        }
        else {
          digitalWrite(relay[i], HIGH);   // turn the LED on (HIGH is the voltage level)
          digitalWrite(relay[i + 1], HIGH); // turn the LED on (HIGH is the voltage level)
          digitalWrite(relay[i + 2], HIGH); // turn the LED on (HIGH is the voltage level)
          if (i == 3) {
            delay(5000);
            Serial.println("Pompa " + String(i - 2) + " mati");
            digitalWrite(relay[i], LOW);    // turn the LED off by making the voltage LOW
            delay(2000);
            digitalWrite(relay[i], HIGH);
            Serial.println("Pompa " + String(i - 2) + " nyala");
          }
          else if (i == 4) {
            Serial.println("Pompa " + String(i - 2) + " mati");
            digitalWrite(relay[i], LOW);    // turn the LED off by making the voltage LOW
            delay(2000);
            digitalWrite(relay[i], HIGH);
            Serial.println("Pompa " + String(i - 2) + " nyala");
          }
          else if (i == 5) {
            Serial.println("Pompa " + String(i - 2) + " mati");
            digitalWrite(relay[i], LOW);    // turn the LED off by making the voltage LOW
            delay(2000);
            digitalWrite(relay[i], HIGH);
            Serial.println("Pompa " + String(i - 2) + " nyala");
          }
        }
        i++;
      } else {
        i = 3;
      }

    }
  }
  String content = "";
  char character;

  while (Serial3.available()) {
    character = Serial3.read();
    content.concat(character);
  }

  if (content != "") {
    int pin = content.toInt();
    Serial.print("Pin " + String(pin));
    if (pin > 0) {
      Serial.println(" nyala");
      digitalWrite(pin, HIGH);
    } else if (pin < 0) {
      Serial.println(" mati");
      digitalWrite(pin * -1, LOW);
    } else {
      Serial.println(" BUILT IN");
    }
  }
}

void debug(String noDebug) {
  if (debugMode) {
    Serial.println("debug " + noDebug);
  }
}