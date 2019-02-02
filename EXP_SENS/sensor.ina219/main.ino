#include "U8glib.h"
#include "Wire.h"
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 

float voltage;
float current;
float power;

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 16, "-= uMeter =-");
  u8g.setPrintPos(0, 34); u8g.print("V: ");u8g.print(voltage);u8g.print(" V");
  u8g.setPrintPos(0, 49); u8g.print("A: ");u8g.print(current);u8g.print(" mA");
  u8g.setPrintPos(0, 64); u8g.print("P: ");u8g.print(power);u8g.print(" mW");
}


void setup()   {     
  ina219.begin();
  ina219.setCalibration_16V_400mA();
}


float measure() {
  float shuntV = ina219.getShuntVoltage_mV();
  voltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
  float loadV = voltage + (shuntV / 1000);
  if (current < 0) {
    current = 0.0;
  }
  power = current * loadV;
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