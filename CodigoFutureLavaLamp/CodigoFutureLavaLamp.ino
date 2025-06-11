#include <Adafruit_NeoPixel.h>

#define echoPin 7
#define trigPin 8

#define stripPIN 6
#define numPixels 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, stripPIN, NEO_GRB + NEO_KHZ800);

int hue = 0;  //para o color cycle

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  strip.show();
  strip.begin();
}


void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  distance = constrain(distance, 25, 200);
  int activeLEDs = map(distance, 200, 25, 0, numPixels);
  int mixAmount = map(distance, 200, 25, 0, 255);  // 0 = base, 255 = complement

  hue = (hue + 2) % 360;
  int rBase, gBase, bBase;
  HSVtoRGB(hue, 255, 255, rBase, gBase, bBase);

  int compHue = (hue + 180) % 360;
  int rComp, gComp, bComp;
  HSVtoRGB(compHue, 255, 255, rComp, gComp, bComp);

  ledColor(activeLEDs, mixAmount, rBase, gBase, bBase, rComp, gComp, bComp);
  delay(50);
}

void ledColor(int activeLEDs, int mixAmount,
              int rBase, int gBase, int bBase,
              int rComp, int gComp, int bComp) {
  for (int i = 0; i < numPixels; i++) {
    int rMix, gMix, bMix;
    rMix = ((255 - mixAmount) * rBase + mixAmount * rComp) / 255;
    gMix = ((255 - mixAmount) * gBase + mixAmount * gComp) / 255;
    bMix = ((255 - mixAmount) * bBase + mixAmount * bComp) / 255;

    if (i < activeLEDs) {
      strip.setPixelColor(i, strip.Color(rMix, gMix, bMix));
    } else {
      strip.setPixelColor(i, strip.Color(rBase, gBase, bBase));
    }
  }
  strip.show();
}


//tbh em grande parte, magia de HSV
void HSVtoRGB(int hue, int saturation, int value, int &r, int &g, int &b) {
  //ok dividir o hue por 60 da bem jeito para serem 6 partes do hue
  float hueSegment = hue / 60.0;
  int i = int(hueSegment);
  float f = hueSegment - i;
  float p = value * (1 - saturation / 255.0);
  float q = value * (1 - f * saturation / 255.0);
  float t = value * (1 - (1 - f) * saturation / 255.0);

  switch (i % 6) {
    case 0:
      r = value;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = value;
      b = p;
      break;
    case 2:
      r = p;
      g = value;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = value;
      break;
    case 4:
      r = t;
      g = p;
      b = value;
      break;
    case 5:
      r = value;
      g = p;
      b = q;
      break;
  }
}
