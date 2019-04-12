-- source: https://github.com/gfnord/lua_wifimanager

print("\n[Lua WIFI Manager]")

btnPin = 4  -- Button (RST)
ledPin = 2  -- LED (Asoc)

gpio.mode(ledPin,gpio.OUTPUT)
gpio.mode(btnPin,gpio.INT, gpio.PULLUP)
--gpio.write(ledPin,gpio.LOW)

-- define a callback function named "pin_cb", short for "pin callback"
function pin_cb()
    print("Reset button pressed.")
    gpio.write(ledPin,gpio.LOW)
    print("Removing credential file..")
    file.remove("credentials.lc")
    print("Rebooting.. ")
    node.restart()
end

-- register a button event
gpio.trig(btnPin, "down", pin_cb)


-- check if file credentials.lc exists
if file.open("credentials.lc") then
  print("Found existing configuration..")
  print(file.read())
  file.close()
  dofile("credentials.lc")
  -- file exists, running on station mode
  dofile("station_mode.lua")
else
  -- file don't exists, runnning on ap mode
  print("Credentials not found, going into AP mode")
  dofile("ap_mode.lua")
end
