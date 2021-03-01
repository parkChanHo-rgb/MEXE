#include "stdafx.h"
#include "player.h"
#include "stage.h"
#include "item.h"
#include "enemy.h"



HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("대기", "image/idle.bmp", 110, 238, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("이동", "image/move.bmp", 536, 238, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("기본공격", "image/attack.bmp", 1131, 238, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐논공격", "image/cannon.bmp", 2493, 238, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스프레드공격", "image/spread.bmp", 1200, 238, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기본", "image/idlestate.bmp", 108, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빈사", "image/damedstate.bmp", 108, 40, true, RGB(255, 0, 255));

	_emotion = IMAGEMANAGER->findImage("기본");

	_player = IMAGEMANAGER->findImage("대기");
	x = 1024 / 6 * 1.5;
	y = WINSIZEY - 156;

	_bullet = new normalBullet;
	_bullet->init(20, WINSIZEX);

	_cannonBullet = new cannonBullet;
	_cannonBullet->init(10, WINSIZEX);

	_spreadBullet = new spreadBullet;
	_spreadBullet->init(100, 0, WINSIZEX);

	_item = new item;
	_item->init();

	_moveCount = _moveIndex = 0;
	_attackCount = _attackIndex = 0;
	state = IDLE;

	_isInvisible = false;
	_invisibleCount = 0;

	_currentHP = _maxHP = 100;

	_hpBar = new progressBar;
	_hpBar->init(108, -20, 425, 40);
	_hpBar->setGauge(_currentHP, _maxHP);
	
	return S_OK;
}

void player::release()
{

}

void player::update()
{
	_bullet->update();
	_cannonBullet->update();
	_spreadBullet->update();
	action();
	setState();
	collision();
	_item->update();

	_hpBar->setX(108);
	_hpBar->setY(-20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	if (_currentHP < 40.0f)
	{
		_emotion = IMAGEMANAGER->findImage("빈사");
	}

	if (_currentHP <= 0)
	{
		SCENEMANAGER->changeScene("게임오버");
	}

}


void player::render()
{
	_emotion->render(getMemDC());
	_hpBar->render();
	_bullet->render();
	_cannonBullet->render();
	_spreadBullet->render();
	if (_isInvisible && _invisibleCount % 5 == 0 && _invisibleCount > 1)
	{
		_player->alphaFrameRender(getMemDC(), _rc.left - 30, _rc.top - 186, 1, 1, 255);
	}
	else 
	{
		_player->frameRender(getMemDC(), _rc.left - 30, _rc.top - 186);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{ 
	Rectangle(getMemDC(), _rc);
	}
	_item->render();
	
}

void player::action()
{	
	
	_rc = RectMakeCenter(x, y, 50, 50);

	
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _rc.right < WINSIZEX / 2 - 100 && state == IDLE) { x += 1024 / 6; state = MOVE; }

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _rc.left > 100 && state == IDLE) { x -= 1024 / 6; state = MOVE; }

		if (KEYMANAGER->isOnceKeyDown(VK_UP) && _rc.top > WINSIZEY - 250 && state == IDLE) { y -= 104; state = MOVE; }

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _rc.top < WINSIZEY - 150 && state == IDLE) { y += 104; state = MOVE; }
	
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && (state == IDLE || state == ATTACK)) { _bullet->fire(_rc.right + 20, (_rc.top + _rc.bottom) / 2); state = ATTACK; }

		if (KEYMANAGER->isOnceKeyDown('Z') && state == IDLE)
		{
			if (_item->getItem() == CANNON)
			{
				
				_cannonBullet->fire(_rc.right + 20, (_rc.top + _rc.bottom) / 2);
				state = CANNONATTACK;
			}

			if (_item->getItem() == SPREAD)
			{
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 4, (PI / 30 * -4));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 3, (PI / 30 * -3));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 2, (PI / 30 * -2));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 1, (PI / 30 * -1));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 0, (PI / 30 * 0));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 1, (PI / 30 * 1));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 2, (PI / 30 * 2));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 3, (PI / 30 * 3));
				_spreadBullet->fire(_rc.right + 20, ((_rc.top + _rc.bottom) / 2) + 4, (PI / 30 * 4));
				
				state = SPREADATTACK;
			}

			if (_item->getItem() == INVISIBLE)
			{
				_isInvisible = true;
				_invisibleCount = 300;
			}
		}

		if (_isInvisible)
		{
			_invisibleCount--;
		}

		if (_invisibleCount <= 0)
		{
			_isInvisible = false;
			_invisibleCount = 0;
			
		}
}

