// #include <Arduino.h>

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>

// #define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
// #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// BLECharacteristic *pCharacteristic;

// void setup() {
//   //setup serial
//   Serial.begin(115200);
//   while(!Serial);
//   Serial.println("Program begun");
  
//   //setup BLE
//   BLEDevice::init("FlySafeModuleA"); //remember to incr to B,C,D
//   BLEServer *pServer = BLEDevice::createServer();
//   BLEService *pService = pServer->createService(SERVICE_UUID);
//   pCharacteristic = pService->createCharacteristic(
//                                          CHARACTERISTIC_UUID,
//                                          BLECharacteristic::PROPERTY_READ |
//                                          BLECharacteristic::PROPERTY_WRITE
//                                        );

//   pService->start();
//   BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//   pAdvertising->addServiceUUID(SERVICE_UUID);
//   pAdvertising->setScanResponse(true);
//   pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
//   pAdvertising->setMinPreferred(0x12);
//   BLEDevice::startAdvertising();
//   Serial.println("BLE setup finished");


// }

// void loop() {
//   int message = random(10);
//   pCharacteristic->setValue(message);
//   Serial.print("message: ");
//   Serial.println(message);
//   pCharacteristic->notify();
//   Serial.println("notified");
//   delay(2000);
// }
