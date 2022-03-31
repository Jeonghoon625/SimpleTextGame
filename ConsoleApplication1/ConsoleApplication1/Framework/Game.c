#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"
#include "Input.h"
#include "Timer.h"

bool Initialize()
{
	if (false == InitializeRenderer())
	{
		return false;
	}

	InitializeTimer();

	return true;
}

void processInput()
{
	UpdateInput();
}

void update()
{
	//// 0.5초 간격으로 특정 메세지를 깜빡이기.
	//static float store_deltaTime = 0.0;
	//
	//float flikerTime = 0.5;

	//if (store_deltaTime >= flikerTime)
	//{
	//	SetMessage("킹갓엠퍼러");
	//	
	//}
	//
	//if (store_deltaTime >= flikerTime * 2)
	//{
	//	store_deltaTime = 0.0;
	//}
	//
	//store_deltaTime += GetDeltaTime();
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

	while (true)
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
}