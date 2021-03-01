#include "stdafx.h"
#include "enemy.h"
#include "player.h"

HRESULT enemy::init()
{
	IMAGEMANAGER->addFrameImage("미니언", "image/enemy/enemyidle.bmp", 108, 108, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미니언공격", "image/enemy/enemyattack.bmp", 972, 108, 9, 1, true, RGB(255, 0, 255));
	

	_enemy = IMAGEMANAGER->findImage("미니언");

	x = WINSIZEX - (1024 / 6 * 1.5);
	y = WINSIZEY - 156;

	_state = E_IDLE;
	_currentHP = _maxHP = 100;

	_count = _index = 0;

	_isDead = false;


	
		_eBullet = new enemyBullet;
		_eBullet->init(50, WINSIZEX);


		_eHpBar = new enemyProgressBar;
		_eHpBar->init(_rc.left - 85, _rc.top - 54, 170, 16);
		_eHpBar->setGauge(_currentHP, _maxHP);

		_rndCount = RND->getFromIntTo(150, 200);
		_actCount = 0;
		_rndMoveCount = RND->getFromIntTo(1, 3);
		_moveCount = 0;
	

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	
		actionCount();
		action();
		setState();
		collision();
		_eBullet->update();

		_eHpBar->setX(_rc.left - 58);
		_eHpBar->setY(_rc.top - 54);
		_eHpBar->setGauge(_currentHP, _maxHP);
		_eHpBar->update();

		if (_currentHP <= 0)
		{
			_isDead = true;
			
		}

		if (_isDead)
		{
			x = 40000;
			y = 40000;
		}
	
		if (_boss->getIsSummon())
		{
			_isDead = false;
		}
}

void enemy::render()
{
	
		_eHpBar->render();
		_enemy->frameRender(getMemDC(), _rc.left - 27, _rc.top - 54);
		_eBullet->render();

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _rc);
		}
	
	

}

void enemy::action()
{
	
		_rc = RectMakeCenter(x, y, 50, 50);

		if (actionCount())
		{
			if (_state == E_IDLE && (_player->getRC().bottom < _rc.top))
			{
				y -= 104;
			}

			if (_state == E_IDLE && (_player->getRC().top > _rc.bottom))
			{
				y += 104;
			}

			if (_state == E_IDLE && (_player->getRC().bottom >= _rc.top && _player->getRC().top <= _rc.bottom))
			{
				if (_rndMoveCount == 1)
				{
					_rndMoveCount = RND->getFromIntTo(1, 4);
					_state = E_ATTACK;
					_eBullet->fire(_rc.left - 20, (_rc.top + _rc.bottom) / 2);
				}

				if (_rndMoveCount == 2)
				{
					_rndMoveCount = RND->getFromIntTo(1, 4);
					if (_rc.left <= 600) return;
					x -= 1024 / 6;
				}

				if (_rndMoveCount == 3)
				{
					_rndMoveCount = RND->getFromIntTo(1, 4);
					if (_rc.right >= 800) return;
					x += 1024 / 6;
				}

			}

		}
	

}

bool enemy::actionCount()
{
	
		_actCount++;

		if (_actCount % _rndCount == 0)
		{
			_actCount = 0;
			_rndCount = RND->getFromIntTo(150, 200);

			return true;
		}

		return false;
	
}

void enemy::setState()
{
	
		_count++;
		if (_count % 5);
		{
			switch (_state)
			{
			case E_IDLE:
				_enemy = IMAGEMANAGER->findImage("미니언");
				_index = 0;
				_enemy->setFrameY(0);
				_enemy->setFrameX(_index);
				break;
			case E_ATTACK:
				_enemy = IMAGEMANAGER->findImage("미니언공격");
				if (_index >= 9)  _state = E_IDLE;
				_enemy->setFrameY(0);
				_enemy->setFrameX(_index);
				_index++;
				break;
			}
			_count = 0;
		}
	
}

