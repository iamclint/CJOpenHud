#include "pch.h"
#include "Game.h"


HWND game::get_window()
{
	return *(HWND*)0xCC1B6FC;
}
bool game::is_focused()
{
	return *(bool*)0x0CC1B704;
}

LPDIRECT3DDEVICE9 game::get_device()
{
	return *(LPDIRECT3DDEVICE9*)0xCC9A408;
}

bool game::is_connected()
{
	int state = *(int*)0xC5F900;
	return state == connection_state_connected;
}

vec3<float> game::get_view()
{
	vec3<float> view = *(vec3<float>*)0x79B698;
	return view;
}

vec3<float> game::get_origin()
{
	vec3<float> pos = *(vec3<float>*)0x794490;
	return pos;
}

vec3<float> game::get_velocity()
{
	vec3<float> vel = *(vec3<float>*)0x79449c;
	return vel;
}