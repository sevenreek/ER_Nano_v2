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
public:
	BoardCoordinator(CommunicationController * pc, CommunicationController * mega, WirelessController * wireless);
	void onUpdate();
};