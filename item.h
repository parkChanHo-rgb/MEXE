#pragma once
#include "gameNode.h"

enum ITEM
{
	CANNON,
	SPREAD,
	INVISIBLE
};

class item : public gameNode
{
private:
	image* _menu;
	image* _chip;
	image* _intro;
	ITEM _item;

public:
	item() {};
	~item() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	ITEM &getItem() { return _item; }
};

