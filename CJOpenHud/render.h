#pragma once
#include "d3dx9/d3dx9.h"
#include <functional>
typedef std::function<void()> RenderCallback;
class render
{
public:
	render(class CJOpenHud* openhud);
	~render();
	void init_graphics();
	void endscene(LPDIRECT3DDEVICE9 pDevice);
	void invalidate_objects(LPDIRECT3DDEVICE9 pDevice);
	void create_objects(LPDIRECT3DDEVICE9 pDevice);
	void init_imgui(LPDIRECT3DDEVICE9 dev);
	void add_callback(RenderCallback);

private:
	bool imgui_initialized = false;
	std::vector<RenderCallback> callbacks_render{};
};

