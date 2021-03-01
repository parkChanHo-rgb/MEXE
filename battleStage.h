#pragma once
#include "gameNode.h"
#include "stage.h"



class player;
class enemy;
class boss;

class battleStage : public gameNode
{
private:

	float loopX, loopY;
	stage _stage;
	player* _player;
	enemy* _enemy;
	boss* _boss;
	


public:
	battleStage() {};
	~battleStage() {};

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
};

