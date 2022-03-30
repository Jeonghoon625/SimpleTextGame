#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"

bool Initialize()
{
	if (false == InitializeRenderer())
	{
		return false;
	}

	return true;
}

void processInput()
{

}

void update()
{


}

void render()
{
	RenderMap();
}

int32_t Run()
{
	// Game Loop => �÷��̾�κ����� �Է��� �ϵ����� �и���Ų��.
	
	// Game Loop�� ��ü�� Frame
	while (true)
	{
		// �Է�ó��
		processInput();
		// ������Ʈ
		update();
		// ������
		render();
	}
}