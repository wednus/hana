#include <SPI.h>
#include <Wire.h>
#include "U8glib.h"
#include "DFRobot_BME680_I2C.h"

DFRobot_BME680_I2C bme(0x77);  //0x77 I2C address
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 

float temp;
float pres;
float humi;
float gas;
float alt;

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 16, "");
  u8g.setPrintPos(0, 10); u8g.print("T: ");u8g.print(temp);u8g.print(" C");
  u8g.setPrintPos(0, 23); u8g.print("P: ");u8g.print(pres);u8g.print(" kPa");
  u8g.setPrintPos(0, 36); u8g.print("H: ");u8g.print(humi);u8g.print(" %rh");
  u8g.setPrintPos(0, 49); u8g.print("G: ");u8g.print(gas);u8g.print(" kOhm");
  u8g.setPrintPos(0, 62); u8g.print("A: ");u8g.print(alt);u8g.print(" m");
}


void setup()   {
  uint8_t rslt = 1;
  while(rslt != 0) {
    rslt = bme.begin();
    if(rslt != 0) {
      Serial.println("bme begin failure");
      delay(2000);
    }
  }
}


float measure() {
  bme.startConvert();
  delay(1000);
  bme.update();
  temp = bme.readTemperature() / 100.0;
  pres = bme.readPressure() / 1000.0;
  humi = bme.readHumidity() / 1000.0;
  gas = bme.readGasResistance() / 1000.0;
  alt = bme.readAltitude();
}


void loop() {
  delay(1000);
  measure();
  // picture loop
  u8g.firstPage();
  do{
    draw();
  }while(u8g.nextPage());
  // rebuild the picture after some delay
  delay(500);
}