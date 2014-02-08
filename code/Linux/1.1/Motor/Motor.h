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
#ifndef MOTOR_H
#define MOTOR_H
#include "../Main/Define.h"
#include "../Object/Object.h"
#include "../Character/Character.h"

class	Motor
{
	private :
		SDL_Surface 	*_Screen;
		SDL_TimerID 	_timer;		
		char		_Plate [25][25];
		const char	*BmpPath;
		int		_Level, iKey[2], iDoor[2], iObj1[2], iObj2[2];
		Uint8		*keys;
		bool		_CheckKey, _CheckDoor, _CheckObj1, _CheckObj2, _RestartLevel, UP1, DOWN1, RIGHT1, LEFT1, UP, DOWN, RIGHT, LEFT;
		
	public :
		bool Exit;
		//Constructeur/destructeur
		Motor();
		~Motor();
		//Instantiation des objets graphiques
		Object		Brique, Fond, Key, Door, Noir, TextFont;//Elements du décor
		Object		Obj1, Obj2;//2 Champi
		Object		Cloud, White;//Décor du Menu
		Character	H, E, E1;//Personnages
		//Méthodes d'accès
		SDL_Surface *GetScreen();
		void SetPlate(int,int,char);
		int GetLevel();
		//Méthodes membres
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
		//bool LoadLevel(const char *);
		bool Display();
		bool Menu ();
		void EventManagement();
};
#endif
