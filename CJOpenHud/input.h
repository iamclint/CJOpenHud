#pragma once
#include <Windows.h>
class input
{
public:
	input(class CJOpenHud* pinst_openhud);
	~input();
	bool handle_key(UINT key_code, UINT state);
	WNDPROC p_wndproc = nullptr;
	HWND window_handle;
	void update_wndproc(HWND handle);
	
};

