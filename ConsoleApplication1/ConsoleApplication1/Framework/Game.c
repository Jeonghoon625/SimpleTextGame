#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"
#include "Input.h"

bool Initialize()
{
	if (false == InitializeRenderer())
	{
		return true;
	}
}

void processInput()
{
	UpdateInput();
}

void update()
{
	if (GetButton(KEYCODE_W))
	{
		SetKeyMessage(KEYCODE_W);
	}

	else if (GetButton(KEYCODE_A))
	{
		SetKeyMessage(KEYCODE_A);
	}

	else if (GetButton(KEYCODE_S))
	{
		SetKeyMessage(KEYCODE_S);
	}

	else if (GetButton(KEYCODE_D))
	{
		SetKeyMessage(KEYCODE_D);
	}
}

void render()
{
	RenderMap();

}
int32_t Run()
{
	// Game Loop => 플레이어로부터의 입력을 하드웨어와 분리시킨다.
	// https://www.gameprogrammingpatterns.com/game-loop.html

	while (true)
	{
		// 입력 처리
		processInput();
		// 업데이트
		update();
		// 렌더링
		render();
	}
}