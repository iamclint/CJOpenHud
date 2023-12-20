#include "pch.h"
#include "ui_view.h"
#include "CJOpenHud.h"

void ui_view::render()
{
	if (!ImGui::Begin("test window"))
	{
		ImGui::End();
		return;
	}
	ImGui::Button("test button");
	ImGui::End();
}
ui_view::ui_view(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_view::~ui_view()
{

}