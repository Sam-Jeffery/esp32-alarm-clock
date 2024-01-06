#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DS3231.h>

DS3231 rtc;
Adafruit_SSD1306 display(128, 32, &Wire, (uint8_t)-1);

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
}

bool h12Flag = false;
bool PMFlag = false;

void loop()
{
  Serial.print(rtc.getHour(h12Flag, PMFlag));
  Serial.print(":");
  Serial.print(rtc.getMinute());
  Serial.print(":");
  Serial.println(rtc.getSecond());

  uint8_t hour = rtc.getHour(h12Flag, PMFlag);
  uint8_t minute = rtc.getMinute();
  uint8_t second = rtc.getSecond();

  String constructedTime = String(hour) + ":" + String(minute) + ":" + String(second);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.write(constructedTime.c_str());
  display.display();

  delay(500);
}