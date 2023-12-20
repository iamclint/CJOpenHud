#include "pch.h"
#include "Input.h"
#include "CJOpenHud.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND WINAPI get_foreground_window()
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	HWND orig = openhud->inst_hooks->hook_map["GetForegroundWindow"]->original(get_foreground_window)();
	if (openhud->give_cursor)
		return 0; //tell the game that it isn't the foreground window
	return orig;
}

input::input(CJOpenHud* openhud)
{
	openhud->inst_hooks->Add("GetForegroundWindow", GetProcAddress(GetModuleHandleA("user32.dll"), "GetForegroundWindow"), get_foreground_window, hook_type_detour);
}

input::~input()
{
	SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)p_wndproc);
}

bool input::handle_key(UINT key_code, UINT state)
{
	if (key_code == VK_ESCAPE && CJOpenHud::get_instance()->give_cursor)
	{
		CJOpenHud::get_instance()->give_cursor = false;
		return true;
	}
	if (key_code == VK_F4)
	{
		if (state == WM_KEYDOWN)
			return true;
		if (state == WM_KEYUP)
		{
			
			CJOpenHud::get_instance()->give_cursor = !CJOpenHud::get_instance()->give_cursor;
			return true;
		}
	}
	return false;
}

LRESULT __stdcall wndproc_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!CJOpenHud::get_instance())
		return 1;
	

	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);


	if (CJOpenHud::get_instance()->inst_game->is_focused())
	{
		if (uMsg == WM_KEYUP || uMsg == WM_KEYDOWN)
		{
			
			if (CJOpenHud::get_instance()->inst_input->handle_key(wParam, uMsg))
				return 1; //the key was handled and blocked by the handle key function
		}
	}

	if (CJOpenHud::get_instance()->give_cursor)
		return 1;

	return CallWindowProc(CJOpenHud::get_instance()->inst_input->p_wndproc, hWnd, uMsg, wParam, lParam);
}

void input::update_wndproc(HWND handle)
{
	if (window_handle != handle)
	{
		window_handle = handle;
		p_wndproc = (WNDPROC)(SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)wndproc_hook));
	}
}