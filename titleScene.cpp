#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	IMAGEMANAGER->addImage("Ÿ��Ʋ", "image/title.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
}

void titleScene::render()
{
	IMAGEMANAGER->findImage("Ÿ��Ʋ")->render(getMemDC());
}
