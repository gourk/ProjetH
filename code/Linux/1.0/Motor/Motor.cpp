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
#include "Motor.h"

////////////////////////////
//Constructeur/Destructeur//
////////////////////////////
Motor::Motor()
{
	_Screen = NULL;
	_CheckKey = false;
	_CheckDoor = false;
	_CheckObj2 = false;
	_CheckObj1 = false;
	_RestartLevel = false;
	_Level = 1;
	BmpPath = "Images/b.bmp";
	Brique.New(BmpPath);
	BmpPath = "Images/k.bmp";
	Key.New(BmpPath);
	BmpPath = "Images/d.bmp";
	Door.New(BmpPath);
	BmpPath = "Images/x.bmp";
	Noir.New(BmpPath);
	TextFont.New(BmpPath);
	BmpPath = "Images/1.bmp";
	E.New(BmpPath,'1');
	BmpPath = "Images/2.bmp";
	E1.New(BmpPath,'2');
	BmpPath = "Images/G.bmp";
	Obj1.New(BmpPath);
	BmpPath = "Images/R.bmp";
	Obj2.New(BmpPath);
	BmpPath = "Images/c.bmp";
	Cloud.New(BmpPath);
	nb=0;
	nb1=0;
}

Motor::~Motor()
{
	SDL_Quit();
}


////////////////////
//Méthodes d'accès//
////////////////////
SDL_Surface *Motor::GetScreen()
{
	SDL_Surface *Surface = NULL;
	Surface = _Screen;
	return (Surface);
}

void Motor::SetPlate(int i,int j,char Letter)
{
	_Plate [i][j] = Letter;
}

void Motor::SetCharac_i(int i)
{
	Charac_i = i;
}

void Motor::SetCharac_j(int j)
{
	Charac_j = j;
}

int Motor::GetCharac_i()
{
	return Charac_i;
}

int Motor::GetCharac_j()
{
	return Charac_j;
}

int Motor::GetLevel()
{	
	return _Level;
}


////////////////////
//Méthodes membres//
////////////////////
bool Motor::Init()
{
	if (SDL_Init (SDL_INIT_VIDEO) < 0) 
	{
		 fprintf (stderr, "Erreur d'initialisation de SDL: %s\n",
         SDL_GetError ());
		 return 1;
	}
	atexit (SDL_Quit);

	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL+50);
	int full;
	cout << "Plein ecran(1) ou fenetre(2) ?";
	cin >> full;

	int options = (/*SDL_ANYFORMAT  |*/ SDL_FULLSCREEN | SDL_SWSURFACE | SDL_DOUBLEBUF);
	int options2 = (SDL_SWSURFACE | SDL_DOUBLEBUF);
	if (full == 1)
	{
		_Screen = SDL_SetVideoMode (WIDTH, HEIGHT, DEPTH, options);
	}
	else
	{
		_Screen = SDL_SetVideoMode (WIDTH, HEIGHT, DEPTH, options2);
	}
	if (_Screen == NULL) 
	{
		fprintf (stderr, "Erreur d'init du mode video: %s\n",
        SDL_GetError ());
		return 1;
	}
	//Initialisation de SDL_TTF 
	if( TTF_Init() == -1 ) { 
		return 1; 
	}
	//SDL_WM_SetIcon(SDL_LoadBMP("h.bmp"), NULL);
	SDL_WM_SetCaption ("H", "H.ico");
	return 0;
}

void Motor::Cycle()
{
	int currentTime = SDL_GetTicks();
	int NextUpdate = SDL_GetTicks() + 75;

	while (currentTime <= NextUpdate)
	{
		currentTime = SDL_GetTicks();
	}
	MoveAuto();
}

