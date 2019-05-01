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
			switch (msg->command)
			{
				case CMD_TORCH_GLOW:
					wireless->sendShort(SHRT_1, WirelessController::REPEAT_COUNT);
				break;
				case CMD_TORCH_DIM:
					wireless->sendShort(SHRT_2, WirelessController::REPEAT_COUNT);
				break;
				default: 
					mega->sendMessage(msg);
				break;
			}
		}
		delete msg;
		msg = 0;
	}
	if (mega->hasMessage(msg))
	{
		pc->sendMessage(msg);
		delete msg;
		msg = 0;
	}

}
