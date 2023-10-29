// basic ESP stuff IDK if its necessary
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"

// incl Arduino component
#include <Arduino.h>

// BLE
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_DIST_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_VOL_UUID "66d04e60-89ba-4ab2-a0b3-2257bc8d43f7"
#define CHAR_OFFSET_UUID "8c3b12cb-3445-4961-b9af-c49521dc9d7a"
#define CHAR_REBOOT_UUID "0d006e04-39d4-4d90-ae33-e278cbc6dc66"
BLECharacteristic *distChar;
BLECharacteristic *volChar;
BLECharacteristic *speakerChar;
BLECharacteristic *offsetChar;
BLECharacteristic *rebootChar;
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        // to only allow one device connected at a time, do not restart advertising after a connection
        // pServer->startAdvertising(); // restart advertising after a connection
    };
    void onDisconnect(BLEServer *pServer) {
        pServer->startAdvertising(); // restart advertising after a disconnect
    }
};

// LIDAR
#include <Wire.h>
#include <LIDARLite.h>
LIDARLite lidar;

// EEPROM
#include <Preferences.h>
Preferences preferences;
int curVol = 50;
int curOffset = 0;
int wait = 50;

void setup()
{
    // setup serial
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Started program");

    // setup EEPROM
    preferences.begin("sto", false);
    curVol = preferences.getInt("vol", 50);
    curOffset = preferences.getInt("offset", 0);
    Serial.println("Retrieved data from EEPROM");

    // setup BLE server + service
    BLEDevice::init("FlySafeModuleA"); // remember to incr to B,C,D,etc
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks()); // set the callback function
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // setup characteristics
    distChar = pService->createCharacteristic(CHAR_DIST_UUID, BLECharacteristic::PROPERTY_READ);
    int tmpDist = 0;
    distChar->setValue(tmpDist);
    volChar = pService->createCharacteristic(CHAR_VOL_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);
    volChar->setValue(curVol);
    offsetChar = pService->createCharacteristic(
        CHAR_OFFSET_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);
    offsetChar->setValue(curOffset);
    rebootChar = pService->createCharacteristic(
        CHAR_REBOOT_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);
    int tmpReboot = 1;
    rebootChar->setValue(tmpReboot);

    // begin BLE server
    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("BLE setup finished");

    // setup LIDAR
    lidar.begin(0, true); // Set configuration to default and I2C to 400 kHz
    lidar.configure(3);   // Change this number to try out alternate configurations, 3 means max range
    Serial.println("LIDAR setup finished");
}

void loop()
{
    // read dist 
    int dist = lidar.distance();
    Serial.print("cm:");
    Serial.println(dist);

    // write dist to Web
    distChar->setValue(dist);
    delay(wait);
   
    // read vol from Web
    int newVol = volChar->getData()[0];
    Serial.print("vol:");
    Serial.println(newVol);
    preferences.putInt("vol",newVol);
    delay(wait);

    // read offset from Web
    uint8_t* offsetBuffer = offsetChar->getData();
    int newOffset = offsetBuffer[0]+256*offsetBuffer[1];
    Serial.print("offset:");
    Serial.println(newOffset);
    preferences.putInt("offset",newOffset);
    delay(wait);

    // read reboot from Web
    int newReboot = rebootChar->getData()[0];
    Serial.print("reboot:");
    Serial.println(newReboot);
    if (newReboot!=1) ESP.restart();
    delay(wait);
}