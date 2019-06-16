#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
const int keyboardInputStateArraySize = 256;

class InputHandler
{
private:
	static InputHandler* instance;
	InputHandler()
	{
		for (int i = 0; i < keyboardInputStateArraySize; i++) {
			keyboardStatePrevious[i] = false;
			keyboardStatePrevious2[i] = false;
			keyboardStatePrevious3[i] = false;
			keyboardStateCurrent[i] = false;
		}
	};
	//3x previous, 1 previous should work theoretically, but it doesn't
	//2 previous works almost
	//3 previous works 
	bool keyboardStateCurrent[keyboardInputStateArraySize]{};
	bool keyboardStatePrevious[keyboardInputStateArraySize]{};
	bool keyboardStatePrevious2[keyboardInputStateArraySize]{};
	bool keyboardStatePrevious3[keyboardInputStateArraySize]{};
public:
	static InputHandler* GetInstance();

	void Update() {
		for (int i = 0; i < keyboardInputStateArraySize; i++) {
			if (i == 'V') {

			}
			keyboardStatePrevious3[i] = keyboardStatePrevious2[i];
			keyboardStatePrevious2[i] = keyboardStatePrevious[i];
			keyboardStatePrevious[i] = keyboardStateCurrent[i];
			keyboardStateCurrent[i] = GetAsyncKeyState(i) < 0;
		}
	}

	//holding 
	bool IsDown(const unsigned char key) {
		return keyboardStateCurrent[key];
	}

	bool IsUp(const unsigned char key) {
		return !keyboardStateCurrent[key];
	}

	//one-time fire
	bool IsPressed(const unsigned char key)
	{
		return keyboardStateCurrent[key] && !keyboardStatePrevious3[key];
	}

	//one-time fire
	bool IsReleased(const unsigned char key)
	{
		return !keyboardStateCurrent[key] && keyboardStatePrevious3[key];
	}
};

