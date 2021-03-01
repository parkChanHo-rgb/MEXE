#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("��Ʋȭ��", new battleStage);
	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
	SCENEMANAGER->addScene("���ӿ���", new gameoverScene);
	SCENEMANAGER->addScene("����Ŭ����", new gameclearScene);

	SCENEMANAGER->changeScene("Ÿ��Ʋ");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	
}

void playGround::update()
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("��Ʋȭ��");
	}


	
	SCENEMANAGER->update();

}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC());
	}
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

