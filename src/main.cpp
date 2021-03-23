#include <Arduino.h>
#include <U8x8lib.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const int AirValue = 500;   //you need to replace this value with Value_1
const int WaterValue = 190;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
void setup() {
    Serial.begin(9600); // open serial port, set the baud rate to 9600 bps

    u8x8.begin();
    u8x8.setPowerSave(0);
}
void loop() {
    soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
    Serial.println(soilMoistureValue);
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    if (soilmoisturepercent >= 100)
    {
        Serial.println("100 %");

        u8x8.drawString(0, 0, "100 %");
    }
    else if (soilmoisturepercent <= 0)
    {
        Serial.println("0 %");

        u8x8.drawString(0, 0, "0 %");
    }
    else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
    {
        Serial.print(soilmoisturepercent);
        Serial.println("%");

        u8x8.drawString(0, 0, String(soilmoisturepercent).c_str());
        u8x8.drawString(3, 0, "%");
    }

    delay(5000);
}