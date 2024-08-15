#include "App.h"
#include "Window.h"

//implements app
wxIMPLEMENT_APP(App);

//opens a window
bool App::OnInit() {
	window = new Window();
	window->Show(true);
	return true;
}
