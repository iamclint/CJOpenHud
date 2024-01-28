#include "pch.h"
#include "Render.h"
#include "CJOpenHud.h"


void init_graphics_stub()
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (openhud && openhud->inst_render)
		openhud->inst_render->init_graphics();
}

HRESULT __stdcall EndScene_Hook(LPDIRECT3DDEVICE9 dev)
{
	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (openhud && openhud->inst_hooks && openhud->inst_render)
	{
		auto orig = openhud->inst_hooks->hook_map["EndScene"]->original(EndScene_Hook)(dev);
		openhud->inst_render->endscene(dev);
		return orig;
	}
	return 1;
}

HRESULT __stdcall Reset_Hook(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{

	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (openhud && openhud->inst_hooks && openhud->inst_render)
	{

		auto orig = openhud->inst_hooks->hook_map["Reset"]->original(Reset_Hook);
		openhud->inst_render->invalidate_objects(pDevice);
		HRESULT rval = orig(pDevice, pPresentationParameters);
		openhud->inst_render->create_objects(pDevice);
		return rval;
	}
	return 1;
}
void imgui_easy_theming(ImVec4 color_for_text, ImVec4 color_for_head, ImVec4 color_for_area, ImVec4 color_for_body, ImVec4 color_for_pops)
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.95f);
	//style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.58f);
	style.Colors[ImGuiCol_Border] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.47f);

	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	//style.Colors[ImGuiCol_ComboBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);

	style.Colors[ImGuiCol_CheckMark] = ImColor(158, 151, 169, 255).Value;
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_Tab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.76f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	//	style.Colors[ImGuiCol_Column] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.32f);
	//	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	//	style.Colors[ImGuiCol_ColumnActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.15f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	//	style.Colors[ImGuiCol_CloseButton] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.16f);
	//	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.39f);
	//	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImColor(130, 174, 51, 255).Value;// ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImColor(0, 0, 0, 150).Value;
}


void SetupImGuiStyle2()
{
	static ImVec4 color_for_text = ImVec4(.92f, .94f, .94f, 0);
	static ImVec4 color_for_head = ImVec4(ImColor(65, 60, 73, 255).Value);
	static ImVec4 color_for_area = ImVec4(ImColor(82, 75, 92, 255).Value);
	static ImVec4 color_for_body = ImVec4(ImColor(0, 0, 0, 255).Value);
	static ImVec4 color_for_pops = ImColor(40, 37, 45, 255).Value;

	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().ChildRounding = 0.0f;
	ImGui::GetStyle().FrameRounding = 0.0f;
	ImGui::GetStyle().GrabRounding = 0.0f;
	ImGui::GetStyle().PopupRounding = 0.0f;
	ImGui::GetStyle().ScrollbarRounding = 0.0f;
	ImGui::GetStyle().FramePadding = ImVec2(2, 2);
	ImGui::GetStyle().WindowPadding = ImVec2(5, 5);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2(15, 0);
	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;
	

	static bool first_run = true;
	if (first_run)
	{
		imgui_easy_theming(color_for_text, color_for_head, color_for_area, color_for_body, color_for_pops);
		first_run = false;
	}

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
		ImFontConfig config;
		config.SizePixels = 16;
		io.Fonts->AddFontDefault(&config);
		ImGui_ImplDX9_CreateDeviceObjects();
		imgui_initialized = true;

		SetupImGuiStyle2();
	}
	dev->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFF);
}

void render::endscene(LPDIRECT3DDEVICE9 dev)
{
	init_imgui(dev);
	auto& io = ImGui::GetIO();

	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (openhud->want_input)
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
		CJOpenHud* openhud = CJOpenHud::get_instance();

		if (openhud && openhud->inst_hooks) //remove the old hooks
		{
			if (openhud->inst_hooks->hook_map.find("EndScene") != openhud->inst_hooks->hook_map.end())
				openhud->inst_hooks->hook_map["EndScene"]->remove();
			if (openhud->inst_hooks->hook_map.find("Reset") != openhud->inst_hooks->hook_map.end())
				openhud->inst_hooks->hook_map["Reset"]->remove();
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
	CJOpenHud* openhud = CJOpenHud::get_instance();
	if (openhud && openhud->inst_hooks)
	{
		openhud->inst_hooks->hook_map["InitGraphics"]->remove(); //remove hook here in case of a race condition on destructors
		openhud->inst_hooks->hook_map["EndScene"]->remove(); //remove hook here in case of a race condition on destructors
		openhud->inst_hooks->hook_map["Reset"]->remove(); //remove hook here in case of a race condition on destructors
	}
	ImGui::DestroyContext();
}