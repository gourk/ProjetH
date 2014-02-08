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
#include "Object.h"

Object::Object()
{
}

Object::Object(const char *Bmp)
{
	_surfObject = SDL_LoadBMP(Bmp);
}

Object::~Object()
{
	//SDL_FreeSurface(_surfObject);
}

SDL_Surface *Object::GetSurface()
{
	SDL_Surface *Surface;
	Surface = _surfObject;
	return (Surface);
}

SDL_Rect Object::GetRect()
{
	return (_rectObject);
}
void Object::SetSurface(SDL_Surface *Surface)
{
	_surfObject = Surface;
}
void Object::SetRect(SDL_Rect rect)
{
	_rectObject = rect;
}
void Object::Delete()
{
	SDL_FreeSurface(_surfObject);
}

void Object::New(const char *Bmp)
{
	_surfObject = SDL_LoadBMP(Bmp);
}

