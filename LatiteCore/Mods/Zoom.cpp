#include "Zoom.h"
#include "../LocalPlayer.h"
#include "ModManager.h"

float pastFOV;
float pastSens;
unsigned char pastHideHand;
bool keyPressed = false;
bool zoomEnabled;
float fovAmt = 45;
char bind_ = 'C';

void unzoom()
{
	LocalPlayer::setFOV(pastFOV);
	LocalPlayer::setSensitivity(pastSens);
	LocalPlayer::setHideHand(pastHideHand);
}

void zoom()
{
	pastSens = LocalPlayer::getSensitivity();
	pastFOV = LocalPlayer::getFOV();
	pastHideHand = LocalPlayer::getHideHand();

/*	for (float i = pastFOV; i > fovAmt; i -= 10)
	{
		// smoother thing
		Sleep(10);
		LocalPlayer::setFOV(i);
	}*/
	LocalPlayer::setFOV(pastFOV - fovAmt);
	LocalPlayer::setSensitivity(0.3);
	LocalPlayer::setHideHand(1);
}

void Zoom::setFovAmount(float fov)
{
	this->fovAmount = fov;
	fovAmt = fov;
	log << "new fa: " << this->fovAmount << "\n";
}

void Zoom::setBind(char b)
{
	bind_ = b;
	this->bind = b;
}

void Zoom::onDisable()
{
	this->enabled = false;
	zoomEnabled = false;
	unzoom();
}

void Zoom::onEnable()
{
	this->enabled = true;
	zoomEnabled = true;
}

void Zoom::onTick()
{
	/*
	check if they started pressing C (or whatever the key is)
	*/
	if ((GetKeyState(bind_) & 0x8000) && !keyPressed) // started being held down
	{
		keyPressed = true;
		if (zoomEnabled) zoom();
	}
	else if (!(GetKeyState(bind_) & 0x8000) && keyPressed)
	{
		keyPressed = false;
		if (zoomEnabled) unzoom();
	}
}