// #include <stdio.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// #include <driver/gpio.h>
// #include "sdkconfig.h"

// #include <Arduino.h>
// #include <BluetoothA2DPSource.h>
// #include <math.h> 
// #include <my_utils.cpp>

// #include <0.h>

// SoundData *zero = new OneChannelSoundData((int16_t*)__0_raw, __0_raw_len/2);

// #define c3_frequency  130.81

// char dev1[]= "Bose AE2 SoundLink";
// char dev2[]= "Photive PH-BTW55 Speaker";

// BluetoothA2DPSource a2dp_source;

// // int32_t get_data_channels(Frame *frame, int32_t channel_len) {
// //     static double m_time = 0.0;
// //     double m_amplitude = 10000.0;  // -32,768 to 32,767
// //     double m_deltaTime = 1.0 / 44100.0;
// //     double m_phase = 0.0;
// //     double double_Pi = PI * 2.0;
// //     // fill the channel data
// //     for (int sample = 0; sample < channel_len; ++sample) {
// //         double angle = double_Pi * c3_frequency * m_time + m_phase;
// //         frame[sample].channel1 = m_amplitude * sin(angle);
// //         frame[sample].channel2 = frame[sample].channel1;
// //         m_time += m_deltaTime;
// //     }

// //     return channel_len;
// // }

// void setup() {
//     Serial.begin(115200);
//     while (!Serial);
//     Serial.println("Program starting...");

//     a2dp_source.set_auto_reconnect(false);
//     //a2dp_source.start(dev2, get_data_channels);  
//     a2dp_source.start(dev2); 
//     a2dp_source.set_volume(50);
//     Serial.println("Connected");
// }

// void loop() {
//     delay(10);

//     bool isConnected = a2dp_source.is_connected();
//     std::string lastPeer = addrToString(a2dp_source.get_last_peer_address());
//     Serial.print("Connected: ");
//     Serial.println(isConnected?"no":"yes");
//     Serial.print("Last peer:");
//     Serial.println(lastPeer.c_str());

//     a2dp_source.write_data(zero);
//     delay(1000);
// }