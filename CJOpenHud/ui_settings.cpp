#include "pch.h"
#include "ui_settings.h"
#include "CJOpenHud.h"


void ui_settings::render()
{

}
ui_settings::ui_settings(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });

}
ui_settings::~ui_settings()
{

}