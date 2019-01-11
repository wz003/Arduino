#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include <PubSubClient.h>

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

const char* mqtt_server = "broker.hivemq.com"; //broker.hivemq.com
const char* IOT_topic = "home37/LED1";
char* IOT_ACK = "home37/LED1/ACK";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

int pin=2; //pin 2 EQUAL TO LED_BUILD_IN
int pin2 = 16;

void setup(){
  Serial.begin(115200);
  pinMode(2, OUTPUT); 
  pinMode(16, OUTPUT); 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.subscribe(IOT_topic);
  client.setCallback(callback);
}

void setup_wifi() {
  WiFiManager wifiManager;
  //wifiManager.resetSettings(); //forget SSID & password every plugging
  
  //first parameter is name of access point, second is the password
  //wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
  wifiManager.autoConnect("SoftAP_testing");

  // Start the server
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print the IP address
  
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print(".");
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("DoNotKickMeOUTTT")) {
      Serial.println("connected");
      // Once connected, publish an announcement and resubscribe...
      client.subscribe(IOT_topic);
      //client.publish(IOT_topic, "Reconnected Successed");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String received = "";
  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    if(c!='\n' and c!='\r'){
      received += c;
      Serial.print(c);
    }
  }
  Serial.println();

  if (received=="close") {
    digitalWrite(pin2, 1);
    client.publish(IOT_ACK, "LED Closed");
  }else if(received=="open"){
    digitalWrite(pin2, 0);
    client.publish(IOT_ACK, "LED Opened");
  }/*else{
    Serial.print("repeat: ");
    Serial.println(s);
  }*/
}


void loop(){
  if (!client.connected()) {
    digitalWrite(pin, 1);
    Serial.print("Attempting MQTT connection...");
    reconnect();
  }else{
    digitalWrite(pin, 0);
    client.loop();
  }
  
  delay(500);
}






