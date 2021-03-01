#include "stdafx.h"
#include "gameclearScene.h"

HRESULT gameclearScene::init()
{
	IMAGEMANAGER->addImage("게임클리어", "image/gameclear.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	return S_OK;
}

void gameclearScene::release()
{
}

void gameclearScene::update()
{
}

void gameclearScene::render()
{
	IMAGEMANAGER->findImage("게임클리어")->render(getMemDC());
}
