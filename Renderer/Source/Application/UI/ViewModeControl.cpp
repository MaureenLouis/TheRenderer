#include "stdafx.h"
#include "ViewModeControl.h"

void ViewmodeControl::draw()
{
	ImGui::Begin("View control");

	int& trackMode = RenderGlobal::get()._trackMode;
	ImGui::RadioButton("Rotate", &trackMode, 0), ImGui::SameLine();
	ImGui::RadioButton("Scale", &trackMode, 1), ImGui::SameLine();
	ImGui::RadioButton("Pan", &trackMode, 2), ImGui::SameLine();
	ImGui::RadioButton("Select", &trackMode, 3);
	ImGui::End();
}


void DisplaySettings::draw()
{
	ImGui::Begin("Display settings");

	const Config::VideoModes& videoModes = Config::get().videoModes();
	int currentVideoMode = Config::get().defaultVideoMode();

	int i = 0;
	for (auto iter = videoModes.begin(); iter != videoModes.end(); iter++, i++)
	{
		int width = iter->width;
		int height = iter->height;
		int refreshRate = iter->refreshRate;
		static char buf[32] = { 0 };
		sprintf(buf, "%dx%d@%dHz", width, height, refreshRate);
		ImGui::RadioButton(buf, &currentVideoMode, i);
	}
	
	Config::get().setDefaultVideoMode(currentVideoMode);

	ImGui::End();

}
