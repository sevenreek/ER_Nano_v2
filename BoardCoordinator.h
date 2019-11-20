#pragma once
#include "CommunicationController.h"
#include "WirelessController.h"
class GameStateInterface;
class BoardCoordinator {
private:
	GameStateInterface * currentInterface;
	CommunicationController * pc;
	CommunicationController * mega;
	WirelessController * wireless;
	unsigned int currentInterfaceIndex;
	unsigned int timedEventBegin;
	bool reenableTorches = false;
	const uint8_t PIN_DRAWER_LOCK = 4; 
public:
	BoardCoordinator(CommunicationController * pc, CommunicationController * mega, WirelessController * wireless);
	void onUpdate();
};