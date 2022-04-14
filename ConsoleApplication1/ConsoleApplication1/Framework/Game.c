#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"
#include "Input.h"
#include "Timer.h"
#include "Game/Stage.h"

extern bool gameOver;

bool Initialize()
{
	if (false == InitializeRenderer())
	{
		return false;
	}
	 
	InitializeTimer();
		
	LoadStage(STAGE_01);

	return true;
}

void processInput()
{
	UpdateInput();
}

void update()
{
	UpdateStage();
}	

void render()
{
	RenderMap();
}

int32_t Run()
{
	// Game Loop => 플레이어로부터의 입력을 하드웨어와 분리, 
	// 이러한 입력처리와 업데이트, 렌더링을 프레임 단위로 실행한다. 
	// https://www.gameprogrammingpatterns.com/game-loop.html

	while (!gameOver)
	{
		//프레임 시작 ----- 다음 프레임 시작
		// Δ
		UpdateTimer();
		// 입력 처리
		processInput();
		// 업데이트
		update();
		// 렌더링
		render();
	}

	return 0;
}