void enemy::collision()
{
	
		for (int i = 0; i < _eBullet->getVBullet().size(); ++i)
		{
			RECT temp;
			if (IntersectRect(&temp,
				&_eBullet->getVBullet()[i].rc,
				&_player->getRC())
				&& !_player->getIsInvisible())
			{
				EFFECTMANAGER->play("히트", (_player->getRC().left + _player->getRC().right) / 2, _player->getRC().top - 25);
				_eBullet->removeBullet(i);
				_player->hitDamage(5);
				break;
			}
		}
	
}

void enemy::hitDamage(float damage)
{
	
	_currentHP -= damage;
	
}



HRESULT boss::init()
{
	IMAGEMANAGER->addFrameImage("에어맨", "image/airman/airmanidle.bmp", 225, 213, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에어맨공격", "image/airman/airmanattack.bmp", 1350, 213, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에어맨이동", "image/airman/airmanmove.bmp", 675, 213, 3, 1, true, RGB(255, 0, 255));

	_boss = IMAGEMANAGER->findImage("에어맨");

	x = 50000;
	y = 50000;

	//x = WINSIZEX - (1024 / 6 * 1.5);
	//y = WINSIZEY - 260;

	_state = B_IDLE;

	_currentHP = _maxHP = 500;

	_eBullet = new enemyBullet;
	_eBullet->init(50, WINSIZEX);

	_sBullet = new specialBullet;
	_sBullet->init(100, WINSIZEX);

	_fBullet = new finishBullet;
	_fBullet->init(100, 100);

	_eHpBar = new enemyProgressBar;
	_eHpBar->init(_rc.left, _rc.top, 170, 16);
	_eHpBar->setGauge(_currentHP, _maxHP);

	_rndCount = RND->getFromIntTo(200, 300);
	_rndMoveCount = RND->getFromIntTo(1, 4);
	_actCount = 0;
	_moveCount = 0;
	_specialCount = 0;
	_finishCount = 0;
	_actionCount = 0;  
	_actionIndex = 0;
	_attackCount = 0;
	_attackIndex = 0;


	return S_OK;
}



void boss::release()
{
}

void boss::update()
{	
	
	
	if (_enemy->getIsDead())
	{
		x = WINSIZEX - (WINSIZEX / 6 * 1.5);
		y = WINSIZEY - 156;

		_isSummon = true;
	 }

	_rc = RectMake(x, y, 50, 52);

	
	actionCount();
	action();
	setState();
	collision();
	_eBullet->update();
	_sBullet->update();
	_fBullet->update();
	
	_eHpBar->setX(_rc.left - 50);
	_eHpBar->setY(_rc.top - 180);
	_eHpBar->setGauge(_currentHP, _maxHP);
	_eHpBar->update();


	if (_currentHP <= 0)
	{
		SCENEMANAGER->changeScene("게임클리어");
	}
	

}

void boss::render()
{
	_eHpBar->render();
	_boss->frameRender(getMemDC(), _rc.left - 100, _rc.top - 162);
	_eBullet->render();
	_sBullet->render();
	_fBullet->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	
}

