#include "stdafx.h"
#include "Game.h"

bool Initialize()
{
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