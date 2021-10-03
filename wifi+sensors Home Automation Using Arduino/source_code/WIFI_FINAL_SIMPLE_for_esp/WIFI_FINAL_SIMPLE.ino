#include<ESP8266WiFi.h> // we need to include library file for inbuilt function

const char* ssid = "Winter & Stark Automation"; // here you give name to your esp module which will be available on your phone just like your wifi name
const char* password = "Jonsnow#1008"; // for security we set password who can connect to your automation and who don't


WiFiServer server(80);// port 80 is default for wifi in devices for we need to communicate to server using port 80
int FanPin = 2; // 2=GPIO2 of ESP8266  //* this All PINS ARE general purpose pins in ESP so we can use it for turning ON/OFF devices
int StripPin = 4; // 4=GPIO4 of ESP8266  //* please take in cosider that you don't chose any other pin otherwise it won't work
int LedPin = 12; // 12=GPIO12 of ESP8266
int Expin1 = 0 ; // 0=GPIO0 of ESP8266 // this may be priting mistake on board (GP1O2) (bottom of GND)* consider it as 0 insted of 2
int Expin2 = 16; // 16=GPIO16 of ESP8266  

void setup() 
{
  delay(1000);
  WiFi.softAP(ssid, password); // start interacting & create wifi signal for Devices which need to be connected 
  
  server.begin(); // server stated with station(192.168.4.1) in Your case it might be different
  pinMode(FanPin, OUTPUT);
  delay(100);
  pinMode(StripPin, OUTPUT);
  delay(100);
  pinMode(LedPin, OUTPUT);
  delay(100);
  pinMode(Expin1,OUTPUT);
  delay(100);
  pinMode(Expin2,OUTPUT);  // set all 5 GPIO pins as OUTPUT
  delay(100);              // delay of 100 microseconds
 
  digitalWrite(FanPin, HIGH); // initially all set to off  as we have loW trigger so HIGH = off & LOW=on 
  digitalWrite(StripPin, HIGH);//according to your relay module you should specify HIGH and LOW 
  digitalWrite(LedPin, HIGH);
  digitalWrite(Expin1, HIGH);
  digitalWrite(Expin2, HIGH);

}


void loop()
 {
  WiFiClient client = server.available(); // if server is available on device then module will create 1 client of that server
  if (!client) // if client not found then exit this loop and search again for client
 {
    return;
  }

 while(!client.available()) // if available then wait for 1 microSeconds
 {
    delay(1);
  }
  
  String req = client.readStringUntil('\r'); // accepting data packets fsent by the server which is sent by 192.168.4.1 (e.g. LED_1/on)
  client.flush(); //now close the client connection until server sent another request
   
  //FAN
  if (req.indexOf("/FAN_1/off") != -1)   // compare string to check what to turn on - off
  {
  
    digitalWrite(FanPin, HIGH);
   
  } 
  else if (req.indexOf("FAN_1/on") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(FanPin, LOW);
 
  }
  
  //STRIP
  if (req.indexOf("/STRIP_1/off") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(StripPin, HIGH);
  } 
  else if (req.indexOf("STRIP_1/on") != -1)  // compare string to check what to turn on - off
  {
    digitalWrite(StripPin, LOW);
  }
  
  //LED
  if (req.indexOf("/LED_1/off") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(LedPin, HIGH);
  } 
  else if (req.indexOf("LED_1/on") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(LedPin, LOW);
  }
  
  //External Pin 1
  if (req.indexOf("/ExternalPin1_1/off") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(Expin1, HIGH);
  } 
  else if (req.indexOf("ExternalPin1_1/on") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(Expin1, LOW);
  }
  
  //External Pin 2
  if (req.indexOf("/ExternalPin2_1/off") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(Expin2, HIGH);
  } 
  else if (req.indexOf("ExternalPin2_1/on") != -1)   // compare string to check what to turn on - off
  {
    digitalWrite(Expin2, LOW);
  }
  else if (req.indexOf("/") != -1); // to end with nothing on &off bcz loop will always continue to be executed
  else 
 {
    client.stop(); // here client req. will stop and it will return control back to new loop
    return;
  }
   
  client.flush(); 
  
  // actual webpages to be created

String HTML = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html> <h1>DIY Winter & Stark Automation</h1> <h2> Control</h2>";

//Fan
HTML += "<h3>Fan is : ";

HTML += (digitalRead(FanPin))?"OFF":"ON</h3>"; //Low = FAN ON and High = FAN OFF

HTML += "<h3>Fan : <button onclick=\"window.location.href='/FAN_1/on'\">ON</button>&nbsp;<button onclick=\"window.location.href='/FAN_1/off'\">OFF</button></h3></html>";

//Strip LED 
HTML += "<h3>Strip LED is : ";

HTML += (digitalRead(StripPin))?"OFF":"ON</h3>"; //Low = Strip LED  and High = Strip LED 

HTML += "<h3>Strip LED  :<button onclick=\"window.location.href='/STRIP_1/on'\">ON</button>&nbsp;<button onclick=\"window.location.href='/STRIP_1/off'\">OFF</button></h3></html>";

//LED
HTML += "<h3>LED is :";

HTML += (digitalRead(LedPin))?"OFF":"ON</h3>"; //Low = FAN ON and High = FAN OFF

HTML += "<h3>LED :<button onclick=\"window.location.href='/LED_1/on'\">ON</button>&nbsp;<button onclick=\"window.location.href='/LED_1/off'\">OFF</button></h3></html>";

//External Pin 1
HTML += "<h3>External Pin 1 is :";

HTML += (digitalRead(Expin1))?"OFF":"ON</h3>"; //Low = EX1 ON and High = Ex1 OFF

HTML += "<h3>External Pin 1 : <button onclick=\"window.location.href='/ExternalPin1_1/on'\">ON</button>&nbsp;<button onclick=\"window.location.href='/ExternalPin1_1/off'\">OFF</button></h3></html>";

//External Pin 2
HTML += "<h3>External Pin 2 is :";

HTML += (digitalRead(Expin2))?"OFF":"ON</h3>"; //Low = EX2 ON and High = Ex2 OFF

HTML += "<h3>External Pin 2 : <button onclick=\"window.location.href='/ExternalPin2_1/on'\">ON</button>&nbsp;<button onclick=\"window.location.href='/ExternalPin2_1/off'\">OFF</button></h3></html>";

client.print(HTML); // make webpage means it will print all HTML code to 192.168.4.1 station
delay(10);
}
