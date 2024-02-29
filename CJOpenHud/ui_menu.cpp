#include "pch.h"
#include "ui_menu.h"
#include "CJOpenHud.h"

void ui_menu::menu(CJOpenHud* hud)
{
	ImGui::Begin("OpenCJHud");

	ImGui::Checkbox("Show Velocity", &show_velocity);

	ImGui::SameLine(); ImGui::ColorButton("Color Button", velocity_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("ColorPickerPopup");
	}

	if(ImGui::BeginPopup("ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &velocity_color.x);

		ImGui::EndPopup();
	}

	ImGui::Checkbox("Show Position", &show_position);

	ImGui::Checkbox("Show View Angles", &show_view);
}

void ui_menu::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	
	if(hud->want_input)
	{
		menu(hud);
	}

	if(show_velocity)
	{
		hud->inst_ui_velocity->render();
	}

	if(show_position)
	{
		hud->inst_ui_position->render();
	}

	if(show_view)
	{
		hud->inst_ui_view->render();
	}
	
}

ui_menu::ui_menu(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}

ui_menu::~ui_menu()
{

}
