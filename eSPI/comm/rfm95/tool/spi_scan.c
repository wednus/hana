// spi_scan.cpp
//
// Example program showing how to detect multiple module RH_RF69/RH_RF95 on Raspberry Pi
// Requires bcm2835 library to be already installed
// http://www.airspayce.com/mikem/bcm2835/
// Use the Makefile in this directory:
// cd example/raspi/spi_scan
// make
// sudo ./spi_scan
//
// Will check for RFM92/95/96/98 or RFM69/RFM69HCW/RFM69W modules on SPI BUS
// scan with CS = GPIO8
//
// Contributed by Charles-Henri Hallard (hallard.me)
// Modifiled by Sundew Shin for HackIoT Hana

#include <bcm2835.h>
#include <stdio.h>

#define CS 8

uint8_t readRegister(uint8_t addr){
  char spibuf[2];
  spibuf[0] = addr & 0x7F;
  spibuf[1] = 0x00;

  bcm2835_gpio_write(CS,0);
  bcm2835_spi_transfernb( spibuf, spibuf, sizeof(spibuf) );
  bcm2835_gpio_write(CS,1);
  return spibuf[1];
}


bool getModuleName(uint8_t version){
  bool isFound = false;
  printf(" => Found ");
  if(version==00 || version==0xFF) printf("Nothing!\n");
  else if(version == 0x12) printf("SX1276 RF95/96");
  else if(version == 0x22) printf("SX1272 RF92");
  else if(version == 0x24) printf("SX1231 RFM69");
  else printf("Unknown");

  if(version!=00 && version!=0xFF)
    printf(" (V=0x%02X)\n", version);

  if(version == 0x12 or version == 0x22) return true;
  return false;
}


void readModuleVersion(){
  uint8_t version;
  // RFM9x version is reg 0x42
  printf("Checking register(0x42)");
  if(getModuleName(readRegister(0x42)))
    return;
  // RFM69 version is reg 0x10
  printf("Checking register(0x10)");
  getModuleName(readRegister(0x10));
}


int main(int argc, char **argv){
  if(!bcm2835_init()){
    printf("bcm2835_init failed. Are you running as root??\n");
  }else if(!bcm2835_spi_begin()){
    printf("bcm2835_spi_begin failed\n");
  }else{
    // SPI init; we control CS line manually don't assert CEx line!
    bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
    // set CS high to avoid any conflict
    bcm2835_gpio_fsel(CS, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(CS, 1);

    readModuleVersion(); 
    bcm2835_spi_end();
  }
  bcm2835_close();
}
