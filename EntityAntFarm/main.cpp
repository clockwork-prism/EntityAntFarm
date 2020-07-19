// O------------------------------------------------------------------------------O
// | Example "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O

#include "olcPixelGameEngine.h"
#include "MainEngine.h"

int main()
{
	MainEngine engine;
	if (engine.Construct(256, 256, 2, 2))
		engine.Start();
	return 0;
}