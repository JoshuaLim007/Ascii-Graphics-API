#include "InputManager.h"


Input::KeyState Input::keys[256];
short Input::key_states[256];
short Input::old_key_states[256];


void Input::Tick() {
	for (int i = 0; i < 256; i++)
	{
		key_states[i] = GetAsyncKeyState(i);
		keys[i].pressed = false;
		keys[i].released = false;
		if (key_states[i] != old_key_states[i]) {
			if (key_states[i] & 0x8000)
			{
				keys[i].pressed = !keys[i].held;
				keys[i].held = true;
			}
			else
			{
				keys[i].released = true;
				keys[i].held = false;
			}
		}
		old_key_states[i] = key_states[i];
	}
}


bool Input::GetKeyDown(int code) {
	return keys[code].pressed;
}
bool Input::GetKeyUp(int code) {
	return keys[code].released;
}
bool Input::GetKey(int code) {
	return keys[code].held;
}