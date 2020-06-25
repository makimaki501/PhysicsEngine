#include "Input.h"

Input::Input()
{
	memset(mKeyPressingCount, 0, sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount, 0, sizeof(mKeyReleasingCount));
}

Input::~Input()
{
}

void Input::Update()
{
	char nowKeyStatus[KEY_NUM];

	GetHitKeyStateAll(nowKeyStatus);


	for (int i = 0; i < KEY_NUM; i++)
	{
		if (nowKeyStatus[i] != 0)
		{
			// —£‚³‚ê‚Ä‚È‚¢‚Ì‚ÅƒJƒEƒ“ƒg‚ð‰Šú‰»
			if (mKeyReleasingCount[i] > 0)
			{
				mKeyReleasingCount[i] = 0;
			}
			mKeyPressingCount[i]++;
		}
		else
		{
			if (mKeyPressingCount[i] > 0)
			{
				mKeyPressingCount[i] = 0;
			}
		}
	}
}

int Input::GetKeyPressingCount(int keyCode)
{
	if (!Input::IsAvaiableKeyCode(keyCode))
	{
		return -1;
	}

	return mKeyPressingCount[keyCode];
}

int Input::GetKeyReleasingCount(int keyCode)
{
	if (!Input::IsAvaiableKeyCode(keyCode))
	{
		return -1;
	}

	return mKeyReleasingCount[keyCode];
}

bool Input::isKeyDown(int keyCode)
{
	if (GetKeyPressingCount(keyCode) == 1)
	{
		return true;
	}

	return false;
}

bool Input::isKey(int keyCode)
{
	if (GetKeyPressingCount(keyCode) >= 1)
	{
		return true;
	}

	return false;
}



bool Input::IsAvaiableKeyCode(int keyCode)
{
	if (!(0 <= keyCode && keyCode < KEY_NUM))
	{
		return false;
	}

	return true;
}

