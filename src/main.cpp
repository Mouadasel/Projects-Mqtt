#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>


const char* ssid ="TP-LINK_9512B5";
const char* pass ="casa2022";
// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);




void setupWifi(){
  delay(100);
  Serial.print("\nConnecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConnected to");
  Serial.println(ssid);
}
void reconnect(){
  while(!client.connected()){
    Serial.print("\nConnecting to ");
    Serial.println(mqtt_server);
    if(client.connect("clientId-GCSG0K2cTB")){
      Serial.print("\nConnected to ");
      Serial.println(mqtt_server);
      
      
    }
    else{
      Serial.println("\nTrying connect again");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  
  
}



void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  
  setupWifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  
  reconnect();
}


void loop() {
  // put your main code here, to run repeatedly:
if(!client.connected()){
  reconnect();
}
client.loop();

}