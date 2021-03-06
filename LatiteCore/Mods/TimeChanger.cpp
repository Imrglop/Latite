#include "TimeChanger.h"
#include "../Utils/memory.h"
#include "../dllmain.h"
#include "../Utils/server_mod_disabler.h"

unsigned int tick = 0;
int timeSet = 0;
bool isEnabled = false;
bool disabledByServer = false;

void TimeChanger::onDisable()
{
	this->enabled = false;
	isEnabled = false;
	memory::WriteBytes(currentModuleBase() + 0xD4D5F1, { 0x89, 0x81, 0x90, 0x03, 0x00, 0x00 });
	memory::WriteBytes(currentModuleBase() + 0x80E224, { 0x44, 0x89, 0x88, 0x90, 0x03, 0x00, 0x00 });
	log << "Timechanger on disable\n";
}

void TimeChanger::onEnable(int time)
{
	this->enabled = true;
	isEnabled = true;
	disabledByServer = moduleDisabledOnServer(LocalPlayer::getServer(), "time_changer");
	if (disabledByServer) return;
	memory::Nop(currentModuleBase() + 0xD4D5F1, 6);
	memory::Nop(currentModuleBase() + 0x80E224, 6);
	timeSet = time;
	tick = 0;
	LocalPlayer::setTime(timeSet);
	log << "Timechanger on enable\n";
}

void TimeChanger::onTick()
{
	if (disabledByServer) {
		this->onDisable();
		return;
	}
	if (isEnabled && (tick % 20) == 0)
	{
		LocalPlayer::setTime(timeSet);
	}
	tick++;
}
