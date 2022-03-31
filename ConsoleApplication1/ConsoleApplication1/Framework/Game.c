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
	//// 0.5�� �������� Ư�� �޼����� �����̱�.
	//static float store_deltaTime = 0.0;
	//
	//float flikerTime = 0.5;

	//if (store_deltaTime >= flikerTime)
	//{
	//	SetMessage("ŷ�����۷�");
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
	// Game Loop => �÷��̾�κ����� �Է��� �ϵ����� �и�, 
	// �̷��� �Է�ó���� ������Ʈ, �������� ������ ������ �����Ѵ�. 
	// https://www.gameprogrammingpatterns.com/game-loop.html

	while (true)
	{
		//������ ���� ----- ���� ������ ����
		// ��
		UpdateTimer();
		// �Է� ó��
		processInput();
		// ������Ʈ
		update();
		// ������
		render();
	}
}