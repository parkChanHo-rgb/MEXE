#pragma once
#include "gameNode.h"


class stage : public gameNode
{
private:
	image* _stage;
	

public:
	stage() {};
	~stage() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

