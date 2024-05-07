#include "DHT.h"
#include <stdlib.h>
#include <string.h>
 #include <Adafruit_Sensor.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


#define DHTTYPE DHT22
const int DHTPin = 13;
DHT dht(DHTPin, DHTTYPE);
char inputBuffer[10];
char tx[10];
int h, t;
#define SERVICE_UUID "df620f6f-8907-47b1-aa61-1e81d2db5f6f"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {

      Serial.print("Received Value: ");
      for (int i = 0; i < rxValue.length(); i++) {
        inputBuffer[i]=rxValue[i];
      }
      if (strcmp(inputBuffer,"temp") == 0) {
        t = dht.readTemperature();
        Serial.print("Tempertaure ==>");
        Serial.println(t);
        pCharacteristic->notify(itoa(t,tx,10));

      } 
      else if (strcmp(inputBuffer, "humid") == 0) {
        h = dht.readHumidity();
        Serial.print("Humidity ==> ");
        Serial.print(h);
        pCharacteristic->notify(itoa(h,tx,10));
      }
    }
  }
};



void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  dht.begin();
  BLEDevice::init("Harsh");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  // setCallbacks is an API used to create class object MyCallbacks()
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello says => Harsh, Vijay, Dipesh, Romana");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}