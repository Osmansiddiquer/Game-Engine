#pragma once
class InputManager
{
public:
	bool IsKeyDown(int keycode);

private:
	static InputManager* s_Instance;
};

