#include "ModManager.h"

Zoom zoom;
LookBehind lookBehind;
ToggleSprint toggleSprint;
TimeChanger timeChanger;
Fullbright fullBright;

void Mod::disableAll()
{
	zoom.enabled = false;
	zoom.onDisable();
	lookBehind.enabled = false;
	lookBehind.onDisable();
	toggleSprint.enabled = false;
	toggleSprint.onDisable();
	timeChanger.onDisable();
}

void Mod::initialize()
{
	log << "Initializing mods\n";
	zoom.onEnable();
	lookBehind.onEnable();
	zoom.enabled = true;
	lookBehind.enabled = true;
}

void Mod::tickModules()
{
	zoom.onTick();
	lookBehind.onTick();
	//toggleSprint.onTick(); - not needed
	timeChanger.onTick();
	fullBright.onTick();
}

Zoom getZoomModule()
{
	return zoom;
}

LookBehind getLookBehindModule()
{
	return lookBehind;
}

ToggleSprint getToggleSprintModule()
{
	return toggleSprint;
}

TimeChanger getTimeChangerModule()
{
	return timeChanger;
}

Fullbright getFullbrightModule()
{
	return fullBright;
}
