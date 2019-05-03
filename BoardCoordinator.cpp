#include "BoardCoordinator.h"
BoardCoordinator::BoardCoordinator(CommunicationController * pc, CommunicationController * mega, WirelessController * wireless)
{
	this->pc = pc;
	this->mega = mega;
	this->wireless = wireless;
}

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
