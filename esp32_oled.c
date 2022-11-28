#include "Wire.h"
#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,&Wire);
DHT dht(32, DHT11);
void setup() {
  Wire.begin();
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if(isnan(h) || isnan(t) || isnan(f) ) {
    display.println("Failed to read from DHT sensor!");
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Humidity:");
  display.print(h);
  display.println("%");
  display.print("TEMP:");
  display.print(t);
  display.print("C | ");
  display.print(f);
  display.print("F");
  display.display();
}