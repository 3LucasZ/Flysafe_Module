#include <string>
#include<sstream>
#include<iomanip>
#include<stdio.h>
#include <BluetoothA2DPSource.h>

std::string addrToStr(esp_bd_addr_t* m_address) {
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(2) << std::hex << (int) ((uint8_t*) (m_address))[0] << ':';
	stream << std::setfill('0') << std::setw(2) << std::hex << (int) ((uint8_t*) (m_address))[1] << ':';
	stream << std::setfill('0') << std::setw(2) << std::hex << (int) ((uint8_t*) (m_address))[2] << ':';
	stream << std::setfill('0') << std::setw(2) << std::hex << (int) ((uint8_t*) (m_address))[3] << ':';
	stream << std::setfill('0') << std::setw(2) << std::hex << (int) ((uint8_t*) (m_address))[4] << ':';
	stream << std::setfill('0') << std::setw(2) << std::hex << (int) ((uint8_t*) (m_address))[5];
	return stream.str();
} 
bool strToBool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}