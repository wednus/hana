HackIoT Hana
=
## Firmware Downloader/Uploader
Simple but useful scripts download and upload AVR's flash memory contents.

The downloaded image ('firmware.bin') includes the Arduino bootloader as well by default. It means it is safe to be uploaded to the HackIoT Hana's and any other Arduino w/ ATmega328p.

#### Downloading
    ./download.sh
    
#### Uploading
    ./upload.sh [filename]
