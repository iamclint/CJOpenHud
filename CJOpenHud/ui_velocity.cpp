#include "pch.h"
#include "ui_velocity.h"
#include "CJOpenHud.h"

void ui_velocity::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	if (!hud->inst_game->is_connected()) //only draw while connected to a server
		return;
	vec3<float> vel = hud->inst_game->get_velocity();
	ImGui::SetNextWindowBgAlpha(0); //no background
	ImGui::Begin("Velocity information", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2);
	ImGui::TextColored(ImColor(1.0f, 0.0f, 0.0f, 1.0f), "%.f", vel.Length2D()); //cj typically uses the 2d velocity as to not add in drop to your speed
	ImGui::End();
}
ui_velocity::ui_velocity(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_velocity::~ui_velocity()
{

}