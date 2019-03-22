#pragma once
#include <Windows.h>

const int keyboardInputStateArraySize = 256;

enum KeyState {
	StillReleased,
	JustPressed,
	StillPressed,
	JustReleased
};

class InputHandler
{
private:
	static InputHandler* instance;
	InputHandler() = default;

	bool keyboardStateCurrent[keyboardInputStateArraySize];

public:
	static InputHandler* GetInstance();

	void Update() {
		for (int i = 0; i < keyboardInputStateArraySize; i++) {
			keyboardStateCurrent[i] = GetAsyncKeyState(i) < 0;
		}
	}

	bool IsDown(const unsigned char key) {
		return keyboardStateCurrent[key];
	}

};

