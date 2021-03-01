#pragma once
#include "gameNode.h"


class enemyProgressBar : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y;
	float _width;

	image* _progressBarFront;		//�տ� ���� ������ �̹���
	image* _progressBarBack;	//�ڿ� �׷��� ������ �̹���

public:
	enemyProgressBar() {};
	~enemyProgressBar() {};

	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

};