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

	

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

};

