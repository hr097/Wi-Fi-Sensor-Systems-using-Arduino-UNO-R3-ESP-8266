#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>



#define HOME 4
#define LED 12
#define FAN 2
#define AC  16
#define TV 0

char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<head>
  <title>
    Winter And Stark
  </title>
  <link rel = "icon" href = "WS.jpeg" type = "image/x-icon">
  <meta content="width=device-width, initial-scale=1" name="viewport" />
  <script src="jquery.min.js"></script>

  <style>
      * {
    -webkit-tap-highlight-color: transparent;
}
    body {
      font-family: 'Poppins', sans-serif;
      background-color: black;
      padding-bottom: 50px;
    }

    th {
      font-weight: 600;
    }

    table {
      border-collapse: collapse;
      width: 70%;
    }

    .Title {
      padding-left: 100px;
      font-size: 25px;
    }

    table tr {
      border-bottom: .5px solid grey;
      background: white;
    }

    table tr:nth-child(1) {
      border-bottom: 0;

    }

    table th:nth-child(1) {
      padding-bottom: 50px;
      padding-top: 50px;
      font-size: 41px;
      color: white;
      font-weight: 100;
    
    }

    

    
  

    tr:nth-child(1) {
      background-color: rgb(81 81 81);
    }

    
    .button {
      background-color: black; /* Green */
      font-family: 'Poppins', sans-serif;
      border: none;
      color: white;
      padding: 15px 32px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      margin: 4px 2px;
      cursor: pointer;
  }

    .button1 {
    font-size: 15px;
    border-radius:5px;
    }
    .button2 {font-size: 15px;
    border-radius:5px;}
    .Logo {
      color: White;
      text-align: center;
      font-size: 75px;
      font-family: 'Poppins', sans-serif;
      padding: 25px 0 70px;
      
    }
    input,
    textarea,
    button,
    select,
    a {
    -webkit-tap-highlight-color: rgba(0,0,0,0);
    }
  
    @media (max-width:1000px) {
      .Title {
        padding-left: 45px;
      }
      table th:nth-child(1){
        font-weight: 400;
        font-size: 35px !important;
      }
    }

    @media (max-width:700px) {
      .Title {
        font-size: 20px !important;
        padding-left: 30px;
      }
      table{
        width: 90%;
      }
      .Logo {
        font-size: 50px;
        margin: auto;
        display: block;
      }
    }

  </style>
</head>

<body>
  <center>
    <div class="Logo">
      Winter & Stark
    </div>

    <table class="table1" cellpadding="20" cellspacing="0" bgcolor="#F0FFF0">

      <tr>
        <th colspan="4">
          <center>Control Panel</center>
        </th>
      </tr>
      <tr>
        <td class="Title">Home Light</td>
        <th>
          
          <button class="button button1" id="4" onclick="Check(4,1)">ON</button>
          <button class="button button2" id="4" onclick="Check(4,0)">OFF</button>
        </th>
      </tr>

      <tr>
        <td class="Title">Bulb Light</td>
        <th>
          <button class="button button1" id="12" onclick="Check(12,1)">ON</button>
          <button class="button button2" id="12" onclick="Check(12,0)">OFF</button>
        </th>
      </tr>
      <tr>
        <td class="Title">A.C.</td>
        <th>
          <button class="button button1" id="16" onclick="Check(16,1)">ON</button>
          <button class="button button2" id="16" onclick="Check(16,0)">OFF</button>
        </th>
      </tr>
      <tr>
        <td class="Title">Television</td>
        <th>
          <button class="button button1" id="0" onclick="Check(0,1)">ON</button>
          <button class="button button2" id="0" onclick="Check(0,0)">OFF</button>
        </th>
      </tr>
      <tr>
        <td class="Title">Fan</td>
        <th>
          <button class="button button1" id="2" onclick="Check(2,1)">ON</button>
          <button class="button button2" id="2" onclick="Check(2,0)">OFF</button>
        </th>
      </tr>

  </center>
  </table>
  <script type="text/javascript">
    function Check(ID,POS) {var INPUT = document.getElementById(ID);
      
      if (POS) {
        window.location.href = http://${location.hostname}/${ID}/on;
        //console.log(${ID} - ON);
      }
      else {

        window.location.href = http://${location.hostname}/${ID}/off;
        //console.log(${ID} - OFF);
      }
    }

  </script>

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
  
  pinMode(HOME,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(AC,OUTPUT);
  pinMode(TV,OUTPUT);
  pinMode(FAN ,OUTPUT);
  digitalWrite(HOME,HIGH);
  digitalWrite(LED,HIGH);
  digitalWrite(AC,HIGH);
  digitalWrite(TV,HIGH);
  digitalWrite(FAN ,HIGH);
  
  WiFi.softAP("Winter & Stark Automation", "Jonsnow#1008");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }


  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", webpage);
  });

 
   server.on("/4/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(HOME,LOW);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/4/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(HOME,HIGH);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/12/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED,LOW);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/12/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED,HIGH);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/16/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(AC,LOW);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/16/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(AC,HIGH);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/2/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(FAN,LOW);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/2/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(FAN,HIGH);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/0/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(TV,LOW);
    request->send_P(200, "text/html", webpage);
  });
  server.on("/0/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(TV,HIGH);
    request->send_P(200, "text/html", webpage);
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
}


void loop(void)
{
}
