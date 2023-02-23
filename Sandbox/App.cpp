#include <stdio.h>
namespace Engine {
	_declspec(dllexport) void Print(); //exports function to the .dll file
}

void main() {
	Print();
}