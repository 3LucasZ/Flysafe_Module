/*
NOTES:
TRUE: Use const for raw sound arrays to reduce dynamic RAM usage
TRUE: You can not use bluetooth (specifically, A2DP) with wifi
TRUE: Hold down BOOT NOT EN when loading to ESP32 using Arduino IDE
TRUE: NEVER interact with serial during BT use, or else can not connect
SET: Components -> Debug Log -> Error only
 */

// basic ESP stuff IDK if its necessary
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include "my_utils.cpp"

// incl Arduino component
#include <Arduino.h>

// BLE
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// LIDAR
#include <Wire.h>
#include <LIDARLite.h>

// EEPROM/real state
#include <Preferences.h>
Preferences preferences;
int curVol = 50;


// BLE
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_DIST_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_VOL_UUID "66d04e60-89ba-4ab2-a0b3-2257bc8d43f7"
#define CHAR_SPEAKER_UUID "90788378-fca7-48da-9b30-a0bbfeacdb7b"
BLECharacteristic *distChar;
BLECharacteristic *volChar;
BLECharacteristic *speakerChar;
class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer){
        // to only allow one device connected at a time, do not restart advertising.
        // pServer->startAdvertising(); // restart advertising
    };
    void onDisconnect(BLEServer *pServer)
    {
        pServer->startAdvertising(); // restart advertising
    }
};

// LIDAR
LIDARLite lidar;

// fcn
void setupBLE();
void setupLidar();

void setup()
{

    Serial.begin(115200);
    while (!Serial);

    Serial.println("Program begun");

    preferences.begin("sto", false);
    curVol = preferences.getInt("vol", 50);

    setupBLE();
    setupLidar();
}

void loop()
{
    // read frame
    int decimeters = round(lidar.distance() / 10.0);
    Serial.print("dm:");
    Serial.println(decimeters);

    // write frame_dist to Web
    distChar->setValue(decimeters);
    delay(100);
   
    // read frame_vol from Web
    // int newVol = stoi(volChar->getValue());
    // preferences.putInt("vol",newVol);
    //delay(100);

    // read frame_reboot from Web
    //bool reboot = strToBool(volChar->getValue());
    //delay(100);
}

void setupBLE()
{
    // setup BLEServer + Service
    BLEDevice::init("FlySafeModuleA"); // remember to incr to B,C,D
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks()); // set the callback function
    BLEService *pService = pServer->createService(SERVICE_UUID);
    //dist
    distChar = pService->createCharacteristic(
        CHAR_DIST_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);
    
    //vol
    volChar = pService->createCharacteristic(
        CHAR_VOL_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);

    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();

    Serial.println("BLE setup finished");
}

void setupLidar()
{
    lidar.begin(0, true); // Set configuration to default and I2C to 400 kHz
    lidar.configure(0);   // Change this number to try out alternate configurations
}