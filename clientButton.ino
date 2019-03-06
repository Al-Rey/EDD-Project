//CLIENT CODE
#include <SPI.h>
#include <ESP8266WiFi.h>

const int greenLED = 15;
const int yellowLED = 2;//was 2
const int requestBtn = 4;
const int cancelBtn = 13;//DON'T USE 0 AS AN INPUT (D3) [was 12]

byte ledPin = 2;
char ssid[] = "AndroidAP5B11";           // SSID of your home WiFi
char pass[] = "rykr8399";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,43,208);       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);               // only for debug

  //GREEN LED - request sent
  pinMode(greenLED, OUTPUT);
  
  //YELLOW LED - cancel light (teacher cancels request / student cancels request
  pinMode(yellowLED, OUTPUT);

  //CANCEL BUTTON
  pinMode(cancelBtn, INPUT);

  //REQUEST BUTTON
  pinMode(requestBtn, INPUT);

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
/*  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());*/
  pinMode(ledPin, OUTPUT);
}

void loop () {
  client.connect(server, 80);   // Connection to the server
  digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
  Serial.println(".");
  if(digitalRead(RequestBtn)){
     digitalWrite(greenLED, HIGH);
     client.println("Request sent\r");
  }
  if(digitalRead(cancelBtn)){
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    client.println("Request canceled\r");
    delay(5000);
    digitalWrite(yellowLED, LOW);
  }
  
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
}