bool Motor::Display(SDL_Surface *surfH, SDL_Rect H, const char *FileName)
{	
	int i, j, k, l, x, y=0;
	ifstream	File;
	
	//Traitement du fichier txt
	File.open(FileName, ios::in);
	if (File.bad())
    return (1);
	//Récupération du contenu du fichier dans un tableau char [25][25]
	for (i=0; i<25; i++)
	{
		for (j=0; j<25; j++)
		{
			File >> _Plate[i][j];
		}
	}
	File.close();
	//Affichage à partir du tableau de char
	SDL_Rect rectBrique =  Brique.GetRect();
	SDL_Rect rectE =  E.GetRect();
	SDL_Rect rectE1 =  E1.GetRect();
	SDL_Rect rectObj1 = Obj1.GetRect();
	SDL_Rect rectObj2 = Obj2.GetRect();
	SDL_Rect rectKey =  Key.GetRect();
	SDL_Rect rectDoor =  Door.GetRect();
	SDL_Rect rectNoir =  Noir.GetRect();
	for (k=0; k<25; k++)
	{	x = 0;
		for (l=0; l<25; l++)
		{	
			switch (_Plate [k][l])
			{
				case 'b':
					rectBrique.x = x;
					rectBrique.y = y;
					SDL_BlitSurface(Brique.GetSurface(), NULL, _Screen, &rectBrique );
					break;
				case '1':
					E.SetCharac_i (k);
					E.SetCharac_j (l);
					rectE.x = x;
					rectE.y = y;
					SDL_BlitSurface(E.GetSurface(), NULL, _Screen, &rectE);
					break;
				case '2':
					E1.SetCharac_i (k);
					E1.SetCharac_j (l);
					rectE1.x = x;
					rectE1.y = y;
					SDL_BlitSurface(E1.GetSurface(), NULL, _Screen, &rectE1);
					break;
				case 'G':
					Obj1_i = k;
					Obj1_j = l;
					rectObj1.x = x;
					rectObj1.y = y;
					SDL_BlitSurface(Obj1.GetSurface(), NULL, _Screen, &rectObj1);
					break;
				case 'R':
					Obj2_i = k;
					Obj2_j = l;
					rectObj2.x = x;
					rectObj2.y = y;
					SDL_BlitSurface(Obj2.GetSurface(), NULL, _Screen, &rectObj2);
					break;
				case 'h':
					Charac_i = k;
					Charac_j = l;
					H.x = x;
					H.y = y;
					SDL_BlitSurface(surfH, NULL, _Screen, &H);
					break;
				case 'k':
					if (this->_CheckObj1 == true)
					{
						Key_i = k;
						Key_j = l;
						rectKey.x = x;
						rectKey.y = y;
						SDL_BlitSurface(Key.GetSurface(), NULL, _Screen, &rectKey);
					}
					else
					{
						Key_i = k;
						Key_j = l;
						rectKey.x = x;
						rectKey.y = y;
						rectBrique.x = x;
						rectBrique.y = y;
						SDL_BlitSurface(Brique.GetSurface(), NULL, _Screen, &rectBrique);
					}
					break;
				case 'd':
					if (this->_CheckObj2 == true)
					{
						Door_i = k;
						Door_j = l;
						rectDoor.x = x;
						rectDoor.y = y;
						SDL_BlitSurface(Door.GetSurface(), NULL, _Screen, &rectDoor);
					}
					else
					{
						Door_i = k;
						Door_j = l;
						rectDoor.x = x;
						rectDoor.y = y;
						rectBrique.x = x;
						rectBrique.y = y;
						SDL_BlitSurface(Brique.GetSurface(), NULL, _Screen, &rectBrique);
					}
					break;
				case 'x':
					rectNoir.x = x;
					rectNoir.y = y;
					SDL_BlitSurface(Noir.GetSurface(), NULL, _Screen, &rectNoir);
					break;
			}
            x = x + 32;			
		}
		y = y + 32;
	}
	return 0;
}
bool Motor::Display(SDL_Surface *surfH, SDL_Rect H)
{	
	int k, l, x, y=0;

	//Affichage à partir du tableau de char
	SDL_Rect rectBrique =  Brique.GetRect();
	SDL_Rect rectE =  E.GetRect();
	SDL_Rect rectE1 =  E1.GetRect();
	SDL_Rect rectObj1 = Obj1.GetRect();
	SDL_Rect rectObj2 = Obj2.GetRect();
	SDL_Rect rectKey =  Key.GetRect();
	SDL_Rect rectDoor =  Door.GetRect();
	SDL_Rect rectNoir =  Noir.GetRect();
	for (k=0; k<25; k++)
	{	x = 0;
		for (l=0; l<25; l++)
		{	
			switch (_Plate [k][l])
			{
				case 'b':
					rectBrique.x = x;
					rectBrique.y = y;
					SDL_BlitSurface(Brique.GetSurface(), NULL, _Screen, &rectBrique );
					break;
				case '1':
					rectE.x = x;
					rectE.y = y;
					SDL_BlitSurface(E.GetSurface(), NULL, _Screen, &rectE);
					break;
				case '2':
					rectE1.x = x;
					rectE1.y = y;
					SDL_BlitSurface(E1.GetSurface(), NULL, _Screen, &rectE1);
					break;
				case 'G':
					Obj1_i = k;
					Obj1_j = l;
					rectObj1.x = x;
					rectObj1.y = y;
                    SDL_BlitSurface(Obj1.GetSurface(), NULL, _Screen, &rectObj1);
					break;
				case 'R':
					Obj2_i = k;
					Obj2_j = l;
					rectObj2.x = x;
					rectObj2.y = y;
					SDL_BlitSurface(Obj2.GetSurface(), NULL, _Screen, &rectObj2);
					break;
				case 'h':
					Charac_i = k;
					Charac_j = l;
					H.x = x;
					H.y = y;
					SDL_BlitSurface(surfH, NULL, _Screen, &H);
					break;
				case 'k':
					if (_CheckObj1 == true)
					{
						Key_i = k;
						Key_j = l;
						rectKey.x = x;
						rectKey.y = y;
						SDL_BlitSurface(Key.GetSurface(), NULL, _Screen, &rectKey);
					}
					else
					{
						Key_i = k;
						Key_j = l;
						rectKey.x = x;
						rectKey.y = y;
						rectBrique.x = x;
						rectBrique.y = y;
						SDL_BlitSurface(Brique.GetSurface(), NULL, _Screen, &rectBrique);
					}
					break;
				case 'd':
					if (this->_CheckObj2 == true)
					{
						Door_i = k;
						Door_j = l;
						rectDoor.x = x;
						rectDoor.y = y;
						SDL_BlitSurface(Door.GetSurface(), NULL, _Screen, &rectDoor);
					}
					else
					{
						Door_i = k;
						Door_j = l;
						rectDoor.x = x;
						rectDoor.y = y;
						rectBrique.x = x;
						rectBrique.y = y;
						SDL_BlitSurface(Brique.GetSurface(), NULL, _Screen, &rectBrique);
					}
					break;
				case 'x':
					rectNoir.x = x;
					rectNoir.y = y;
					SDL_BlitSurface(Noir.GetSurface(), NULL, _Screen, &rectNoir);
					break;
			}
            x = x + 32;			
		}
		y = y + 32;
		cout << endl;
	}
	return 0;
}

