#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid="Wokwi-GUEST";
const char* password="";

const String url="https://raw.githubusercontent.com/nouraANDbats/ReadWebPageContentWithESP32controller/main/backward.html";// the URL of the webpage you want to read it`s content
String payload="";

int Fpin=27;
int Rpin=26;
int Lpin=14;
int Bpin=25;

void setup() {
  pinMode(Fpin, OUTPUT);
  pinMode(Rpin, OUTPUT);
  pinMode(Lpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");
}

void loop() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
    if( payload == "forward" ){
      digitalWrite(Fpin, HIGH);
    }
     else if(payload=="right"){
      digitalWrite(Rpin, HIGH);
    }
     else if(payload=="left"){
      digitalWrite(Lpin, HIGH);
    }
     else if(payload=="Backward"){
      digitalWrite(Bpin, HIGH);
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
  
}