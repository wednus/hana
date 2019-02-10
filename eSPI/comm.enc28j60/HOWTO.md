No additional package install required.

[Step 1]
Open /boot/config.txt and add the following two lines:
dtparam=spi=on
dtoverlay=enc28j60

[Step 2]
Reboot. ('sudo reboot')
Try 'ifconfig' and confirm 'eth0' info
That's it.