bool Motor::Collision(int i, int j)
{
	switch (_Plate [i][j])
			{
				case 'k' :
					if (_CheckObj1 == true)
					{
                        return false;
					}
					else
					{
						return true;
					}
					break;
				case 'd' :
					if ((_CheckKey == true)&&(_CheckObj2 == true))
					{
						return false;
					}
					else
					{
						return true;
					}
					break;
				case 'x':
					return false;
					break;
				default :
					return true;
			}
}

void Motor::CheckObj1()
{
	if (_CheckObj1 == false)
	{
		if ((this->Obj1_i == this->E.GetCharac_i())&&(this->Obj1_j == this->E.GetCharac_j()))
		{
			_CheckObj1 = true;
		}
		else
		{
			_CheckObj1 = false;
		}
	}
}
void Motor::CheckObj2()
{
	if (_CheckObj2 == false)
	{
		if ((this->Obj2_i == this->E1.GetCharac_i())&&(this->Obj2_j == this->E1.GetCharac_j()))
		{
			_CheckObj2 = true;
		}
		else
		{
			_CheckObj2 = false;
		}
	}
}
void Motor::CheckKey()
{
	if (_CheckKey == false)
	{
		if ((this->Key_i == this->Charac_i)&&(this->Key_j == this->Charac_j))
		{
			this->_CheckKey = true;
		}
		else
		{
			this->_CheckKey = false;
		}
	}
}

