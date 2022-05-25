#pragma once

struct ViewmodeControl
{
	static void draw();
};

struct DisplaySettings
{
	static void draw();
};

struct MenuBar
{
	static void draw();

private:
	static void drawFileMenu();
	static void drawEditMenu();

	static bool _showPreferenceWidget;
};