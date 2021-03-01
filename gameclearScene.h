#pragma once
#include "gameNode.h"

class gameclearScene : public gameNode
{
public:
	gameclearScene() {};
	~gameclearScene() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

