#include "U8glib.h"
#include "DHT.h"
DHT dht(A0, DHT22);  // AM2302
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 

float hum;
float temp;

void draw(void) {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 16, "-= uWeather =-");
  u8g.setPrintPos(0, 42); u8g.print("Temp: ");u8g.print(temp);u8g.print(" C");
  u8g.setPrintPos(0, 64); u8g.print("Humi: ");u8g.print(hum);u8g.print(" %");
}

void setup(void) {
  dht.begin();
}

void loop(void) {
  delay(1000);
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  
  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  // rebuild the picture after some delay
  delay(500);
}
