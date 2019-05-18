STM32F1x Programming
=
## Programming
Run openocd

    ./openocd

Access openocd using telnet

    telnet localhost 4444

From telnet CLI, run:

    stm32f1x mass_erase 0
    flash erase_check 0
    flash write_bank 0 blink/blink.bin 0


## Troubleshoot
#### 'reset halt' doesn't work: Force reset from openocd
- full msg: Could not find MEM-AP to control the core
- Press and hold reset button

      reset halt

#### programming failure:
- full msg: embedded:startup.tcl:479: Error: ** Programming Failed **
- fix: stop openocd server and restart

#### Verify failed
- full: More than 128 errors, the rest are not printed. embedded:startup.tcl:479: Error: ** Verify Failed **
- fix: use
        
      flash write_bank 0 blink/blink.bin 0