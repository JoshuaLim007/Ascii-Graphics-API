#pragma once
#include <Windows.h>

class Input
{
private:
	struct KeyState {
		bool held;
		bool pressed;
		bool released;
	};
	static KeyState keys[256];
	static short key_states[256];
	static short old_key_states[256];
public:

	static void Tick();
	static bool GetKeyDown(int);
	static bool GetKeyUp(int);
	static bool GetKey(int);
};

