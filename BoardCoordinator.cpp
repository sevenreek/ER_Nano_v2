#include "BoardCoordinator.h"
BoardCoordinator::BoardCoordinator(CommunicationController * pc, CommunicationController * mega, WirelessController * wireless)
{
	this->pc = pc;
	this->mega = mega;
	this->wireless = wireless;
}
const unsigned int TORCH_OFF_TEMP_DELAY_TIME = 3000; // time after which to turn the torches back on after TEMP_OFF
void BoardCoordinator::onUpdate()
{
	Message * msg = 0;
	if (pc->hasMessage(msg))
	{
		if (msg->sender == SNDR_PC)
		{
			if (msg->type == MTYPE_EVENT)
			{
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
					delay(TORCH_OFF_TEMP_DELAY_TIME);
					wireless->sendShort(TORCH_LOW, WirelessController::REPEAT_COUNT);
					break;
				case CMD_TORCH_OFF:
					wireless->sendShort(TORCH_OFF, WirelessController::REPEAT_COUNT);
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
