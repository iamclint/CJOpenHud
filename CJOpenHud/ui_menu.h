#pragma once
class CJOpenHud;

class ui_menu
{
public:
	void menu(CJOpenHud* hud);
	ui_menu(CJOpenHud* hud);
	~ui_menu();
	void render();

	bool show_velocity = true;
	bool show_position = true;
	bool show_view = true;

	ImVec4 velocity_color = {0.f, 1.f ,0.f ,1.f};
};

