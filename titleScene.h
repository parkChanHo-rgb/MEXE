#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
public:
	titleScene() {};
	~titleScene() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

