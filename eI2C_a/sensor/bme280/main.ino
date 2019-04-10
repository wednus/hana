#include <Wire.h>
#include "U8glib.h"
#include "Seeed_BME280.h"

BME280 bme;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 

float temp;
float pres;
float humi;
float alt;

void draw(void){
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 10, "-= BME280 =-");
  u8g.setPrintPos(0, 23); u8g.print("T: ");u8g.print(temp);u8g.print(" C");
  u8g.setPrintPos(0, 36); u8g.print("P: ");u8g.print(pres);u8g.print(" kPa");
  u8g.setPrintPos(0, 49); u8g.print("H: ");u8g.print(humi);u8g.print(" %");
  u8g.setPrintPos(0, 62); u8g.print("A: ");u8g.print(alt);u8g.print(" m");
}


void setup(){
  
  if (!bme.init()) { 
    Serial.println("Could not find a valid BME280 sensor, check wiring!"); 
    while (1); 
  } 
}


float measure(){
  temp = bme.getTemperature();
  pres = bme.getPressure() / 1000.0;
  humi = bme.calcAltitude(pres) / 1000.0;
  alt = bme.getHumidity();
}


void loop(){
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