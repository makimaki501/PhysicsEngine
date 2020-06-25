#pragma once
#include <DxLib.h>
#include "Singleton.h"
#include <memory>

static class Input : public Singleton<Input>
{
	Input();
	~Input();
	friend Singleton<Input>;

public:
	void Update();
	int GetKeyPressingCount(int keyCode);
	int GetKeyReleasingCount(int keyCode);
	bool isKeyDown(int keyCode);
	bool isKey(int keyCode);

private:
	static const int KEY_NUM = 256;
	int mKeyPressingCount[KEY_NUM];
	int mKeyReleasingCount[KEY_NUM];
	bool IsAvaiableKeyCode(int keyCode);
};