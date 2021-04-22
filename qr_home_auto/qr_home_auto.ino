#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif


#define LED1 15
#define LED2 2
#define LED3 4
#define LED4 22


const char* ssid     = "SSID";
const char* password = "PASS";


char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<body>

<center>
<h1>My Home Automation</h1>

<h3> LED 1 </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led1/on'">On</button><button onclick="window.location = 'http://'+location.hostname+'/led1/off'">Off</button>
<h3> LED 2 </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led2/on'">On</button><button onclick="window.location = 'http://'+location.hostname+'/led2/off'">Off</button>
<h3> LED 3 </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led3/on'">On</button><button onclick="window.location = 'http://'+location.hostname+'/led3/off'">Off</button>
<h3> LED 4 </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led4/on'">On</button><button onclick="window.location = 'http://'+location.hostname+'/led4/off'">Off</button>

</center>
</body>
</html>

)=====";

// ipaddress/led1/on
//ipaddress/led1/off

// ipaddress/led2/on
//ipaddress/led2/off
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  
  WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

  if (MDNS.begin("ESP2")) { //esp2.local/
    Serial.println("MDNS responder started");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", webpage);
  });

   server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,HIGH);
  request->send_P(200, "text/html", webpage);
  });

     server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,LOW);
  request->send_P(200, "text/html", webpage);
  });


    server.on("/led2/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED2,HIGH);
  request->send_P(200, "text/html", webpage);
  });

     server.on("/led2/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED2,LOW);
  request->send_P(200, "text/html", webpage);
  });

    server.on("/led3/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED3,HIGH);
  request->send_P(200, "text/html", webpage);
  });

     server.on("/led3/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED3,LOW);
  request->send_P(200, "text/html", webpage);
  });

    server.on("/led4/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED4,HIGH);
  request->send_P(200, "text/html", webpage);
  });

     server.on("/led4/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED4,LOW);
  request->send_P(200, "text/html", webpage);
  });

   server.on("/led3/toggle", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED3,!digitalRead(LED3));
  request->send_P(200, "text/plain", "Light Toggled");
  });

  server.on("/led4/toggle", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED4,!digitalRead(LED4));
  request->send_P(200, "text/plain", "Light Toggled");
  });

  server.on("/led2/toggle", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED2,!digitalRead(LED2));
  request->send_P(200, "text/plain", "Light Toggled");
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
}


void loop(void)
{
}
