#include <FS.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#define RECONNECT_PIN 2
#define RESET_PIN 4       // Button (RST)

#define SSID "HackIoT"
#define PASSWORD "password"

const int baud = 19200;
// length should be max size + 1 
char mqtt_server[40];
char mqtt_port[6] = "8080";
char blynk_token[33] = "YOUR_BLYNK_TOKEN";
// default custom static IP
char static_ip[16] = "192.168.1.19";
char static_gw[16] = "192.168.1.254";
char static_sn[16] = "255.255.255.0";
// extra parameters
WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 5);
WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 34);

void saveConfigCallback () {
  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(blynk_token, custom_blynk_token.getValue());

  Serial.println("Connection Succeeded: Saving config..");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["mqtt_server"] = mqtt_server;
  json["mqtt_port"] = mqtt_port;
  json["blynk_token"] = blynk_token;
  json["ip"] = WiFi.localIP().toString();
  json["gateway"] = WiFi.gatewayIP().toString();
  json["subnet"] = WiFi.subnetMask().toString();

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  json.prettyPrintTo(Serial);
  json.printTo(configFile);
  Serial.println();
  configFile.close();
}


void read_config(){
  //SPIFFS.format();
  Serial.println("mounting FS...");
  if (SPIFFS.begin()){
    Serial.println("mounted file system");

    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");

      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);

        if (json.success()){
          Serial.println("\nparsed json");
          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(blynk_token, json["blynk_token"]);

          if(json["ip"]){
            Serial.println("setting custom ip from config");
            strcpy(static_ip, json["ip"]);
            strcpy(static_gw, json["gateway"]);
            strcpy(static_sn, json["subnet"]);
            Serial.println(static_ip);
          }else Serial.println("no custom ip in config");
        }else Serial.println("failed to load json config");
      }
    }
  }else Serial.println("failed to mount FS");

  Serial.println(static_ip);
  Serial.println(blynk_token);
  Serial.println(mqtt_server);
}


void wifi_setup(bool isReset){
  read_config();
  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  // reset settings if demanded
  if(isReset) wifiManager.resetSettings();

  IPAddress _ip,_gw,_sn;
  _ip.fromString(static_ip);
  _gw.fromString(static_gw);
  _sn.fromString(static_sn);
  wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);

  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_blynk_token);

  wifiManager.setMinimumSignalQuality();

  if (!wifiManager.autoConnect(SSID, PASSWORD)) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.print("local ip: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.subnetMask());
}


void setup() {
  Serial.begin(baud);
  pinMode(RECONNECT_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);
  WiFi.hostname("HackIoT");
  WiFi.printDiag(Serial);
  wifi_setup(false);
}


void loop() {
  if (digitalRead(RECONNECT_PIN) == LOW){
    wifi_setup(false);  // factory reset: false
    delay(2000);
  }

  if (digitalRead(RESET_PIN) == LOW){
    wifi_setup(true);   // factory reset: true
    delay(2000);
  }
  
  /* your code here; */
}


