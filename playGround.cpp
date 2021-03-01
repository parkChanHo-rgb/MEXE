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

	SCENEMANAGER->addScene("배틀화면", new battleStage);
	SCENEMANAGER->addScene("타이틀", new titleScene);
	SCENEMANAGER->addScene("게임오버", new gameoverScene);
	SCENEMANAGER->addScene("게임클리어", new gameclearScene);

	SCENEMANAGER->changeScene("타이틀");

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
		SCENEMANAGER->changeScene("배틀화면");
	}


	
	SCENEMANAGER->update();

}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC());
	}
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

