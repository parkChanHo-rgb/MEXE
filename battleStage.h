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

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

