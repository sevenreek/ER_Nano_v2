#pragma once
#include <SPI.h>
#include <RH_ASK.h>
#include "Message.h"
class WirelessController {
private:
	RH_ASK * driver;
public:
	static const int REPEAT_COUNT = 25;
	WirelessController(int speed, int rx, int tx, int ptt, bool ptt_inv);
	void sendMessage(Message * m, int repeatCount);
	void sendShort(uint8_t shrt, int repeatCount);
};