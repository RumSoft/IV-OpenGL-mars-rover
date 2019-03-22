#include "InputHandler.h"

InputHandler* InputHandler::instance;

InputHandler* InputHandler::GetInstance() {
	if (InputHandler::instance == nullptr)
		InputHandler::instance = new InputHandler();
	return InputHandler::instance;
}