-- put module in AP mode
wifi.setmode(wifi.SOFTAP)
print("ESP8266 mode is: " .. wifi.getmode())

-- Set the SSID of the module in AP mode and access password
cfg={}
cfg.ssid="HackIoT_" .. string.sub(node.chipid(), -3)
cfg.pwd="hanapass"
wifi.sta.sethostname("HackIoT")
print("Chip ID: " .. node.chipid())
print("ESP8266 SSID is: " .. cfg.ssid .. " and PASSWORD is: " .. cfg.pwd)

-- Now you should see an SSID wireless router named ESP_STATION when you scan 
--   for available WIFI networks
-- Lets connect to the module from a computer of mobile device. So, 
--   find the SSID and connect using the password selected
wifi.ap.config(cfg)
ap_mac = wifi.ap.getmac()
print("AP MAC: " .. ap_mac)

-- create a server on port 80 and wait for a connection, when a connection 
--   is coming in function c will be executed
sv = net.createServer(net.TCP, 30) -- 30s timeout

function receiver(sck, data)
  -- wait until SSID comes back and parse the SSID and the password
  print(string.match(data,"GET"))
  ssid_start,ssid_end=string.find(data,"SSID=")
  if ssid_start and ssid_end then
    amper1_start, amper1_end =string.find(data,"&", ssid_end+1)
    if amper1_start and amper1_end then
      http_start, http_end =string.find(data,"HTTP/1.1", ssid_end+1)
      if http_start and http_end then
        ssid=string.sub(data,ssid_end+1, amper1_start-1)
        password=string.sub(data,amper1_end+10, http_start-2)
        print("ESP8266 connecting to SSID: " .. ssid .. " with PASSWORD: " .. password)
        if ssid and password then
          -- close the server and set the module to STATION mode
          sv:close()
          wifi.setmode(wifi.STATION)
          print("ESP8266 mode now is: " .. wifi.getmode())
          -- configure the module wso it can connect to the network using the received SSID and password
          config_wifi={}
          config_wifi.ssid=ssid
          config_wifi.pwd=password
          wifi.sta.config(config_wifi)
          wifi.sta.connect()
          print("Setting up ESP8266 for station mode... Please wait.")
          -- Loop to check if wifi is connected
          myTimer = tmr.create()
          myTimer:alarm(5000,1,function()
            -- Connect wifi
            if wifi.sta.getip() == nil then
              print('IP unavaiable, waiting...')
            else
              myTimer:stop(2)
              -- Save wifi configuration on file
              file.open("credentials.lua","w+")
              temp = "SSID = \""..ssid.."\""
              file.writeline(temp)
              temp = "PASS = \""..password.."\""
              file.writeline(temp)
              file.flush()
              temp = nil
              file.close()
              node.compile("credentials.lua")
              file.remove("credentials.lua")
              print('The module MAC address is: ' .. wifi.ap.getmac())
              print('Config done. ('..wifi.sta.getip()..')')
              -- led indication
              gpio.write(ledPin, gpio.HIGH)
            end
          end)
          
        end
      end
    end
  end
  
  -- this is the webpage form presented to be configured
  local title = "HackIoT"
  local subtitle = "Configure Wifi</h2><p>Use the following form to connect to a Wifi network"

  local response = {"HTTP/1.0 200 OK\r\nServer: NodeMCU on ESP8266\r\nContent-Type: text/html\r\n\r\n"}
  response[#response + 1] = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\"><head>" 
  response[#response + 1] = "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"><title>" .. title .. "</title></head><body><div><h1><a>" .. title .. "</a></h1>" 
  response[#response + 1] = "<form method=\"get\" action=\"/?SSID=\"><div>"
  response[#response + 1] = "<h2>" .. subtitle .. "</p></div>"
  response[#response + 1] = "<ul ><li><label> SSID </label><div><input name=\"SSID\" type=\"text\" maxlength=\"255\" value=\"\"/>" 
  response[#response + 1] = "</div> </li><li><label> Password </label><div><input name=\"PASSWORD\" type=\"text\" maxlength=\"255\" value=\"\"/> </div> </li><input type=\"submit\" value=\"Save\" /></ul></form>"
  response[#response + 1] = "<div>Powered by <a href=\"https://flat.wednus.com\">HackIoT @ 2019</a></div></div></body></html>"
  response[#response + 1] =  "The module MAC address is: " .. ap_mac


  -- sends and removes the first element from the 'response' table
  local function send(localSocket)
    if #response > 0 then
      localSocket:send(table.remove(response, 1))
    else
      localSocket:close()
      response = nil
    end
  end

  -- triggers the send() function again once the first chunk of data was sent
  sck:on("sent", send)
  send(sck)
end

if sv then
  print("Server Created.")
  sv:listen(80, function(conn) -- listen on port 80
    print("Receiving connection on port 80.")
    conn:on("receive", receiver)
  end)
else
  print("ERR: Server was not created.")
end
