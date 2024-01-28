#include "pch.h"
#include "Input.h"
#include "CJOpenHud.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND WINAPI get_foreground_window()
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	HWND orig = openhud->inst_hooks->hook_map["GetForegroundWindow"]->original(get_foreground_window)();
	if (openhud->want_input)
		return 0; //tell the game that it isn't the foreground window
	return orig;
}

input::input(CJOpenHud* openhud)
{
	window_handle = nullptr;
	openhud->inst_hooks->Add("GetForegroundWindow", GetProcAddress(GetModuleHandleA("user32.dll"), "GetForegroundWindow"), get_foreground_window, hook_type_detour);
}

input::~input()
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (openhud && openhud->inst_hooks)
	{
		openhud->inst_hooks->hook_map["GetForegroundWindow"]->remove(); //remove hook here in case of a race condition on destructors
	}
	SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)p_wndproc);
}

bool input::handle_key(UINT key_code, UINT state)
{

	for (auto &[ key, fn ] : callbacks_input)
	{
		if (key == key_code && fn(state)) //if the callback returns true then return true here as well so we can block the input
			return true;
	}
	if (key_code == VK_ESCAPE && CJOpenHud::get_instance()->want_input)
	{
		CJOpenHud::get_instance()->want_input = false;
		return true;
	}
	return false;
}

LRESULT __stdcall wndproc_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!CJOpenHud::get_instance())
		return 1;
	
	if (CJOpenHud::get_instance()->want_input) //only give input information to imgui if we want input so it doesn't get clicked and dragged or typed in while just playing
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);


	if (CJOpenHud::get_instance()->inst_game->is_focused())
	{
		if (uMsg == WM_KEYUP || uMsg == WM_KEYDOWN)
		{
			
			if (CJOpenHud::get_instance()->inst_input->handle_key(wParam, uMsg))
				return 1; //the key was handled and blocked by the handle key function
		}
	}

	if (CJOpenHud::get_instance()->want_input)
		return 1;

	return CallWindowProc(CJOpenHud::get_instance()->inst_input->p_wndproc, hWnd, uMsg, wParam, lParam);
}
void input::add_callback(UINT key, InputCallback fn)
{
	callbacks_input.push_back({ key, fn });
}
void input::update_wndproc(HWND handle)
{
	if (window_handle != handle)
	{
		if (p_wndproc)
			SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)p_wndproc);
		window_handle = handle;
		p_wndproc = (WNDPROC)(SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)wndproc_hook));
	}
}