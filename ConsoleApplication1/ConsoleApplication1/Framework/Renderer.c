#include "stdafx.h"
#include "Renderer.h"

#define MAP_SIZE 24

static char s_map[MAP_SIZE][MAP_SIZE];
static HANDLE s_consoleHandle;

void clear()
{
	memset(s_map, ' ', sizeof(s_map));

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		s_map[i][MAP_SIZE - 1] = '\0';
	}
}

bool InitializeRenderer()
{
	s_consoleHandle = GetStdHandle
	(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE == s_consoleHandle)
	{
		return false;
	}

	return true;
}

void RenderMap()
{
	const static COORD initialPos = { 0 , 0 };
	const static CONSOLE_CURSOR_INFO info = { 100, false };

	SetConsoleCursorPosition(s_consoleHandle, initialPos);
	SetConsoleCursorInfo(s_consoleHandle, &info);

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		puts(s_map[i]);
	}

	// 출력 후에 현재 프레임을 지움.
	clear();
}

void SetKeyMessage(int keyCode)
{
	sprintf_s(s_map[0], sizeof(s_map[0]), "%c키가 눌림", keyCode);
}