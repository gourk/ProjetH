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
#include "../Object/Object.h"

class Enemy : public Object
{	
	private :
		char _Letter;
		int	_Charac_i, _Charac_j;
		
	public :
		Enemy();
		Enemy(const char *,char);
		void SetCharac_i(int);
		void SetCharac_j(int);
		int GetCharac_i();
		int GetCharac_j();
		void New(const char *,char);
		void Init();
		void Up();
		void Right();
		void Left();
		void Down();
};
