#include "stdafx.h"
#include "gameclearScene.h"

HRESULT gameclearScene::init()
{
	IMAGEMANAGER->addImage("����Ŭ����", "image/gameclear.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

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
	IMAGEMANAGER->findImage("����Ŭ����")->render(getMemDC());
}
