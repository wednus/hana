ST7789 Display
=

## Using bcm2835 library
#### Run
    cd bcm2835
    ./lcd_1in3

#### Build
    make

## Using fb0-python (experimental)
#### Acknowledgement
Extracted/modifled from [waveshare demo](https://www.waveshare.com/wiki/1.3inch_LCD_HAT) code.

#### Run
    cd fb0-python
    python fb.py


## Using [fbcp-ili9341](https://github.com/juj/fbcp-ili9341) Driver
#### Prep
Specify the display's resolution in the /boot/config.txt and reboot.
<br>e.g. For Hana.eSPI.LCD240x240:

    hdmi_group=2
    hdmi_mode=87
    hdmi_cvt=240 240 60 1 0 0 0
    hdmi_force_hotplug=1

After reboot, the default HDMI output of RPi will be blacked out because 240x240 is not a valid HDMI mode.
Refer: https://www.raspberrypi.org/documentation/configuration/config-txt/video.md
Note: To make LCD a proper framebuffer device, use [fbtft](https://github.com/notro/fbtft) driver instead.

#### Run
    cd fbcp-ili9341
    
No DMA pre-built:

    ./fbcp-ili9341

DMA pre-built:

    ./fbcp-ili9341_dma

#### Build
    cmake -DST7789VW=ON -DGPIO_TFT_DATA_CONTROL=25 \
      -DUSE_DMA_TRANSFERS=ON -DSPI_BUS_CLOCK_DIVISOR=6 \
      -DSTATISTICS=0

    make -j
    
    
#### Test
    apt-get install fbset
    fbset -i

#### Play Sample
    apt-get install -y omxplayer
    wget http://adafruit-download.s3.amazonaws.com/bigbuckbunny320p.mp4
    omxplayer bigbuckbunny320p.mp4
