#pragma once

// Libraries

#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <sstream>
#include <vector>

using std::vector;

// Macros / Types

// 64 Bit unsigned integer
typedef unsigned long long ADDRESS;
#ifndef LATITE_EXPORTS
#define LATITE_API __declspec(dllexport)
#else
#define LATITE_API __declspec(dllimport)
#endif
#define BASE_H
#define DEBUG_MODE TRUE
#define log std::cout

// Exports

// Api Functions

extern "C" LATITE_API bool connectedToMinecraft(int type = 2);
extern "C" LATITE_API DWORD attach();
extern "C" LATITE_API void consoleMain();
extern "C" LATITE_API void detach();
extern "C" LATITE_API void loop();

extern "C" LATITE_API void setEnabled(unsigned int modId, bool enabled);

// this should be namespace if c# is good with that
extern "C" LATITE_API void mod_zoom_setBind(char bind);
extern "C" LATITE_API void mod_zoom_setAmount(float amount);
extern "C" LATITE_API void mod_lookBehind_setBind(char bind);

extern "C" LATITE_API void setTimeChangerSetting(int setting);

// Local Player
extern "C" LATITE_API float LPGetYMotion();
extern "C" LATITE_API float LPGetMotion();

extern "C" LATITE_API float LPGetXPos();
extern "C" LATITE_API float LPGetYPos();
extern "C" LATITE_API float LPGetZPos();

// code

// these are to be updated every Minecraft update

// pointer to fov
#define ADDRESS_FOV_BASEADDY 0x0369BD40
#define ADDRESS_FOV_SEMI_OFFSETS { 0x20, 0xC98, 0x68, 0x08, 0x1A0, 0x120 }

// pointer to sensitivity
#define ADDRESS_FSENS_BASEADDY 0x0369BD40
#define ADDRESS_FSENS_SEMI_OFFSETS { 0x20, 0xFA0, 0x1A8, 0xC78, 0x200, 0x48 }
#define ADDRESS_FSENS_LAST_OFFSET 0x14

// pointer to hide hand
#define ADDRESS_FHH_BASEADDY 0x0369BD40
#define ADDRESS_FHH_SEMI_OFFSETS { 0x20, 0x9F8, 0x1D8, 0x08, 0xD10 }
#define ADDRESS_FHH_LAST_OFFSET 0x1E0

// pointer to Y lower coordinate
#define ADDRESS_Y_BASEADDY 0x03699238
#define ADDRESS_Y_SEMI_OFFSETS { 0x10, 0x128, 0x0, 0x138, 0x490, 0xc0 }
#define ADDRESS_Y_LAST_OFFSET 0x49C

// pointer to F3 prespective
#define ADDRESS_PRESPECTIVE_BASEADDY 0x0369BD40
#define ADDRESS_PRESPECTIVE_OFFSETS { 0x20, 0xE88, 0x1D8, 0x08, 0x20 }
#define ADDRESS_PRESPECTIVE_LAST_OFFSET 0x1E8

// address to assembly code that checks if you're holding CTRL before sprinting
#define ADDRESS_STATIC_SPRINT_CODE 0x1618D8F

// pointer to time of day client side
#define ADDRESS_TIME_BASEADDY 0x036A1FB0
#define ADDRESS_TIME_OFFSETS { 0x0, 0x8F0, 0x28, 0x10, 0x7F8, 0x0 }
#define ADDRESS_TIME_LAST_OFFSET 0x5D0

// pointer to server IP
#define ADDRESS_SERVER_BASEADDY 0x36A1FB0
#define ADDRESS_SERVER_OFFSETS { 0x0, 0x518, 0x10, 0x0, 0x1E8, 0x380 }
#define ADDRESS_SERVER_LAST_OFFSET 0x0

// functions

// Gets starting address of Minecraft
ADDRESS currentModuleBase();
// Gets the process of Minecraft
HANDLE getHProcess();
// Gets in-game name
std::string getUsername();