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
	// Game Loop => �÷��̾�κ����� �Է��� �ϵ����� �и�, 
	// �̷��� �Է�ó���� ������Ʈ, �������� ������ ������ �����Ѵ�. 
	// https://www.gameprogrammingpatterns.com/game-loop.html

	while (!gameOver)
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

	return 0;
}