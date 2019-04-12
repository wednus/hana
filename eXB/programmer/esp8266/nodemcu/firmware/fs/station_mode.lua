  wifi.setmode(wifi.STATION)
  print("ESP8266 mode now is: " .. wifi.getmode())
  -- configure the module so it can connect to the network using the received SSID and password
  config_wifi={}
  config_wifi.ssid=SSID
  config_wifi.pwd=PASS
  wifi.sta.config(config_wifi)
  wifi.sta.connect()
  -- Finite loop to check if wifi is connected
  myTimer = tmr.create()
  myTimer:alarm(5000,1,function()
    -- Connect wifi
    if wifi.sta.getip() == nil then
      print('IP unavaiable, waiting...')
    else
      myTimer:stop(2)
      print('The module MAC address is: ' .. wifi.ap.getmac())
      print('Config done. ('..wifi.sta.getip()..')')
    end
  end)