void boss::action()
{
	_rc = RectMakeCenter(x, y, 50, 52);
	_specialCount++;
	_finishCount++;
	if (actionCount())
	{
		if ((_state == B_IDLE || _state == B_MOVE )&& (_player->getRC().bottom < _rc.top))
		{
			y -= 104;
			_state = B_MOVE;
		}

		if ((_state == B_IDLE || _state == B_MOVE) && (_player->getRC().top > _rc.bottom))
		{
			y += 104;
			_state = B_MOVE;
		}

		if (_state == B_IDLE && (_player->getRC().bottom >= _rc.top && _player->getRC().top <= _rc.bottom))
		{
			if (_rndMoveCount == 1)
			{
				_rndMoveCount = RND->getFromIntTo(1, 4);
				_state = B_ATTACK;
				_eBullet->fire(_rc.left - 20, (_rc.top + _rc.bottom) / 2);
				
			}

			if (_rndMoveCount == 2)
			{
				_rndMoveCount = RND->getFromIntTo(1, 4);
				_state = B_MOVE;
				if (_rc.left <= 600) return;
				x -= 1024 / 6;
			}

			if (_rndMoveCount == 3)
			{
				_rndMoveCount = RND->getFromIntTo(1, 4);
				_state = B_MOVE;
				if (_rc.right >= 800) return;
				x += 1024 / 6;
			}


			if (_finishCount >= 200)
			{
			_state = B_ATTACK;
			_fBullet->fire((WINSIZEX / 6) * 0.5, WINSIZEY - 260);
			_fBullet->fire((WINSIZEX / 6) * 2.5, WINSIZEY - 260);
			_fBullet->fire((WINSIZEX / 6) * 1.5, WINSIZEY - 156);
			_fBullet->fire((WINSIZEX / 6) * 0.5, WINSIZEY - 52);
			_fBullet->fire((WINSIZEX / 6) * 2.5, WINSIZEY - 52);
			_finishCount = 0;
			}
			if (_specialCount >= 30)
			{
				_state = B_ATTACK;
				_sBullet->fire(WINSIZEX - (WINSIZEY / 6 * 2.5f), WINSIZEY - 260);
				_sBullet->fire(WINSIZEX, WINSIZEY - 156);
				_sBullet->fire(WINSIZEX - (WINSIZEY / 6 * 2.5f), WINSIZEY - 52);
				_specialCount = 0;
				
				
			}

			

		}			
		
	}

}

bool boss::actionCount()
{
	
	_actCount++;

	if (_actCount % _rndCount == 0)
	{
		_actCount = 0;
		_rndCount = RND->getFromIntTo(200, 300);

		return true;
	}

	return false;
}

void boss::setState()
{
	_actionCount++;
	_attackCount++;

	if (_actionCount % 1 == 0)
	{
		switch (_state)
		{
		case B_IDLE:
			_boss = IMAGEMANAGER->findImage("에어맨");
			_actionIndex = 0;
			_attackIndex = 0;
			_boss->setFrameY(0);
			_boss->setFrameX(_actionIndex);
			break;
		case B_MOVE:
			_boss = IMAGEMANAGER->findImage("에어맨이동");
			if (_actionIndex >= 3) _state = B_IDLE;
			_boss->setFrameY(0);
			_boss->setFrameX(_actionIndex);
			_actionIndex++;
			break;
		}
		_actionCount = 0;
	}

	if (_attackCount % 5 == 0)
	{
		switch (_state)
		{
		case B_ATTACK:
			_boss = IMAGEMANAGER->findImage("에어맨공격");
			if (_attackIndex >= 6) _state = B_IDLE;
			_boss->setFrameY(0);
			_boss->setFrameX(_attackIndex);
			_attackIndex++;
			break;
		}
		_attackCount = 0;
	}

}

void boss::collision()
{


	for (int i = 0; i < _eBullet->getVBullet().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp,
			&_eBullet->getVBullet()[i].rc,
			&_player->getRC())
			&& !_player->getIsInvisible())
		{
			EFFECTMANAGER->play("히트", (_player->getRC().left + _player->getRC().right) / 2, _player->getRC().top - 25);
			_eBullet->removeBullet(i);
			_player->hitDamage(5);
			break;
		}
	}

	for (int i = 0; i < _sBullet->getVBullet().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp,
			&_sBullet->getVBullet()[i].rc,
			&_player->getRC())
			&& !_player->getIsInvisible())
		{
			EFFECTMANAGER->play("히트", (_player->getRC().left + _player->getRC().right) / 2, _player->getRC().top - 25);
			_sBullet->removeBullet(i);
			_player->hitDamage(10);
			break;
		}
	}

	for (int i = 0; i < _fBullet->getVBullet().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp,
			&_fBullet->getVBullet()[i].rc,
			&_player->getRC())
			&& !_player->getIsInvisible())
		{
			EFFECTMANAGER->play("히트", (_player->getRC().left + _player->getRC().right) / 2, _player->getRC().top - 25);
			_fBullet->removeBullet(i);
			_player->hitDamage(20);
			break;
		}
	}

}

void boss::hitDamage(float damage)
{
	_currentHP -= damage;
}

