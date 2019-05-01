#include "WirelessController.h"

WirelessController::WirelessController(int speed, int rx, int tx, int ptt, bool ptt_inv)
{
	driver = new RH_ASK(speed, rx, tx, ptt, ptt_inv);
	driver->init();
}
void WirelessController::sendMessage(Message *m, int repeatCount)
{
	char * mes = Message::toCharArray(m);
	int len = strlen(mes);
	while (repeatCount--)
	{
		driver->send((uint8_t*)mes,len);
		driver->waitPacketSent();
	}
}
void WirelessController::sendShort(uint8_t shrt, int repeatCount)
{
	while (repeatCount--)
	{
		driver->send(&shrt, 1);
		driver->waitPacketSent();
	}
}
