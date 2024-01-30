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

	std::shared_ptr<input> inst_input;
	std::shared_ptr<render> inst_render;
	std::shared_ptr<game> inst_game;
	std::shared_ptr<hook_wrapper> inst_hooks;


	std::shared_ptr<ui_position> inst_ui_position;
	std::shared_ptr<ui_velocity> inst_ui_velocity;
	std::shared_ptr<ui_view> inst_ui_view;
	std::shared_ptr<ui_settings> inst_ui_settings;
	

	bool exit = false;
	bool want_input = false;
	bool bind_toggle_input(UINT key_state);
	bool bind_close(UINT key_state);
	static CJOpenHud* inst_CJOpenHud;
	static CJOpenHud* get_instance();
};

