#include "stdafx.h"
#include "Renderer.h"
#include "Game/Stage.h"

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
	//콘솔 프로세스는 핸들을 사용하여 콘솔의 입력 및 화면 버퍼에 엑세스한다.
	// GetStdHandle 함수는 프로세스와 관련된 표준 입출력 및 오류 핸들의 검색 등의 기능을 제공한다.
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 윈도우즈 핸들은 INVALID_HANDLE_VALUE값으로 유효값을 판단한다.
	// 일반적으로 NULL값을 통해 값의 유효를 판단하는 것처럼...
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
	
	const char** stage = GetMap();
	memcpy(s_map, stage, sizeof(s_map));
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		puts(s_map[i]);
	}

	// 출력 후에 현재 프레임을 지움.
	clear();
}