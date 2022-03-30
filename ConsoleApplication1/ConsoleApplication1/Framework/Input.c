#include "stdafx.h"
#include "Input.h"

static bool _currentKeyStates[256] = { false };
static bool _prevKeyStates[256] = { false };

void UpdateInput()
{

}

bool GetButtonDown(EKeyCode keyCode)
{
	if (false == _prevKeyStates[keyCode] && _currentKeyStates[keyCode])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GetButtonUp(EKeyCode keyCode)
{
	if (_prevKeyStates[keyCode] && false == _currentKeyStates[keyCode])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GetButton(EKeyCode keyCode)
