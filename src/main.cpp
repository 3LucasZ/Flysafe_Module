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

// A2DP
#include <BluetoothA2DPSource.h>

#include "1.h"
#include "2.h"
#include "3.h"
#include "4.h"
#include "5.h"
#include "6.h"
#include "7.h"
#include "8.h"
#include "9.h"

#include "10.h"
#include "20.h"
#include "30.h"
#include "40.h"
#include "50.h"

#include "point.h"
#include "none.h"
#include "0.h"

// BLE
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// LIDAR
#include <Wire.h>
#include <LIDARLite.h>

// EEPROM
#include <Preferences.h>
Preferences preferences;

// A2DP
//"Bose AE2 SoundLink";
//"Photive PH-BTW55 Speaker";
String curSpeaker = "NOT-CONFIGURED";
int curVol = 50;
BluetoothA2DPSource a2dp_source;

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

SoundData *one = new OneChannelSoundData((int16_t *)__1_raw, __1_raw_len / 2);
SoundData *two = new OneChannelSoundData((int16_t *)__2_raw, __2_raw_len / 2);
SoundData *three = new OneChannelSoundData((int16_t *)__3_raw, __3_raw_len / 2);
SoundData *four = new OneChannelSoundData((int16_t *)__4_raw, __4_raw_len / 2);
SoundData *five = new OneChannelSoundData((int16_t *)__5_raw, __5_raw_len / 2);
SoundData *six = new OneChannelSoundData((int16_t *)__6_raw, __6_raw_len / 2);
SoundData *seven = new OneChannelSoundData((int16_t *)__7_raw, __7_raw_len / 2);
SoundData *eight = new OneChannelSoundData((int16_t *)__8_raw, __8_raw_len / 2);
SoundData *nine = new OneChannelSoundData((int16_t *)__9_raw, __9_raw_len / 2);

SoundData *ten = new OneChannelSoundData((int16_t *)__10_raw, __10_raw_len / 2);
SoundData *twenty = new OneChannelSoundData((int16_t *)__20_raw, __20_raw_len / 2);
SoundData *thirty = new OneChannelSoundData((int16_t *)__30_raw, __30_raw_len / 2);
SoundData *fourty = new OneChannelSoundData((int16_t *)__40_raw, __40_raw_len / 2);
SoundData *fifty = new OneChannelSoundData((int16_t *)__50_raw, __50_raw_len / 2);

SoundData *point = new OneChannelSoundData((int16_t *)point_raw, point_raw_len / 2);
SoundData *zero = new OneChannelSoundData((int16_t *)__0_raw, __0_raw_len / 2);
SoundData *none = new OneChannelSoundData((int16_t *)none_raw, none_raw_len / 2);

SoundData *ones[10];
SoundData *tens[6];

// fcn
void setupA2DP();
void setupBLE();
void setupLidar();

void setup()
{

    Serial.begin(115200);
    while (!Serial);

    Serial.println("Program begun");

    preferences.begin("sto", false);
    curSpeaker = preferences.getString("speaker", "NOT-CONFIGURED");
    curVol = preferences.getInt("vol", 50);

    setupA2DP();
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
    Serial.print("dm: ");
    Serial.println(decimeters);
    delay(200);
    // read frame_speaker from Web
    String newSpeaker = String(speakerChar->getValue().c_str());
    Serial.print("cur: ");
    Serial.println(curSpeaker);
    Serial.print("new: ");
    Serial.println(newSpeaker.c_str());
    Serial.print("same? ");
    bool same = strcmp(curSpeaker.c_str(), newSpeaker.c_str()) == 0 || newSpeaker.length() == 0;
    Serial.println(same ? "yes" : "no");
    if (!same)
    {
        preferences.putString("speaker", newSpeaker);
        ESP.restart();
    }

    delay(200);
    // read frame_vol from Web
    // int newVol = stoi(volChar->getValue());
    // preferences.putInt("vol",newVol);
    //a2dp_source.set_volume(newVol);
    delay(200);
    // read frame_reboot from Web
    //bool reboot = strToBool(volChar->getValue());
    //delay(100);
    // callout frame
    int precision = 3;

    int speakDecimal = decimeters % 10;
    decimeters /= 10;
    int speakOnes = decimeters % 10;
    decimeters /= 10;
    int speakTens = decimeters % 10;
    decimeters /= 10;

    if (precision >= 1)
    {
        a2dp_source.write_data(tens[speakTens]);
        delay(400);
    }
    if (precision >= 2)
    {
        a2dp_source.write_data(ones[speakOnes]);
        delay(400);
    }
    if (precision >= 3)
    {
        a2dp_source.write_data(point);
        delay(400);
    }
    if (precision >= 3)
    {
        a2dp_source.write_data(ones[speakDecimal]);
        delay(400);
    }
}

void setupA2DP()
{
    a2dp_source.set_auto_reconnect(false);
    a2dp_source.start(curSpeaker.c_str());
    a2dp_source.set_volume(curVol);
    Serial.println("A2DP setup finished");
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
   
    //speaker
    speakerChar = pService->createCharacteristic(
        CHAR_SPEAKER_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);

    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();

    //put prelim data
    //distChar->setValue(0);
    //delay(100);
    //volChar->setValue(curVol);
    //delay(100);
    Serial.println("BLE setup finished");
}

void setupLidar()
{
    lidar.begin(0, true); // Set configuration to default and I2C to 400 kHz
    lidar.configure(0);   // Change this number to try out alternate configurations

    ones[0] = none;
    ones[1] = one;
    ones[2] = two;
    ones[3] = three;
    ones[4] = four;
    ones[5] = five;
    ones[6] = six;
    ones[7] = seven;
    ones[8] = eight;
    ones[9] = nine;

    tens[0] = none;
    tens[1] = ten;
    tens[2] = twenty;
    tens[3] = thirty;
    tens[4] = fourty;
    tens[5] = fifty;
}