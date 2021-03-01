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
	image*	_enemy;			//적의 이미지
	RECT	_rc;			//적의 렉트
	float x, y;

	int		_rndCount;		// 랜덤용 카운트
	int		_actCount;		// 행동 실행용 카운트
	int		_rndMoveCount;	// 랜덤 움직임용 카운트
	int		_moveCount;		// 위에놈과 같이 실행시켜줄 카운트
	int		_count, _index; // 프레임렌더용 카운트 인덱스

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
	int		_rndMoveCount;	// 랜덤 행동용 카운트
	int		_moveCount;		// 랜덤 행동용 카운트	
	int		_specialCount;	// 특수 공격용 카운트
	int		_finishCount;	// 필살기용 카운트
	float x, y;
	int _actionCount, _actionIndex; // 움직임 프레임 렌더용 카운트 인덱스
	int _attackCount, _attackIndex; // 공격 프레임 렌더용 카운트 인덱스
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

