#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int sensorPin = A5;
int sensorValue = 0;
int relay1 = 7;
int relay2 = 4;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  sensorValue = analogRead(sensorPin);
  digitalWrite(relay1, HIGH);
  delay(sensorValue);
  digitalWrite(relay1, LOW);
  delay(sensorValue);
  delay(2000); 

int h = dht.readHumidity();// Lee la humedad
int t= dht.readTemperature();//Lee la temperatura
//////////////////////////////////////////////////Humedad
Serial.print("Humedad Relativa: ");                 
Serial.print(h);//Escribe la humedad
Serial.println(" %");                     
delay (2500);
///////////////////////////////////////////////////Temperatura              
Serial.print("Temperatura: ");                  
Serial.print(t);//Escribe la temperatura
Serial.println(" C'");    
if(t > 25)
{
  digitalWrite(relay2, HIGH);
}
else
{
  digitalWrite(relay2, LOW);
}
}
