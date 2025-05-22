#include "Adafruit_NeoPixel.h"

int pix = 144;
const int capteurPin = 0;
int etatCapteur = 2;

Adafruit_NeoPixel strip(pix, 0, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(50);

  pinMode(capteurPin, INPUT_PULLUP);
  Serial.println("Capteur prêt");

  // Couleur de base
  for (int b = 0; b < pix; b++) {
    strip.setPixelColor(b, 32, 86, 190);
  }
  strip.show();

  randomSeed(analogRead(1));
}

void loop() {
  etatCapteur = digitalRead(capteurPin);

  // Si vibration détectée → effet éclair
  if (etatCapteur == LOW) {
    Serial.println("⚡ Vibration détectée : effet éclair");

    strip.setBrightness(255);
    for (int e = 0; e < 6; e++) {
      for (int i = 0; i < pix; i++) {
        strip.setPixelColor(i, 90, 0, 255);
      }
      strip.show();
      delay(40);
      for (int i = 0; i < pix; i++) {
        strip.setPixelColor(i, 180, 80, 255);
      }
      strip.show();
      delay(40);
    }

    // Revenir à la couleur de base
    strip.setBrightness(50);
    for (int b = 0; b < pix; b++) {
      strip.setPixelColor(b, 32, 86, 190);
    }
    strip.show();

    delay(5); // éviter les déclenchements multiples
  } else {
    // Effet de respiration lent et fluide
    for (int b = 50; b <= 255; b += 2) {
      strip.setBrightness(b);
      strip.show();
      delay(20);
      if (digitalRead(capteurPin) == LOW) return;
    }
    for (int b = 255; b >= 50; b -= 2) {
      strip.setBrightness(b);
      strip.show();
      delay(20);
      if (digitalRead(capteurPin) == LOW) return;
    }
  }
}
