#pragma once
#include "gameNode.h"
#include "battleStage.h"
#include "titleScene.h"
#include "gameoverScene.h"
#include "gameclearScene.h"




class playGround : public gameNode
{
private:
	
	
	

public:
	playGround();
	~playGround();

	

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