void player::setState()
{
	_moveCount++;
	_attackCount++;
	if (_moveCount % 1 == 0)
	{
		switch (state)
		{
		case IDLE:
			_player = IMAGEMANAGER->findImage("대기");
			_moveIndex = 0;
			_attackIndex = 0;
			_player->setFrameY(0);
			_player->setFrameX(_moveIndex);
			break;
		case MOVE:
			_player = IMAGEMANAGER->findImage("이동");
			if (_moveIndex >= 6) state = IDLE;
			_player->setFrameY(0);
			_player->setFrameX(_moveIndex);
			_moveIndex++;
			break;
		} 
		_moveCount = 0;
	}

	if (_attackCount % 3 == 0)
	{ 
		switch (state)
		{
			case ATTACK:
			_player = IMAGEMANAGER->findImage("기본공격");
			if (_attackIndex >= 5) state = IDLE;
			_player->setFrameY(0);
			_player->setFrameX(_attackIndex);
			_attackIndex++;
			break;
			case CANNONATTACK:
			_player = IMAGEMANAGER->findImage("캐논공격");
			if (_attackIndex >= 9) state = IDLE;
			_player->setFrameY(0);
			_player->setFrameX(_attackIndex);
			_attackIndex++;
			break;
			case SPREADATTACK:
			_player = IMAGEMANAGER->findImage("스프레드공격");
			if (_attackIndex >= 5) state = IDLE;
			_player->setFrameY(0);
			_player->setFrameX(_attackIndex);
			_attackIndex++;
			break;
		}
		_attackCount = 0;
	}
}

void player::collision()
{
	
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		
			RECT temp;
			if (IntersectRect(&temp,
				&_bullet->getVBullet()[i].rc,
				&_enemy->getRect()))
			{
				EFFECTMANAGER->play("히트", (_enemy->getRect().left + _enemy->getRect().right) / 2, _enemy->getRect().top);
				_bullet->removeBullet(i);
				_enemy->hitDamage(3);
				break;
			}
		
	}

	for (int i = 0; i < _spreadBullet->getVBullet().size(); i++)
	{

		RECT temp;
		if (IntersectRect(&temp,
			&_spreadBullet->getVBullet()[i].rc,
			&_enemy->getRect()))
		{
			EFFECTMANAGER->play("히트", (_enemy->getRect().left + _enemy->getRect().right) / 2, _enemy->getRect().top);
			_spreadBullet->removeBullet(i);
			_enemy->hitDamage(5);
			break;
		}

	}

	for (int i = 0; i < _cannonBullet->getVBullet().size(); i++)
	{

		RECT temp;
		if (IntersectRect(&temp,
			&_cannonBullet->getVBullet()[i].rc,
			&_enemy->getRect()))
		{
			EFFECTMANAGER->play("히트", (_enemy->getRect().left + _enemy->getRect().right) / 2, _enemy->getRect().top);
			_cannonBullet->removeBullet(i);
			_enemy->hitDamage(15);
			break;
		}

	}

	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{

		RECT temp;
		if (IntersectRect(&temp,
			&_bullet->getVBullet()[i].rc,
			&_boss->getRect()))
		{
			EFFECTMANAGER->play("히트", (_boss->getRect().left + _boss->getRect().right) / 2, _boss->getRect().top);
			_bullet->removeBullet(i);
			_boss->hitDamage(3);
			break;
		}

	}

	for (int i = 0; i < _spreadBullet->getVBullet().size(); i++)
	{

		RECT temp;
		if (IntersectRect(&temp,
			&_spreadBullet->getVBullet()[i].rc,
			&_boss->getRect()))
		{
			EFFECTMANAGER->play("히트", (_boss->getRect().left + _boss->getRect().right) / 2, _boss->getRect().top);
			_spreadBullet->removeBullet(i);
			_boss->hitDamage(5);
			break;
		}

	}

	for (int i = 0; i < _cannonBullet->getVBullet().size(); i++)
	{

		RECT temp;
		if (IntersectRect(&temp,
			&_cannonBullet->getVBullet()[i].rc,
			&_boss->getRect()))
		{
			EFFECTMANAGER->play("히트", (_boss->getRect().left + _boss->getRect().right) / 2, _boss->getRect().top);
			_cannonBullet->removeBullet(i);
			_boss->hitDamage(15);
			break;
		}

	}

}

void player::hitDamage(float damage)
{
	_currentHP -= damage;
}

