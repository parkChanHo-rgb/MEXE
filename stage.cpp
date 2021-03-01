#include "stdafx.h"
#include "stage.h"

HRESULT stage::init()
{
	IMAGEMANAGER->addImage("스테이지", "image/stage.bmp", WINSIZEX, 312, false, RGB(255,0,255));
	
	
	
	
	
	
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
	IMAGEMANAGER->render("스테이지", getMemDC(), 0, WINSIZEY-312);

	
}