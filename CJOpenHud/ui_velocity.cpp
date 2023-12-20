#include "pch.h"
#include "ui_velocity.h"
#include "CJOpenHud.h"

void ui_velocity::render()
{

}
ui_velocity::ui_velocity(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_velocity::~ui_velocity()
{

}