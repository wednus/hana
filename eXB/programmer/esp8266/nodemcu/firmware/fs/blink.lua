-- Blink using timer alarm --
-- use D4 (GPIO2)
ledPin = 4
-- set mode to output
gpio.mode(ledPin,gpio.OUTPUT)
ledState = 0
-- timer loop
tmr.create():alarm(1000, tmr.ALARM_AUTO, function()
  ledState = 1 - ledState;
  gpio.write(ledPin, ledState)
  print("LED:"..ledState)
end)