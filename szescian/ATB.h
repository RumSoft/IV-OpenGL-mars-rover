#pragma once
#include <AntTweakBar.h>
bool ATB::KeyboardCB(OGLDEV_KEY OgldevKey)
{
	int ATBKey = OgldevKeyToATBKey(OgldevKey);

	if (ATBKey == TW_KEY_LAST) {
		return false;
	}

	return (TwKeyPressed(ATBKey, TW_KMOD_NONE) == 1);
}


bool ATB::PassiveMouseCB(int x, int y)
{
	return (TwMouseMotion(x, y) == 1);
}


bool ATB::MouseCB(OGLDEV_MOUSE Button, OGLDEV_KEY_STATE State, int x, int y)
{
	TwMouseButtonID btn = (Button == OGLDEV_MOUSE_BUTTON_LEFT) ? TW_MOUSE_LEFT : TW_MOUSE_RIGHT;
	TwMouseAction ma = (State == OGLDEV_KEY_STATE_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;

	return (TwMouseButton(ma, btn) == 1);
}