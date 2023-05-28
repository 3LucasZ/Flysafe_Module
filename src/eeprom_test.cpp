// /*
//  ESP32 startup counter example with Preferences library.

//  This simple example demonstrates using the Preferences library to store how many times the ESP32 module has booted. 
//  The Preferences library is a wrapper around the Non-volatile storage on ESP32 processor.

//  created for arduino-esp32 09 Feb 2017 by Martin Sloup (Arcao)
 
//  Complete project details at https://RandomNerdTutorials.com/esp32-save-data-permanently-preferences/
// */

// #include <Arduino.h>
// #include <Preferences.h>

// Preferences preferences;

// void setup() {
//   Serial.begin(115200);
//   while (!Serial);
//   Serial.println("Program begun");

//   preferences.begin("sto", false); //false = r/w, true = r

//   String counter = preferences.getString("speaker", "none");
//   counter.concat("YES");
//   Serial.print("msg: ");
//   Serial.println(counter);

//   preferences.putString("speaker", counter);
//   preferences.putString("speaker","");

//   //preferences.end(); //optional close

//   Serial.println("Restarting in 5 seconds...");
//   delay(5000);
//   ESP.restart();
// }

// void loop() {

// }