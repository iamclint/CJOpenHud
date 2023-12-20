#pragma once
#include <memory>
#include "Input.h"
#include "Render.h"
#include "ui_position.h"
#include "ui_velocity.h"
#include "ui_view.h"
#include "ui_settings.h"
#include "Game.h"
#include "imgui-docking/imgui.h"
#include "imgui-docking/imgui_internal.h"
#include "imgui-docking/backends/imgui_impl_win32.h"
#include "imgui-docking/backends/imgui_impl_dx9.h"
#include "hook_wrapper.h"
#include "memory.h"
extern "C" {
	bool __declspec(dllexport) __stdcall RIB_Main(int a, int b);
}

class CJOpenHud
{
public: 
	CJOpenHud();
	~CJOpenHud();

	std::shared_ptr<input> inst_input = nullptr;
	std::shared_ptr<render> inst_render = nullptr;
	std::shared_ptr<game> inst_game = nullptr;
	std::shared_ptr<hook_wrapper> inst_hooks = nullptr;


	std::shared_ptr<ui_position> inst_ui_position = nullptr;
	std::shared_ptr<ui_velocity> inst_ui_velocity = nullptr;
	std::shared_ptr<ui_view> inst_ui_view = nullptr;
	std::shared_ptr<ui_settings> inst_ui_settings = nullptr;
	

	bool exit = false;
	bool give_cursor = false;
	static std::shared_ptr<CJOpenHud> inst_CJOpenHud;
	static CJOpenHud* get_instance();
};

