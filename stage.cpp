#include "stdafx.h"
#include "stage.h"

HRESULT stage::init()
{
	IMAGEMANAGER->addImage("��������", "image/stage.bmp", WINSIZEX, 312, false, RGB(255,0,255));
	
	
	
	
	
	
	return S_OK;
}

void stage::release()
{
	
}

void stage::update()
{
	

	
}

void stage::render()
{
	IMAGEMANAGER->render("��������", getMemDC(), 0, WINSIZEY-312);

	
}