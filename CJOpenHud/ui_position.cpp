#include "pch.h"
#include "ui_position.h"
#include "CJOpenHud.h"

void ui_position::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	if (!hud->inst_game->is_connected()) //only draw while connected to a server
		return;
	vec3<float> pos = hud->inst_game->get_origin();

	ImGui::SetNextWindowBgAlpha(.2);
	ImGui::Begin("Position information", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::BeginTable("pos info", 2);
	ImGui::TableNextColumn();
	ImGui::Text("X:");
	ImGui::TableNextColumn();
	ImGui::Text("%f", pos.x);

	ImGui::TableNextColumn();
	ImGui::Text("Y:");
	ImGui::TableNextColumn();
	ImGui::Text("%f", pos.y);

	ImGui::TableNextColumn();
	ImGui::Text("Z:");
	ImGui::TableNextColumn();
	ImGui::Text("%f", pos.z);
	ImGui::EndTable();
	ImGui::End();
}

ui_position::ui_position(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}

ui_position::~ui_position()
{

}
