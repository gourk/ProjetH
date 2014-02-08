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
#ifndef OBJECT_H
#define OBJECT_H
#include "../Main/Define.h"

class	Object
{
	public :
		Object();
		Object(const char *);
		~Object();
		SDL_Surface	*GetSurface();
		SDL_Rect	GetRect();
		SDL_Surface	*_surfObject;
		SDL_Rect	_rectObject;
		void Delete();
		void New(const char *);
};
#endif
