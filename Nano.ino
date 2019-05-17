// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Nano.ino
    Created:	2019-05-01 8:07:36 PM
    Author:     DESKTOP-RP1NLIS\Dickbutt
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
const static int RF_SPEED = 2000;
const static int RF_RX = 12;
const static int RF_TX = 11;
const static int RF_PTT = 10;
const static bool RF_PTT_INV = false;
// The setup() function runs once each time the micro-controller starts
#include <SPI.h>
#include <NeoICSerial.h>
#include <RH_ASK.h>
#include "BoardCoordinator.h"
#include "CommunicationController.h"
#include "WirelessController.h"
BoardCoordinator * coordinator;
CommunicationController * pc;
CommunicationController * mega;
WirelessController * torches;
NeoICSerial * serial;
void setup()
{
	Serial.begin(9600);
	serial = new NeoICSerial();
	serial->begin(9600);
	pc = new CommunicationController(&Serial);
	mega = new CommunicationController(serial);
	torches = new WirelessController(RF_SPEED, RF_RX, RF_TX, RF_PTT, RF_PTT_INV);
	coordinator = new BoardCoordinator(pc, mega, torches);
	mega->pushCommsCleaner();
	//torches->sendShort(TORCH_HIGH, WirelessController::REPEAT_COUNT);
}

// Add the main program code into the continuous loop() function
void loop()
{
	//Serial.println("Update");
	coordinator->onUpdate();
}
