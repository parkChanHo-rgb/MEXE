#include "stdafx.h"
#include "weapon.h"




HRESULT normalBullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void normalBullet::release()
{
}

void normalBullet::update()
{
	move();
}

void normalBullet::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
	
}

void normalBullet::fire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.speed = 20.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 10, 10);

	_vBullet.push_back(bullet);
	
}

void normalBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 10, 10);

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void normalBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT cannonBullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void cannonBullet::release()
{
}

void cannonBullet::update()
{
	move();
}

void cannonBullet::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
}

void cannonBullet::fire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.speed = 20.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 100, 100);

	_vBullet.push_back(bullet);
}

void cannonBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 100, 100);

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void cannonBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT spreadBullet::init(int bulletMax, float angle, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	_angle = angle;
	return S_OK;
}

void spreadBullet::release()
{
}

void spreadBullet::update()
{
	move();
}

void spreadBullet::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
}

void spreadBullet::fire(float x, float y, float angle)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.speed = 30;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 10, 10);

	_vBullet.push_back(bullet);
}

void spreadBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 10, 10);

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{        
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void spreadBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT enemyBullet::init(int bulletMax, float range)
{

	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void enemyBullet::release()
{
}

void enemyBullet::update()
{
	move();
}

void enemyBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), 
			_viBullet->rc.left, 
			_viBullet->rc.top - 38, 
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
}

void enemyBullet::fire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.bulletImage = new image;
	bullet.bulletImage->init("image/enemy/enemybullet.bmp", 240, 88, 3, 1, true, RGB(255, 0, 255));
	bullet.speed = 15;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 50, 50);

	_vBullet.push_back(bullet);
}

void enemyBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 50, 50);

		if (_range < getDistance(_viBullet->x, _viBullet->y,
			_viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void enemyBullet::removeBullet(int arrNum)
{
	SAFE_RELEASE(_vBullet[arrNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT specialBullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void specialBullet::release()
{
}

void specialBullet::update()
{
	move();
}

void specialBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top - 38,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
}

void specialBullet::fire(float x, float y)
{

	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.bulletImage = new image;
	bullet.bulletImage->init("image/airman/windbullet.bmp", 345, 96, 4, 1, true, RGB(255, 0, 255));
	bullet.speed = 20;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 50, 50);

	_vBullet.push_back(bullet);

}

void specialBullet::move()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 50, 50);

		if (_range < getDistance(_viBullet->x, _viBullet->y,
			_viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}

}

void specialBullet::removeBullet(int arrNum)
{
	SAFE_RELEASE(_vBullet[arrNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT finishBullet::init(int bulletMax, float duration)
{
	_bulletMax = bulletMax;
	_duration = duration;
	
	return S_OK;
}

void finishBullet::release()
{
}

void finishBullet::update()
{
	move();
}

void finishBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left - 30,
			_viBullet->rc.top - 162,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc);
		}
	}
}

void finishBullet::fire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.bulletImage = new image;
	bullet.bulletImage->init("image/airman/tornadobullet.bmp", 480, 195, 4, 1, true, RGB(255, 0, 255));
	bullet.speed = 0;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 50, 50);

	_vBullet.push_back(bullet);
}

void finishBullet::move()
{
	_duration--;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 50, 50);

		if (_duration <= 0)
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
			_duration = 100;
		}
		else ++_viBullet;
	}
}

void finishBullet::removeBullet(int arrNum)
{
	SAFE_RELEASE(_vBullet[arrNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + arrNum);
	
}
