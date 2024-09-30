#pragma once
#include <memory>
#include "IWindowActivity.h"

class WindowStateManager
{
private:
std::unique_ptr<IWindowActivity> currentState;

WindowStateManager() {};

public:
	
	WindowStateManager(const WindowStateManager&) = delete;

	WindowStateManager& operator=(const WindowStateManager&) = delete;

	static WindowStateManager& getInstance() {
		static WindowStateManager instance;
		return instance;
}

	void setState(std::unique_ptr<IWindowActivity> newState) {
		currentState = std::move(newState);
	}

	void RunState() {
		currentState->Run();
	}


};

