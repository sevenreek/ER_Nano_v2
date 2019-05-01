#pragma once
#include "Message.h"
#include "Arduino.h"
class CommunicationController {
private:
	Stream * stream;
	char messageArray[TOTAL_LENGTH];
	unsigned int pos;
public:
	CommunicationController(Stream * stream);
	bool hasMessage(Message * msg);
	void sendMessage(Message * msg);
};