#include "pch.h"
#include "ui_position.h"
#include "CJOpenHud.h"

void ui_position::render()
{

}

ui_position::ui_position(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}

ui_position::~ui_position()
{

}
