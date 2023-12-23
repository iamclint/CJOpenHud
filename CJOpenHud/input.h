#pragma once
#include <Windows.h>
#include <functional>
typedef std::function<bool(UINT state)> InputCallback;
class input
{
public:
	input(class CJOpenHud* pinst_openhud);
	~input();
	bool handle_key(UINT key_code, UINT state);
	WNDPROC p_wndproc = nullptr;
	HWND window_handle;
	void update_wndproc(HWND handle);
	void add_callback(UINT key, InputCallback fn);
private:
	std::vector<std::pair<UINT,InputCallback>> callbacks_input{};
};

