// #include <Arduino.h>

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>

// #define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
// #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// BLECharacteristic *pCharacteristic;
// class MyServerCallbacks: public BLEServerCallbacks {
//     void onConnect(BLEServer* pServer) {
//         //to only allow one device connected at a time, do not restart advertising.
//         pServer->startAdvertising(); // restart advertising
//     };

//     void onDisconnect(BLEServer* pServer) {
//       pServer->startAdvertising(); // restart advertising
//     }
// };


// void setup() {
//     //setup serial
//     Serial.begin(115200);
//     while(!Serial);
//     Serial.println("Program begun");
    
//     //setup BLE
//     BLEDevice::init("BLE_read"); //remember to incr to B,C,D
//     BLEServer *pServer = BLEDevice::createServer();
//     pServer->setCallbacks(new MyServerCallbacks()); //set the callback function
//     BLEService *pService = pServer->createService(SERVICE_UUID);
//     pCharacteristic = pService->createCharacteristic(
//                                             CHARACTERISTIC_UUID,
//                                             BLECharacteristic::PROPERTY_READ |
//                                             BLECharacteristic::PROPERTY_WRITE
//                                         );
//     pCharacteristic->setValue("Empty");                                   
//     pService->start();
//     BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//     pAdvertising->addServiceUUID(SERVICE_UUID);
//     pAdvertising->setScanResponse(true);
//     pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
//     pAdvertising->setMinPreferred(0x12);
//     BLEDevice::startAdvertising();
//     Serial.println("BLE setup finished");
// }

// void loop() {
//   std::string msg = pCharacteristic->getValue();
//   Serial.print("message: ");Serial.println(msg.c_str());
//   Serial.print("message len:");Serial.println(msg.length());
  
//   delay(500);
// }
