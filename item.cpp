#include "stdafx.h"
#include "item.h"



HRESULT item::init()
{
	IMAGEMANAGER->addImage("칩셋", "image/chip.bmp", WINSIZEX / 2, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캐논칩", "image/chip/cannonchip.bmp", 400, 350, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스프레드칩", "image/chip/spreadchip.bmp", 400, 350, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인비저블칩", "image/chip/invisiblechip.bmp", 400, 350, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캐논칩설명", "image/chip/cannonintro.bmp", 400, 25, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스프레드칩설명", "image/chip/spreadintro.bmp", 400, 25, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인비저블칩설명", "image/chip/invisibleintro.bmp", 400, 25, false, RGB(255, 0, 255));
	

	_menu = IMAGEMANAGER->findImage("칩셋");
	_chip = IMAGEMANAGER->findImage("스프레드칩");
	_intro = IMAGEMANAGER->findImage("스프레드칩설명");
	_item = SPREAD;




	return S_OK;
}

void item::release()
{
}

void item::update()
{
	switch (_item)
	{
	case CANNON:
		if (KEYMANAGER->isOnceKeyDown('A')) { _item = INVISIBLE; }
		if (KEYMANAGER->isOnceKeyDown('D')) { _item = SPREAD; }
		_chip = IMAGEMANAGER->findImage("캐논칩");
		_intro = IMAGEMANAGER->findImage("캐논칩설명");
		break;
	case SPREAD:
		if (KEYMANAGER->isOnceKeyDown('A')) { _item = CANNON; }
		if (KEYMANAGER->isOnceKeyDown('D')) { _item = INVISIBLE; }
		_chip = IMAGEMANAGER->findImage("스프레드칩");
		_intro = IMAGEMANAGER->findImage("스프레드칩설명");
		break;
	case INVISIBLE:
		if (KEYMANAGER->isOnceKeyDown('A')) { _item = SPREAD; }
		if (KEYMANAGER->isOnceKeyDown('D')) { _item = CANNON; }
		_chip = IMAGEMANAGER->findImage("인비저블칩");
		_intro = IMAGEMANAGER->findImage("인비저블칩설명");
		break;
	}
}

void item::render()
{
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_menu->render(getMemDC());
		_chip->render(IMAGEMANAGER->findImage("칩셋")->getMemDC(), 56, 27);
		_intro->render(IMAGEMANAGER->findImage("칩셋")->getMemDC(), 50, 420);
		
	}
}
