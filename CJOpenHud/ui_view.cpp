#include "pch.h"
#include "ui_view.h"
#include "CJOpenHud.h"

void ui_view::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	if (!hud->inst_game->is_connected()) //only draw while connected to a server
		return;
	vec3<float> view = hud->inst_game->get_view();
	
	ImGui::SetNextWindowBgAlpha(.2);
	ImGui::Begin("View information", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::BeginTable("view info", 2);
		ImGui::TableNextColumn();
		ImGui::Text("Pitch:");
		ImGui::TableNextColumn();
		ImGui::Text("%f", view.x);

		ImGui::TableNextColumn();
		ImGui::Text("Yaw:");
		ImGui::TableNextColumn();
		ImGui::Text("%f", view.y);

		ImGui::TableNextColumn();
		ImGui::Text("Roll:");
		ImGui::TableNextColumn();
		ImGui::Text("%f", view.z);
	ImGui::EndTable();
	ImGui::End();
}
ui_view::ui_view()
{
	
}
ui_view::~ui_view()
{

}