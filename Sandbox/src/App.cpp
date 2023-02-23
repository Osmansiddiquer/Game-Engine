#include <stdio.h>
namespace Engine {
	_declspec(dllimport) void Print(); //exports function to the .dll file
}

void main() {
	//Engine::Print();
}