#include "pch.h"
#include "CJOpenHud.h"

//pretend its an audio codec for the miles sound system
bool __stdcall RIB_Main(int a, int b)
{
	return true;
}


std::shared_ptr<CJOpenHud> CJOpenHud::inst_CJOpenHud = nullptr;
CJOpenHud::CJOpenHud()
{
	inst_CJOpenHud = std::shared_ptr<CJOpenHud>(this);
	std::shared_ptr<hook_wrapper> inst_hooks = std::shared_ptr<hook_wrapper>(new hook_wrapper);
	std::shared_ptr<game> inst_game = std::shared_ptr<game>(new game());
	std::shared_ptr<input> inst_input = std::shared_ptr<input>(new input(this));
	std::shared_ptr<render> inst_render = std::shared_ptr<render>(new render(this));
	
	std::shared_ptr<ui_settings> inst_ui_settings = std::shared_ptr<ui_settings>(new ui_settings(this));
	std::shared_ptr<ui_position> inst_ui_position = std::shared_ptr<ui_position>(new ui_position(this));
	std::shared_ptr<ui_velocity> inst_ui_velocity = std::shared_ptr<ui_velocity>(new ui_velocity(this));
	std::shared_ptr<ui_view> inst_ui_view = std::shared_ptr<ui_view>(new ui_view(this));
}

CJOpenHud::~CJOpenHud()
{

}

CJOpenHud* CJOpenHud::get_instance()
{
	return inst_CJOpenHud.get();
}