#pragma once
#include "gameNode.h"
#include "weapon.h"
#include "progressBar.h"


enum STATE
{
	IDLE,
	MOVE,
	ATTACK,
	CANNONATTACK,
	SPREADATTACK,
};

class item;
class enemy;
class boss;

class player :public gameNode
{
private:
	image* _player;
	image* _emotion;
	RECT _rc;
	int _moveCount, _moveIndex;
	int _attackCount, _attackIndex;
	BOOL _isInvisible;
	int _invisibleCount;
	float x, y;
	STATE state;
	item* _item;

	normalBullet* _bullet;
	cannonBullet* _cannonBullet;
	spreadBullet* _spreadBullet;

	enemy* _enemy;
	boss* _boss;

	float _currentHP, _maxHP;

	progressBar* _hpBar;

public:
	player() {};
	~player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void action();
	void setState();

	void collision();
	void hitDamage(float damage);

	void setEnemyMemoryAddressLink(enemy* enemy) { _enemy = enemy; }
	void setBossMemoryAddressLink(boss* boss) { _boss = boss; }

	image* getEmotion() { return _emotion; }
	inline BOOL getIsInvisible() { return _isInvisible; }
	inline RECT getRC() { return _rc; }
	normalBullet* getBullet() { return _bullet; }
	cannonBullet* getCannonBullet() { return _cannonBullet; }
	spreadBullet* getSpreadBullet() { return _spreadBullet; }
};

