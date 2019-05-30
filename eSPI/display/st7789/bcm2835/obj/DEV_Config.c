/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"

/******************************************************************************
function:	Initialization pin
parameter:
Info:
******************************************************************************/
static void DEV_GPIOConfig(void)
{
	bcm2835_gpio_fsel(LCD_RST,       BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_DC,        BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LCD_CS,        BCM2835_GPIO_FSEL_OUTP);
	
	bcm2835_gpio_fsel(KEY_UP_PIN,    BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY_DOWN_PIN,  BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY_LEFT_PIN,  BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY_RIGHT_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY_PRESS_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY1_PIN,      BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY2_PIN,      BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(KEY3_PIN,      BCM2835_GPIO_FSEL_INPT);
	
	bcm2835_gpio_set_pud(KEY_UP_PIN,    BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY_DOWN_PIN,  BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY_LEFT_PIN,  BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY_RIGHT_PIN, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY_PRESS_PIN, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY1_PIN,      BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY2_PIN,      BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(KEY3_PIN,      BCM2835_GPIO_PUD_UP);
}

/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{
    if(!bcm2835_init()) {
        DEBUG("bcm2835 init failed  !!! \r\n");
        return 1;
    } else {
        DEBUG("bcm2835 init success !!! \r\n");
    }
	
	DEV_GPIOConfig();

	DEBUG("Using SPI communication...\r\n");
    bcm2835_spi_begin(); 										 //Start spi interface, set spi pin for the reuse function
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //High first transmission
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //spi mode 1
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8);   //Frequency
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //set CE0
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //enable cs0

    return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{
    bcm2835_spi_end();
    bcm2835_close();
}
