#include "stdafx.h"
#include "gameoverScene.h"



HRESULT gameoverScene::init()
{
	IMAGEMANAGER->addImage("���ӿ���", "image/gameover.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	return S_OK;
}

void gameoverScene::release()
{
}

void gameoverScene::update()
{
}

void gameoverScene::render()
{
	IMAGEMANAGER->findImage("���ӿ���")->render(getMemDC());
}