void Motor::CheckDoor()
{
	if (_CheckDoor == false)
	{
		if ((this->Door_i == this->Charac_i)&&(this->Door_j == this->Charac_j))
		{
			this->_CheckDoor = true;
		}
		else
		{
			this->_CheckDoor = false;
		}
	}
}

bool Motor::Collision_E(int i, int j)
{
	switch (_Plate [i][j])
			{
				
				case 'G' :
					return false;
				case 'x':
					return false;
					break;
				default :
					return true;
			}
}

bool Motor::Collision_E1(int i, int j)
{
	switch (_Plate [i][j])
			{
				case 'R' :
					return false;
				case 'x':
					return false;
					break;
				default :
					return true;
			}
}

bool Motor::NextLevel()
{
	if ((this->_CheckKey == true)&&(this->_CheckDoor == true))
	{
		_Level = _Level + 1;
		return true;
	}
	else
	{
		if (_RestartLevel == true)
		{
		_RestartLevel = false;
		return true;
		}
		else
		{return false;}
	}
	
}

void Motor::Reset()
{
	_RestartLevel = true;
}

void Motor::New()
{
	BmpPath = "Images/1.bmp";
	E.New(BmpPath,'1');
	BmpPath = "Images/2.bmp";
	E1.New(BmpPath,'2');
}

void Motor::Delete()
{
	_CheckKey = false;
	_CheckDoor = false;
	_CheckObj1 = false;
	_CheckObj2 = false;
	E.Delete();
	E1.Delete();

	for (int i=0; i<25; i++)
	{
		for (int j=0; j<25; j++)
		{
			_Plate[i][j]='x';
		}
	}
}

bool Motor::ReadTable(const char *FileName)
{	
	ifstream	File;
	int i, j;
	//Traitement du fichier txt
	File.open(FileName, ios::in);	
	if (File.bad())
    return 1;
	//Récupération du contenu du fichier dans un tableau char [25][25]
	for (i=0; i<25; i++)
	{
		for (j=0; j<25; j++)
		{
			File >> _Plate[i][j];
		}
	}
	File.close();
	//Affectation des positions
		for (i=0; i<25; i++)
		{
			for (j=0; j<25; j++)
			{
				switch (_Plate [i][j])
				{
					case 'h':
						Charac_i = i;
						Charac_j = j;
						break;
					case 'k':
						Key_i = i;
						Key_j = j;
						break;
					case 'd':
						Door_i = i;
						Door_j = j;
						break;
					case '1':
						E.SetCharac_i (i);
						E.SetCharac_j (j);
					break;
					case '2':
						E1.SetCharac_i (i);
						E1.SetCharac_j (j);
					break;

				}
			}
		}
		return 0;
}

