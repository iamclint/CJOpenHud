#include "pch.h"
#include "Render.h"
#include "CJOpenHud.h"


void init_graphics_stub()
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	openhud->inst_render->init_graphics();
}

HRESULT __stdcall EndScene_Hook(LPDIRECT3DDEVICE9 dev)
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	auto orig= openhud->inst_hooks->hook_map["EndScene"]->original(EndScene_Hook)(dev);
	openhud->inst_render->endscene(dev);
	return orig;
}

HRESULT __stdcall Reset_Hook(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{

	CJOpenHud* openhud = CJOpenHud::get_instance();
	auto orig = openhud->inst_hooks->hook_map["Reset"]->original(Reset_Hook);
	openhud->inst_render->invalidate_objects(pDevice);
	HRESULT rval = orig(pDevice, pPresentationParameters);
	openhud->inst_render->create_objects(pDevice);
	return rval;
}


void render::init_imgui(LPDIRECT3DDEVICE9 dev)
{
	if (!imgui_initialized)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = false;
		ImGui_ImplWin32_Init(CJOpenHud::get_instance()->inst_game->get_window());
		ImGui_ImplDX9_Init(dev);

		io.Fonts->AddFontDefault();
		ImGui_ImplDX9_CreateDeviceObjects();
		imgui_initialized = true;
	}
	dev->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFF);
}

void render::endscene(LPDIRECT3DDEVICE9 dev)
{
	init_imgui(dev);
	auto& io = ImGui::GetIO();

	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantCaptureMouse || openhud->give_cursor)
		io.MouseDrawCursor = true;
	else
		io.MouseDrawCursor = false;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	for (auto& fn : callbacks_render)
		fn();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void render::add_callback(RenderCallback render)
{
	callbacks_render.push_back(render);
}

void render::invalidate_objects(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}
void render::create_objects(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui_ImplDX9_CreateDeviceObjects();
}
void render::init_graphics()
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	//call the original function first
	openhud->inst_hooks->hook_map["InitGraphics"]->original(init_graphics_stub)();
	static LPDIRECT3DDEVICE9 current_device = nullptr;
	if (current_device != openhud->inst_game->get_device())
	{
		if (current_device)
		{
			D3DPRESENT_PARAMETERS p;
			current_device->Reset(&p);
		}
		current_device = openhud->inst_game->get_device();
		uint32_t* g_methodsTable = (uint32_t*)::calloc(119, sizeof(uint32_t));
		if (g_methodsTable)
		{
			imgui_initialized = false;
			::memcpy(g_methodsTable, *(uint32_t**)(openhud->inst_game->get_device()), 119 * sizeof(uint32_t));
			openhud->inst_hooks->Add("EndScene", g_methodsTable[42], EndScene_Hook, hook_type_detour);
			openhud->inst_hooks->Add("Reset", g_methodsTable[16], Reset_Hook, hook_type_detour);
			//update the wndproc hook on init
			openhud->inst_input->update_wndproc(openhud->inst_game->get_window());
		}
	}
}



render::render(CJOpenHud* openhud)
{
	//doing it this way only works if its loaded before initgraphics is called
	openhud->inst_hooks->Add("InitGraphics", 0x5f4f09, init_graphics_stub, hook_type_replace_call);
}

render::~render() //hooks are removed when the hook wrapper is destroyed
{
	ImGui::DestroyContext();
}