/*
H - Jeu ludique
Copyright (C) 2007  Yoann CALAMAI

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const char *Bmp,char Letter)
{
	_surfObject = SDL_LoadBMP(Bmp);
	_Letter=Letter;
}

void Enemy::SetCharac_i(int i)
{
	_Charac_i = i;
}

void Enemy::SetCharac_j(int j)
{
	_Charac_j = j;
}
int Enemy::GetCharac_i()
{
	return _Charac_i;
}

int Enemy::GetCharac_j()
{
	return _Charac_j;
}

void Enemy::New(const char *Bmp,char Letter)
{
	_surfObject = SDL_LoadBMP(Bmp);
	_Letter=Letter;
}

void Enemy::Init()
{
	SDL_SetColorKey(_surfObject,SDL_SRCCOLORKEY,SDL_MapRGB(_surfObject->format,0,255,0));
}

void Enemy::Up()
{
	if (_Charac_i>0)
	{
		_Charac_i = _Charac_i - 1;
	}
}

void Enemy::Right()
{	
	if (_Charac_j<24)
	{
		_Charac_j =_Charac_j + 1;
	}
}

void Enemy::Left()
{
	if (_Charac_j>0)
	{
		_Charac_j = _Charac_j - 1;
	}
}

void Enemy::Down()
{
	if (_Charac_i<24)
	{
		_Charac_i = _Charac_i + 1;
	}
}
