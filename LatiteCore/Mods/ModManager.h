// Handles all the mods

#pragma once

#ifndef MODMANAGER_H
#define MODMANAGER_H

#include "../dllmain.h"
#include "Zoom.h"
#include "../LookBehind.h"
#include "../ToggleSprint.h"

class Mod {
//	void onEnable();
//	void onDisable();
public:
	static void tickModules();
	static void initialize();
	static void disableAll();
};

Zoom getZoomModule();
LookBehind getLookBehindModule();
ToggleSprint getToggleSprintModule();

#endif