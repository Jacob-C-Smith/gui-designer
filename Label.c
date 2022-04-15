#include <Designer/Label.h>

static const char *submit_button_name       = "label_submit",
                  *label_input_name         = "label_text_input",
                  *x_input_name             = "label_x_input",
                  *y_input_name             = "label_y_input",
	              *name_input_name          = "label_name_input",
				  *text_label               = "label_text",
				  *x_label                  = "label_x",
				  *y_label                  = "label_y",
				  *name_label               = "label_name";
extern UIWindow_t *target;

void label_constructor_submit_callback(UIButton_t* button, mouse_state_t mouse)
{
	// Initialized data
	UIInstance_t *instance     = ui_get_active_instance();
	UIWindow_t   *window       = instance->windows;

	// Elements required to build the element
	UIElement_t  *text_input_element = find_element(window, label_input_name),
	             *x_input_element    = find_element(window, x_input_name),
	             *y_input_element    = find_element(window, y_input_name),
	             *name_input_element = find_element(window, name_input_name),
		         *text_label_element = find_element(window, text_label),
				 *x_label_element    = find_element(window, x_label),
		         *y_label_element    = find_element(window, y_label),
				 *name_label_element = find_element(window, name_label);


	// User specified text
	char         *text       = (text_input_element->type == UI_TEXTINPUT) ? text_input_element->element.text_input->text : 0,
	             *x          = (x_input_element->type    == UI_TEXTINPUT) ? x_input_element->element.text_input->text    : 0,
	             *y          = (y_input_element->type    == UI_TEXTINPUT) ? y_input_element->element.text_input->text    : 0,
		         *name       = (name_input_element->type == UI_TEXTINPUT) ? name_input_element->element.text_input->text : 0;

	// Label text
	char         *text_label = (text_label_element->type == UI_LABEL) ? text_label_element->element.label->text : 0,
		         *x_label    = (x_label_element->type    == UI_LABEL) ? x_label_element->element.label->text    : 0,
		         *y_label    = (y_label_element->type    == UI_LABEL) ? y_label_element->element.label->text    : 0,
		         *name_label = (name_label_element->type == UI_LABEL) ? name_label_element->element.label->text : 0;


	// Error checking
	{
		if ( text == 0 )
			goto no_text;
		if ( x    == 0 )
			goto no_x;
		if ( y    == 0 )
			goto no_y;
		if ( name == 0 )
			goto no_name;

		if (strlen(text) == 0)
		{
			if (text_label)
				text_label[4] = '*';
			goto no_text;
		}
		else
		{
			if (text_label)
				text_label[4] = ' ';
		}

		if (strlen(x)    == 0)
		{
			if (x_label)
				x_label[4] = '*';
			goto no_text;
		}
		else
		{
			if (x_label)
				x_label[4] = ' ';
		}
		
		if (strlen(y)    == 0)
		{
			if (y_label)
				y_label[4] = '*';
			goto no_text;
		}
		else
		{
			if (y_label)
				y_label[4] = ' ';
		}
		
		if (strlen(name) == 0)
		{
			if (name_label)
				name_label[4] = '*';
			goto no_text;
		}
		else
		{
			if (name_label)
				name_label[4] = ' ';
		}

		
	}

	append_element_to_window(target, construct_element (name, construct_label(text, atoi(x), atoi(y)), UI_LABEL));

	//window->is_open = false;

	// Error handling
	{
		no_text:
		no_x:
		no_y:
		no_name:
		return;
	}
}

int label_constructor_dialog ( UIInstance_t *instance, UIWindow_t *target )
{
	// Argument check
	{
		#ifndef NDEBUG
			if (instance == (void *)0)
				goto no_instance;
		#endif
	}
	
	UIWindow_t  *dialog                = load_window("G UI Designer/label constructor.json");
	UIElement_t *submit_button_element = find_element(dialog, submit_button_name);
	UIButton_t  *submit_button         = (submit_button_element) ? (submit_button_element->element.button) : 0;
	target = target;
	add_click_callback_button(submit_button, &label_constructor_submit_callback);

	dialog->is_open = true;
	ui_append_window(instance, dialog);

	return 0;

	// Error handling
	{

		// Argument errors
		{
			no_instance:
				#ifndef NDEBUG
					ui_print_error("[Designer] [Constructor] Null pointer provided for \"instance\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif
				return 0;
		}
	}
}
