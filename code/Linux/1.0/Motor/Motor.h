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
#include "../Main/Define.h"
#include "../Object/Object.h"
#include "../Character/Character.h"

class	Motor
{
	private :
		SDL_Surface *_Screen;		
		char		_Plate [25][25];
		const char	*BmpPath;
		int		_Level, Charac_i, Charac_j, Key_i, Key_j, Door_i, Door_j, Obj1_i, Obj1_j, Obj2_i, Obj2_j, nb, nb1;
		bool		_CheckKey, _CheckDoor, _CheckObj1, _CheckObj2, _RestartLevel, UP1, DOWN1, RIGHT1, LEFT1, UP, DOWN, RIGHT, LEFT;
		
	public :
		//Constructeur/destructeur
		Motor();
		~Motor();
		//Instantiation des objets graphiques
		Object		Brique, Fond, Key, Door, Noir, TextFont;
		Object		Obj1, Obj2;
		Object		Cloud;
		Character	E, E1;
		//M�thodes d'acc�s
		SDL_Surface *GetScreen();
		void SetPlate(int,int,char);
		void SetCharac_i(int);
		void SetCharac_j(int);
		int GetCharac_i();
		int GetCharac_j();
		int GetLevel();
		//M�thodes membres
		bool Init();
		void New();
		void Delete();
		bool ReadTable( const char *);
		void Cycle();
		bool Collision(int,int);
		void CheckKey();
		void CheckDoor();
		void CheckObj1();
		void CheckObj2();
		bool Collision_E(int,int);
		bool Collision_E1(int,int);
		bool NextLevel();
		void Reset();
		bool CheckFile(const char *);
		void MoveAuto();
		bool Display(SDL_Surface*, SDL_Rect,const char *);
		bool Display(SDL_Surface*, SDL_Rect);
		bool Menu ();
};
