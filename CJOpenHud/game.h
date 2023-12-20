#pragma once
#include "d3dx9/d3dx9.h"
class game
{
public:
	HWND get_window(); 
	bool is_focused();
	LPDIRECT3DDEVICE9 get_device();
};

