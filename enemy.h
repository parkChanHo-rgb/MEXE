#pragma once
#include "gameNode.h"
#include "enemyProgressBar.h"
#include "weapon.h"



enum ENEMYSTATE
{
	E_IDLE,
	E_ATTACK,
};

enum BOSSSTATE
{
	B_IDLE,
	B_MOVE,
	B_ATTACK

};



class player;
class boss;
class enemy;

class enemy : public gameNode
{
private:
	image*	_enemy;			//���� �̹���
	RECT	_rc;			//���� ��Ʈ
	float x, y;

	int		_rndCount;		// ������ ī��Ʈ
	int		_actCount;		// �ൿ ����� ī��Ʈ
	int		_rndMoveCount;	// ���� �����ӿ� ī��Ʈ
	int		_moveCount;		// ������� ���� ��������� ī��Ʈ
	int		_count, _index; // �����ӷ����� ī��Ʈ �ε���

	bool _isDead;

	enemyBullet* _eBullet;
	ENEMYSTATE _state;
	player* _player;
	boss* _boss;
	enemyProgressBar* _eHpBar;

	float _currentHP, _maxHP;

	

public:
	enemy() {};
	~enemy() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void action();
	bool actionCount();
	void setState();
	void collision();
	void hitDamage(float damage);

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setBossMemoryAddressLink(boss* boss) { _boss = boss; }

	inline RECT getRect() { return _rc; }
	bool &getIsDead() { return _isDead; }
	

};

class boss : public gameNode
{
private:
	image*	_boss;			
	RECT	_rc;	
	int		_rndCount;
	int		_actCount;		
	int		_rndMoveCount;	// ���� �ൿ�� ī��Ʈ
	int		_moveCount;		// ���� �ൿ�� ī��Ʈ	
	int		_specialCount;	// Ư�� ���ݿ� ī��Ʈ
	int		_finishCount;	// �ʻ��� ī��Ʈ
	float x, y;
	int _actionCount, _actionIndex; // ������ ������ ������ ī��Ʈ �ε���
	int _attackCount, _attackIndex; // ���� ������ ������ ī��Ʈ �ε���
	BOOL _isDead;
	bool _isSummon;
	enemyBullet* _eBullet;
	specialBullet* _sBullet;
	finishBullet* _fBullet;
	BOSSSTATE _state;
	player* _player;
	enemy* _enemy;
	enemyProgressBar* _eHpBar;

	float _currentHP, _maxHP;

public:
	boss() {};
	~boss() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void action();
	bool actionCount();
	void setState();
	void collision();
	void hitDamage(float damage);

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setEmenyMemoryAddressLink(enemy* enemy) { _enemy = enemy; }


	inline RECT getRect() { return _rc; }
	BOOL &getIsDead() { return _isDead; }
	bool &getIsSummon() { return _isSummon; }

};

