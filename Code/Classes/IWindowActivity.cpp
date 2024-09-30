#include "IWindowActivity.h"

void IWindowActivity::Run()
{
	while (window.isOpen()) {
		HandleInput();
		Update();
		Draw();
	}
}
