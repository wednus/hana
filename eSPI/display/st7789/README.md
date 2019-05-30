ST7789 Display
=

## Using bcm2835 library
#### Run
    cd bcm2835
    ./lcd_1in3

#### Build
    make

## Using [fbcp-ili9341](https://github.com/juj/fbcp-ili9341) Driver
#### Prep
Specify the display's resolution in the /boot/config.txt and reboot.
<br>e.g. For Hana.eSPI.LCD240x240:

    hdmi_group=2
    hdmi_mode=87
    hdmi_cvt=240 240 60 1 0 0 0
    hdmi_force_hotplug=1

#### Run
    cd fbcp-ili9341
    ./fbcp-ili9341

This command will show the tty1 of the 'host'.<br>
To forward keyboard input to the shell on the display,

    apt-get install -y kbd
    chvt 1
    
Login with docker host's user 'pi' and its password.

#### Build
    apt-get update && apt-get install -y libraspberrypi-dev

    cmake -DST7789VW=ON -DGPIO_TFT_DATA_CONTROL=25 \
      -DUSE_DMA_TRANSFERS=ON -DSPI_BUS_CLOCK_DIVISOR=6 \
      -DSTATISTICS=0

      (optional) -DDISPLAY_CROPPED_INSTEAD_OF_SCALING=ON

    make -j
    
#### Test-1
    apt-get install -y omxplayer
    wget http://adafruit-download.s3.amazonaws.com/bigbuckbunny320p.mp4
    omxplayer bigbuckbunny320p.mp4
    
#### Test-2
    pip install numpy
    cd fbtft
    python fb.py