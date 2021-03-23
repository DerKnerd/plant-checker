#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ 16);

const int AirValue = 500;
const int WaterValue = 190;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

void setup() {
    Serial.begin(9600);

    u8g2.begin();
    u8g2.setPowerSave(0);
}

void loop() {
    soilMoistureValue = analogRead(A0);
    Serial.println(soilMoistureValue);
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    u8g2.setFont(u8g2_font_logisoso32_tf);
    if (soilmoisturepercent >= 100) {
        Serial.println("100 %");

        u8g2.drawUTF8(0, 0, "100 %");
    } else if (soilmoisturepercent <= 0) {
        Serial.println("0 %");

        u8g2.drawUTF8(0, 0, "0 %");
    } else if (soilmoisturepercent > 0 && soilmoisturepercent < 100) {
        Serial.print(soilmoisturepercent);
        Serial.println("%");

        u8g2.drawUTF8(0, 0, String(soilmoisturepercent).c_str());
        u8g2.drawUTF8(3, 0, "%");
    }

    delay(5000);
}