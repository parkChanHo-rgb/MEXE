#include "stdafx.h"
#include "item.h"



HRESULT item::init()
{
	IMAGEMANAGER->addImage("Ĩ��", "image/chip.bmp", WINSIZEX / 2, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ��Ĩ", "image/chip/cannonchip.bmp", 400, 350, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������Ĩ", "image/chip/spreadchip.bmp", 400, 350, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ�����Ĩ", "image/chip/invisiblechip.bmp", 400, 350, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ��Ĩ����", "image/chip/cannonintro.bmp", 400, 25, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������Ĩ����", "image/chip/spreadintro.bmp", 400, 25, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ�����Ĩ����", "image/chip/invisibleintro.bmp", 400, 25, false, RGB(255, 0, 255));
	

	_menu = IMAGEMANAGER->findImage("Ĩ��");
	_chip = IMAGEMANAGER->findImage("��������Ĩ");
	_intro = IMAGEMANAGER->findImage("��������Ĩ����");
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
		_chip = IMAGEMANAGER->findImage("ĳ��Ĩ");
		_intro = IMAGEMANAGER->findImage("ĳ��Ĩ����");
		break;
	case SPREAD:
		if (KEYMANAGER->isOnceKeyDown('A')) { _item = CANNON; }
		if (KEYMANAGER->isOnceKeyDown('D')) { _item = INVISIBLE; }
		_chip = IMAGEMANAGER->findImage("��������Ĩ");
		_intro = IMAGEMANAGER->findImage("��������Ĩ����");
		break;
	case INVISIBLE:
		if (KEYMANAGER->isOnceKeyDown('A')) { _item = SPREAD; }
		if (KEYMANAGER->isOnceKeyDown('D')) { _item = CANNON; }
		_chip = IMAGEMANAGER->findImage("�κ�����Ĩ");
		_intro = IMAGEMANAGER->findImage("�κ�����Ĩ����");
		break;
	}
}

void item::render()
{
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_menu->render(getMemDC());
		_chip->render(IMAGEMANAGER->findImage("Ĩ��")->getMemDC(), 56, 27);
		_intro->render(IMAGEMANAGER->findImage("Ĩ��")->getMemDC(), 50, 420);
		
	}
}
