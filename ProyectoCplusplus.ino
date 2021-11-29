/*
    Problem: Run on Arduino for temperature & humidity sensor DHT11
*/
//// Librería Genérica Simular Arduino
#include <iostream>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11 
#define sensorPin 6
#define sensorValue

#define _TEST

#include "winet.h"

RelayBk2 relays(PINS(4,5)); // 3.5

auto on_off = false; // 3.5 Inverted logic: relay ON is false
using namespace std;

#define INLINE inline __attribute__((always_inline))

using SenseType = float;   // user-defined types = ADT = abstract data type
using PortType  = uint8_t; // unsigned int 8-bits = fixed size int

void delay(int ms) { for (int i=1; i<ms; i++); }

class SensorTemp { // Class = user defined type definition (define-and-use)
private: // default private visibility
    SenseType temp;
    SenseType moist;
    PortType  port = 2;
    DHT *dht;
public:
    void begin(PortType p) { 
        dht = new DHT(DHTPIN, DHTTYPE);
        dht->begin();
    }
    void read() {
       temp=dht->readTemperature();
       moist=dht->readHumidity();
    }
    friend ostream& operator << (ostream &os,  SensorTemp &s) {
        os << "temp = " << s.temp << "ºC" << endl; // Add humidity value
        return os;
    }
};

SensorTemp th; // use = instance = objeto

void setup() {
    th.begin(2);    // method (dot-operator)
    Serial.begin(115200);
  PL("** Testing Bank of Relays **");
  delay(800);
}

void loop() {
  
    th.read();
    cout << th; // attribute (dot-operator)
    delay(1000);
    relays = BuiltinLED = on_off;
  // relays.cmd(0, on_off);
  delay(500);
  on_off = !on_off; // toggle state
}
