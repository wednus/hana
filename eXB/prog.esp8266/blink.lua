-- Blink using timer alarm --
timerId = 0
dly = 1000
-- use D4 (GPIO2)
ledPin = 4
-- set mode to output
gpio.mode(ledPin,gpio.OUTPUT)
ledState = 0
-- timer loop
tmr.alarm( timerId, dly, 1, function()
  ledState = 1 - ledState;
  -- write state to D4
  gpio.write(ledPin, ledState)
  -- write to serial
  print("LED:"..ledState)
end)