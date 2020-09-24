#include "pch.h"
#include "figure.h"

Sprite& figure::spritefigure() 
{
	return *m_sprite;
}
bool figure::textureready() const
{
	return ok_flag;
}
void figure::setPos(float x,float y)
{
	m_sprite->setPosition(x * 64.f, y * 64.f);
}
void figure::ColorChange(int color)
{
	m_sprite->setColor(sf::Color(color, color, color)); 
}
