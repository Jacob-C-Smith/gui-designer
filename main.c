#include <stdio.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

#include <Designer/Label.h>
#include <Designer/Button.h>

UIWindow_t* target = 0;

int main ( int argc, const char *argv[] )
{
	UIInstance_t *instance = ui_init(0);
	UIWindow_t   *window   = load_window("G UI Designer/main window.json");

	target = window;

	ui_append_window(instance, window);
	label_constructor_dialog(instance, window);
	button_constructor_dialog(instance, window);

	while (instance->windows)
	{
		ui_process_input(instance);

		ui_draw(instance);
	}

	ui_exit(instance);
}