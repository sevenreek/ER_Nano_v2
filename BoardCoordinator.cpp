#include "BoardCoordinator.h"
BoardCoordinator::BoardCoordinator(CommunicationController * pc, CommunicationController * mega, WirelessController * wireless)
{
	this->pc = pc;
	this->mega = mega;
	this->wireless = wireless;
	pinMode(PIN_DRAWER_LOCK, OUTPUT);
	digitalWrite(PIN_DRAWER_LOCK, HIGH);
	
}
const unsigned int TORCH_OFF_TEMP_DELAY_TIME = 4000; // time after which to turn the torches back on after TEMP_OFF not exactly ms
			// because the message is sent a lot of times to make sure it reaches the torches some minimal delay at the beginning exists
			// and equals the time it takes the transmitter to send the message the given amount of time.
void BoardCoordinator::onUpdate()
{
	
	if (reenableTorches && millis() > timedEventBegin + TORCH_OFF_TEMP_DELAY_TIME)
	{
		wireless->sendShort(TORCH_LOW, WirelessController::REPEAT_COUNT);
		reenableTorches = false;
	}
	Message * msg = 0;
	if (pc->hasMessage(msg))
	{
		if (msg->sender == SNDR_PC)
		{
			if (msg->type == MTYPE_EVENT)
			{
				Serial.println("Got event");
				switch (msg->command)
				{
				case CMD_TORCH_GLOW:
					wireless->sendShort(TORCH_HIGH, WirelessController::REPEAT_COUNT);
					break;
				case CMD_TORCH_DIM:
					wireless->sendShort(TORCH_LOW, WirelessController::REPEAT_COUNT);
					break;
				case CMD_TORCH_OFF_TEMP:
					wireless->sendShort(TORCH_OFF_TEMP, WirelessController::REPEAT_COUNT);
					timedEventBegin = millis();
					break;
				case CMD_TORCH_OFF:
					wireless->sendShort(TORCH_OFF, WirelessController::REPEAT_COUNT);
					break;
				case CMD_UNLOCK_DRAWER:
					Serial.println("Unlock drawer");
					digitalWrite(PIN_DRAWER_LOCK, LOW);
					delay(50);
					digitalWrite(PIN_DRAWER_LOCK, HIGH);
					break;
				default:
					mega->sendMessage(msg);
					break;
				}
			}
			else
				mega->sendMessage(msg);
		}
		delete msg;
		msg = 0;
		
	}
	if (mega->hasMessage(msg))
	{
		//Serial.print("Recieved pointer: "); Serial.println((int)msg);
		//Serial.println("Message recieved:");
		//Serial.println(msg->sender);
		//Serial.println(msg->type);
		//Serial.println(msg->command);
		pc->sendMessage(msg);
		delete msg;
		msg = 0;
	}

}