bool Motor::CheckFile(const char *FileName)
{
	/*ifstream	File;
	
	File.open(FileName, ios::in);
	if (File.is_open ()) 
	{
		return true;
   	} 
	else 
	{
		return false;
	}*/
	ifstream	File;
	int		i, j, k, l, x, y = 0;
	bool		b1,b2,bH,bK,bD = false;
	char		_Plate [25][25];
	
	//Traitement du fichier txt
	File.open(FileName, ios::in);
	if (File.bad())
    return (1);
	//Récupération du contenu du fichier dans un tableau char [25][25]
	for (i=0; i<25; i++)
	{
		for (j=0; j<25; j++)
		{
			File >> _Plate[i][j];
		}
	}
	File.close();
	for (k=0; k<25; k++)
	{	x = 0;
		for (l=0; l<25; l++)
		{	
			switch (_Plate [k][l])
			{
				case '1':
					b1=true;
					break;
				case '2':
					b2=true;
					break;
				case 'h':
					bH=true;
					break;
				case 'k':
					bK=true;
					break;
				case 'd':
					bD=true;
					break;
			}
           		x = x + 32;			
		}
		y = y + 32;
	}

	if (bH == true)
	{cout << "Hero trouve" <<endl;}
	else
	{cout << "Hero NON trouve" <<endl;}

	if (b1 == true)
	{cout << "Ennemi 1 trouve" <<endl;}
	else
	{cout << "Ennemi 1 NON trouve" <<endl;}

	if (b2==true)
	{cout << "Ennemi 2 trouve" <<endl;}
	else
	{cout << "Ennemi 2 NON trouve" <<endl;}

	if (bK==true)
	{cout << "Cle trouvee" <<endl;}
	else
	{cout << "Cle NON trouvee" <<endl;}

	if (bD==true)
	{cout << "Porte trouvee" <<endl;}
	else
	{cout << "Porte NON trouvee" <<endl;}
	if ((bH==true) && (b1==true) && (b2==true) && (bK==true) && (bD==true))
	{return true;}
	else
	{return false;}
}

void Motor::MoveAuto()
{
	DOWN	= Collision_E(E.GetCharac_i()+1,E.GetCharac_j());
	RIGHT	= Collision_E(E.GetCharac_i(),E.GetCharac_j()+1);
	UP	= Collision_E(E.GetCharac_i()-1,E.GetCharac_j()); 
	LEFT	= Collision_E(E.GetCharac_i(),E.GetCharac_j()-1);
		
	switch (nb)
	{
	case 1 :
		if (DOWN == false)
		{
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'x');
			E.Down();
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'1');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb=2;
		break;
	case 3 :
       		if (RIGHT == false)
		{
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'x');
			E.Right();
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'1');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb=1;
		break;
	case 0 :
		if (UP == false)
		{
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'x');
			E.Up();
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'1');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb=3;
		break;
	case 2 :
		if (LEFT == false)
		{
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'x');
			E.Left();
			SetPlate(E.GetCharac_i(),E.GetCharac_j(),'1');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb=0;
		break;
	}


	
	DOWN1	= Collision_E1(E1.GetCharac_i()+1,E1.GetCharac_j());
	RIGHT1	= Collision_E1(E1.GetCharac_i(),E1.GetCharac_j()+1);
	UP1	= Collision_E1(E1.GetCharac_i()-1,E1.GetCharac_j()); 
	LEFT1	= Collision_E1(E1.GetCharac_i(),E1.GetCharac_j()-1);

	switch (nb1)
	{
	case 1 :
		if (DOWN1 == false)
		{
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'x');
			E1.Down();
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'2');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb1=3;
		break;
	case 3 :
       		if (RIGHT1 == false)
		{
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'x');
			E1.Right();
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'2');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb1=0;
		break;
	case 0 :
		if (UP1 == false)
		{
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'x');
			E1.Up();
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'2');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb1=2;
		break;
	case 2 :
		if (LEFT1 == false)
		{
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'x');
			E1.Left();
			SetPlate(E1.GetCharac_i(),E1.GetCharac_j(),'2');
			CheckObj1();
			CheckObj2();
		}
		else 
			nb1=1;
		break;
	}
}

 bool Motor::Menu()
{	
	int k, x=0, y=0;

	//Affichage à partir du tableau de char
	SDL_Rect rectCloud =  Cloud.GetRect();
	y=800;
	for (k=0; k<25; k++)
	{	
		rectCloud.x = x;
		rectCloud.y = y;
		SDL_BlitSurface(Cloud.GetSurface(), NULL, _Screen, &rectCloud );
		x = x + 32;
	}
	y=900;
	x=0;
	for (k=0; k<25; k++)
	{	
		rectCloud.x = x;
		rectCloud.y = y;
		SDL_BlitSurface(Cloud.GetSurface(), NULL, _Screen, &rectCloud );
		x = x + 32;
	}	
	return 0;
}

