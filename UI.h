#pragma once
#include "pch.h"
#include "FigureNames.h"
#include <iostream>


class UI
{
public:
	UI() {}

	void mouseShedule(class RenderWindow& window);
	void mouseShedule2(class RenderWindow& window,int x,int y);
	Vector2i& last_coin();
	void setlastcoin(Vector2i coin)
	{
		m_last_coin = coin;
	};
private:
	//	Место последней монетки
	Vector2i m_last_coin = Vector2i(0,0);
	std::chrono::steady_clock::time_point m_start, m_end;

};

