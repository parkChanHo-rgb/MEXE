#include "stdafx.h"
#include "enemyProgressBar.h"

HRESULT enemyProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarFront = IMAGEMANAGER->addImage("enemyFrontBar", "image/enemy/hpBarTop.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage("enemyBackBar", "image/enemy/hpBarBottom.bmp", width, height, true, RGB(255, 0, 255));

	//�������� ����ũ��� �̹����� ����ũ�⸸ŭ.
	_width = _progressBarFront->getWidth();

	return S_OK;
}

void enemyProgressBar::release()
{

}

void enemyProgressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarFront->getWidth(),
		_progressBarFront->getHeight());
}

void enemyProgressBar::render()
{
	IMAGEMANAGER->render("enemyBackBar", getMemDC(),
		_rcProgress.left + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2, 0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMAGEMANAGER->render("enemyFrontBar", getMemDC(),
		_rcProgress.left + _progressBarFront->getWidth() / 2,
		_y + _progressBarFront->getHeight() / 2, 0, 0,
		_width, _progressBarFront->getHeight());

}

void enemyProgressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
