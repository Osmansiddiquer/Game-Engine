namespace Engine {
	_declspec(dllimport) void Print(); //imports Print from the .dll file
}
void main() {
	Engine::Print();
}