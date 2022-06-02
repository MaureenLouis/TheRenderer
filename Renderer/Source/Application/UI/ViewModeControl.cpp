#include "stdafx.h"
#include "ViewModeControl.h"
#include "Renderer/RendererCore/Renderer.h"

void ViewmodeControl::draw()
{
	    ImGui::Begin("View control");
	    int& trackMode = RenderGlobal::get()._trackMode;
	    ImGui::RadioButton("Rotate", &trackMode, 0), ImGui::SameLine();
	    ImGui::RadioButton("Scale", &trackMode, 1), ImGui::SameLine();
	    ImGui::RadioButton("Pan", &trackMode, 2), ImGui::SameLine();
	    ImGui::RadioButton("Select", &trackMode, 3);
	    ImGui::End();


	    ImGui::Begin("Polygon mode");
	    int& polygonMode = Config::get()._polygonMode;
		ImGui::RadioButton("Fill", &polygonMode, 0), ImGui::SameLine();
		ImGui::RadioButton("Line", &polygonMode, 1);
		ImGui::End();

		Renderer::setPolygonMode(Config::PolygonMode(polygonMode));

}


void DisplaySettings::draw()
{
	ImGui::Begin("Display settings");
	
	ImGui::Begin("Resolution");
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



			ImGui::Begin("AntiAlaising");
		
			int chosen = 0;

			int& antiAlaisingLevel = Config::get().antiAlaisingLevel();
			if (antiAlaisingLevel == 0)
			{
				chosen = 0;
			}
			else if (antiAlaisingLevel == 2)
			{
				chosen = 1;

			}
			else if (antiAlaisingLevel == 4)
			{
				chosen = 2;

			}
			else if (antiAlaisingLevel == 8)
			{
				chosen = 3;

			}
			else if (antiAlaisingLevel == 16)
			{
				chosen = 4;
			}


			ImGui::RadioButton("close", &chosen, 0);
			ImGui::RadioButton("2x", &chosen, 1);
			ImGui::RadioButton("4x", &chosen, 2);
			ImGui::RadioButton("8x", &chosen, 3);
			ImGui::RadioButton("16x", &chosen, 4);

			if (chosen == 0)
			{
				antiAlaisingLevel = 0;
			}
			else if (chosen == 1)
			{
				antiAlaisingLevel = 2;
			}
			else if (chosen == 2)
			{
				antiAlaisingLevel = 4;
			}
			else if (chosen == 3)
			{
				antiAlaisingLevel = 8;
			}
			else if (chosen == 4)
			{
				antiAlaisingLevel = 16;
			}

			ImGui::End();
		

	    ImGui::End();
}

bool MenuBar::_showPreferenceWidget = false;

void MenuBar::draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			drawFileMenu();

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			drawEditMenu();

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void MenuBar::drawFileMenu()
{
	if (ImGui::MenuItem("Close"))
	{
	
	}
}

void MenuBar::drawEditMenu()
{
	if (ImGui::MenuItem("Preference"))
	{
		_showPreferenceWidget = true;
	}

#if 0
	if (_showPreferenceWidget)
	{
		static const Config::VideoModes& videoModes = Config::get().videoModes();
		static std::vector<const char*> videoModesStrList;
		videoModesStrList.clear();

		for (auto iter = videoModes.begin(); iter != videoModes.end(); iter++)
		{
			int width = iter->width;
			int height = iter->height;
			int refreshRate = iter->refreshRate;
			static char buf[32] = { 0 };
			sprintf(buf, "%dx%d@%dHz", width, height, refreshRate);
			videoModesStrList.push_back(buf);
		}

		int currentVideoMode = Config::get().defaultVideoMode();

		ImGui::Begin("Preference");
		ImGui::ListBox("listbox", &currentVideoMode, videoModesStrList.data(), videoModesStrList.size(), 4);
		ImGui::SameLine();
		ImGui::End();

		Config::get().setDefaultVideoMode(currentVideoMode);
	}

#endif
}

