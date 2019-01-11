#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dhcp.h>
#include <EthernetServer.h>
#include <Dns.h>
#include <EthernetUdp.h>

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  pinMode(2, OUTPUT); 
  pinMode(16, OUTPUT); 
  //setting WIFI
  WiFiManager wifiManager;
  //wifiManager.resetSettings(); forget SSID & password every plugging
  
  //first parameter is name of access point, second is the password
  //wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
  wifiManager.autoConnect("SoftAP_testing");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop(){
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1) {
    val = LOW;
  } else if (req.indexOf("/gpio/1") != -1) {
    val = HIGH;
  } else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  Serial.print("request : ");
  Serial.println(val);
  digitalWrite(2, val);
  digitalWrite(16, val);

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val) ? "high" : "low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed 
}






