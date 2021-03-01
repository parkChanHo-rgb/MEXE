#include "stdafx.h"
#include "battleStage.h"
#include "player.h"
#include "enemy.h"



HRESULT battleStage::init()
{
	EFFECTMANAGER->addEffect("히트", "image/hiteffect.bmp", 3672, 210, 204, 210, 5.0f, 0.2f, 100);
	IMAGEMANAGER->addImage("배경", "image/background.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	




	_stage.init();
	_player = new player;
	_player->init();
	
	
	_enemy = new enemy;
	_enemy->init();

	_boss = new boss;
	_boss->init();

	loopX = loopY = 0;

	_player->setEnemyMemoryAddressLink(_enemy);
	_player->setBossMemoryAddressLink(_boss);
	_enemy->setPlayerMemoryAddressLink(_player);
	_enemy->setBossMemoryAddressLink(_boss);
	_boss->setPlayerMemoryAddressLink(_player);
	_boss->setEmenyMemoryAddressLink(_enemy);
	

	return S_OK;
}

void battleStage::release()
{
	_stage.release();
	_player->release();
	_enemy->release();
	_boss->release();
	
}

void battleStage::update()
{
	_stage.update();
	_player->update();
	_enemy->update();
	_boss->update();

	EFFECTMANAGER->update();
	loopX -= 5;
	loopY -= 5;

}

void battleStage::render()
{
	
	IMAGEMANAGER->findImage("배경")->loopRender(getMemDC(), &RectMake(0, 0, 1024, 768), loopX, loopY);
	_stage.render();
	_player->render();
	_enemy->render();
	_boss->render();
	EFFECTMANAGER->render();
}
