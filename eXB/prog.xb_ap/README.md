
Troubleshoot
=
#### ImportError: cannot import name Serial
- Install python3 by running prep.sh
- Run code with python3

#### ImportError: No module named 'digi'
pip3 install digi-xbee

#### Unsupported operating mode: AT mode
Full message: digi.xbee.exception.InvalidOperatingModeException: Unsupported operating mode: AT mode
This indicates the module is in transparent mode. Change the AP parameter through XCTU to be API enabled [1].