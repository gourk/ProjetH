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
	Exit = false;
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
	BmpPath = "Images/w.bmp";
	White.New(BmpPath);
	BmpPath = "Images/h.bmp";
	H.New(BmpPath,'h');
}

Motor::~Motor()
{
	SDL_Quit();
}


////////////////////
//M�thodes d'acc�s//
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

int Motor::GetLevel()
{	
	return _Level;
}


////////////////////
//M�thodes membres//
////////////////////
bool Motor::Init()
{
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) 
	{
		 fprintf (stderr, "Erreur d'initialisation de SDL: %s\n",
         SDL_GetError ());
		 return 1;
	}
	atexit (SDL_Quit);

	SDL_WM_SetIcon(SDL_LoadBMP("Images/c.bmp"), 0);
	SDL_WM_SetCaption ("H", NULL);

	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	int full;
	cout << "Plein ecran(1) ou fenetre(2) ?";
	cin >> full;

	//SDL_HWSURFACE -> M�moire de la carte graphique utilis�e
	int options = (SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
	int options2 = (SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (full == 1)
	{
		_Screen = SDL_SetVideoMode (WIDTH, HEIGHT/*+MENU*/, DEPTH, options);
	}
	else
	{
		_Screen = SDL_SetVideoMode (WIDTH, HEIGHT/*+MENU*/, DEPTH, options2);
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
	return 0;
}

void Motor::Cycle()
{
	int currentTime = SDL_GetTicks();
	int NextUpdate = SDL_GetTicks() + 50;

	while (currentTime <= NextUpdate)
	{
		currentTime = SDL_GetTicks();
	}
	EventManagement();
	MoveAuto();
	SDL_Flip(_Screen);
}

/*bool Motor::LoadLevel(const char *FileName)//Regroupement de ReadTable et Display
{	
	int i, j, k, l, x, y=0;
	ifstream	File;
	
	//Traitement du fichier txt
	File.open(FileName, ios::in);
	if (File.bad())
    return (1);
	//R�cup�ration du contenu du fichier dans un tableau char [25][25]
	for (i=0; i<25; i++)
	{
		for (j=0; j<25; j++)
		{
			File >> _Plate[i][j];
		}
	}
	File.close();
	//Affichage � partir du tableau de char
	SDL_Rect rectBrique =  Brique.GetRect();
	SDL_Rect rectE =  E.GetRect();
	SDL_Rect rectE1 =  E1.GetRect();
	SDL_Rect rectObj1 = Obj1.GetRect();
	SDL_Rect rectObj2 = Obj2.GetRect();
	SDL_Rect rectKey =  Key.GetRect();
	SDL_Rect rectDoor =  Door.GetRect();
	SDL_Rect rectNoir =  Noir.GetRect();
	SDL_Rect rectH = H.GetRect();
	for (l=0; l<25; l++)
	{	x = 0;
		for (k=0; k<25; k++)
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
					iObj1[0] = k;
					iObj1[1] = l;
					rectObj1.x = x;
					rectObj1.y = y;
					SDL_BlitSurface(Obj1.GetSurface(), NULL, _Screen, &rectObj1);
					break;
				case 'R':
					iObj2[0] = k;
					iObj2[1] = l;
					rectObj2.x = x;
					rectObj2.y = y;
					SDL_BlitSurface(Obj2.GetSurface(), NULL, _Screen, &rectObj2);
					break;
				case 'h':
					H.SetCharac_i (k);
					H.SetCharac_j (l);
					rectH.x = x;
					rectH.y = y;
					SDL_BlitSurface(H.GetSurface(), NULL, _Screen, &rectH);
					break;
				case 'k':
					if (this->_CheckObj1 == true)
					{
						iKey[0] = k;
						iKey[1] = l;
						rectKey.x = x;
						rectKey.y = y;
						SDL_BlitSurface(Key.GetSurface(), NULL, _Screen, &rectKey);
					}
					else
					{
						iKey[0] = k;
						iKey[1] = l;
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
						iDoor[0] = k;
						iDoor[1] = l;
						rectDoor.x = x;
						rectDoor.y = y;
						SDL_BlitSurface(Door.GetSurface(), NULL, _Screen, &rectDoor);
					}
					else
					{
						iDoor[0] = k;
						iDoor[1] = l;
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
}*/
bool Motor::Display()
{	
	int k, l, x, y=0;

	//Affichage � partir du tableau de char
	SDL_Rect rectBrique =  Brique.GetRect();
	SDL_Rect rectE =  E.GetRect();
	SDL_Rect rectE1 =  E1.GetRect();
	SDL_Rect rectObj1 = Obj1.GetRect();
	SDL_Rect rectObj2 = Obj2.GetRect();
	SDL_Rect rectKey =  Key.GetRect();
	SDL_Rect rectDoor =  Door.GetRect();
	SDL_Rect rectNoir =  Noir.GetRect();
	SDL_Rect rectH = H.GetRect();
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
					iObj1[0] = k;
					iObj1[1] = l;
					rectObj1.x = x;
					rectObj1.y = y;
                    SDL_BlitSurface(Obj1.GetSurface(), NULL, _Screen, &rectObj1);
					break;
				case 'R':
					iObj2[0] = k;
					iObj2[1] = l;
					rectObj2.x = x;
					rectObj2.y = y;
					SDL_BlitSurface(Obj2.GetSurface(), NULL, _Screen, &rectObj2);
					break;
				case 'h':
					H.SetCharac_i (k);
					H.SetCharac_j (l);
					rectH.x = x;
					rectH.y = y;
					SDL_BlitSurface(H.GetSurface(), NULL, _Screen, &rectH);
					break;
				case 'k':
					if (_CheckObj1 == true)
					{
						iKey[0] = k;
						iKey[1] = l;
						rectKey.x = x;
						rectKey.y = y;
						SDL_BlitSurface(Key.GetSurface(), NULL, _Screen, &rectKey);
					}
					else
					{
						iKey[0] = k;
						iKey[1] = l;
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
						iDoor[0] = k;
						iDoor[1] = l;
						rectDoor.x = x;
						rectDoor.y = y;
						SDL_BlitSurface(Door.GetSurface(), NULL, _Screen, &rectDoor);
					}
					else
					{
						iDoor[0] = k;
						iDoor[1] = l;
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
		if ((this->iObj1[0] == this->E.GetCharac_i())&&(this->iObj1[1] == this->E.GetCharac_j()))
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
		if ((this->iObj2[0] == this->E1.GetCharac_i())&&(this->iObj2[1] == this->E1.GetCharac_j()))
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
		if ((this->iKey[0] == this->H.GetCharac_i())&&(this->iKey[1] == this->H.GetCharac_j()))
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
		if ((this->iDoor[0] == this->H.GetCharac_i())&&(this->iDoor[1] == this->H.GetCharac_j()))
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
	BmpPath = "Images/h.bmp";
	H.New(BmpPath,'h');
}

void Motor::Delete()
{
	_CheckKey = false;
	_CheckDoor = false;
	_CheckObj1 = false;
	_CheckObj2 = false;
	E.Delete();
	E1.Delete();
	H.Delete();

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
	//R�cup�ration du contenu du fichier dans un tableau char [25][25]
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
					H.SetCharac_i (i);
					H.SetCharac_j (j);
					break;
				case 'k':
					iKey[0] = i;
					iKey[1] = j;
					break;
				case 'd':
					iDoor[0] = i;
					iDoor[1] = j;
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
	ifstream	File;
	int		i, j;
	bool		b1,b2,bH,bK,bD = false;
	char		_Plate [25][25];
	
	//Traitement du fichier txt
	File.open(FileName, ios::in);
	if (File.bad())
    return (1);
	//R�cup�ration du contenu du fichier dans un tableau char [25][25]
	for (i=0; i<25; i++)
	{
		for (j=0; j<25; j++)
		{
			File >> _Plate[i][j];
		}
	}
	File.close();
	//Recherche des erreurs dans le fichier
	for (i=0; i<25; i++)
	{
		for (j=0; j<25; j++)
		{	
			switch (_Plate [i][j])
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
		}
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
	static int nb[2];
	DOWN	= Collision_E(E.GetCharac_i()+1,E.GetCharac_j());
	RIGHT	= Collision_E(E.GetCharac_i(),E.GetCharac_j()+1);
	UP	= Collision_E(E.GetCharac_i()-1,E.GetCharac_j()); 
	LEFT	= Collision_E(E.GetCharac_i(),E.GetCharac_j()-1);
		
	switch (nb[0])
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
			nb[0]=2;
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
			nb[0]=1;
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
			nb[0]=3;
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
			nb[0]=0;
		break;
	}


	
	DOWN1	= Collision_E1(E1.GetCharac_i()+1,E1.GetCharac_j());
	RIGHT1	= Collision_E1(E1.GetCharac_i(),E1.GetCharac_j()+1);
	UP1	= Collision_E1(E1.GetCharac_i()-1,E1.GetCharac_j()); 
	LEFT1	= Collision_E1(E1.GetCharac_i(),E1.GetCharac_j()-1);

	switch (nb[1])
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
			nb[1]=3;
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
			nb[1]=0;
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
			nb[1]=2;
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
			nb[1]=1;
		break;
	}
}

bool Motor::Menu()
{	
	int x=0, y=800;

	//Affichage � partir du tableau de char
	SDL_Rect rectCloud = Cloud.GetRect();
	SDL_Rect rectWhite = White.GetRect(); 

	for (y=800; y<928; y=y+32)
	{
		for (x=0; x<800; x=x+32)
		{
			switch (y)
			{
				case 800:
				case 896:
					rectCloud.x = x;
					rectCloud.y = y;
					SDL_BlitSurface(Cloud.GetSurface(), NULL, _Screen, &rectCloud );
					break;
				default:
					if ((x==0)||(x==768))
					{
						rectCloud.x = x;
						rectCloud.y = y;
						SDL_BlitSurface(Cloud.GetSurface(), NULL, _Screen, &rectCloud );
					}
					else
					{
						rectWhite.x = x;
						rectWhite.y = y;
						SDL_BlitSurface(White.GetSurface(), NULL, _Screen, &rectWhite );
					}
					break;
			}
		}
	}
	return 0;
}
void Motor::EventManagement()
{
	keys = SDL_GetKeyState(NULL);

	//touche Echap
	if (keys[SDLK_ESCAPE])
	{
		Exit=true;
	}
	//touche r et R
	if (keys[SDLK_r])
	{
		Reset();
	}
	//touche bas
	if(keys[SDLK_DOWN])
	{
		if ((Collision((H.GetCharac_i()+1), H.GetCharac_j())) == false)
		{	
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'x');
			H.Down();
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'h');
			Display();
			CheckKey();
			CheckDoor();
		}
	}
	//touche droite
	if (keys[SDLK_RIGHT])
	{
		if ((Collision(H.GetCharac_i(), H.GetCharac_j()+1)) == false)
		{
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'x');
			H.Right();
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'h');
			Display();
			CheckKey();
			CheckDoor();
		}
	}
	//touche gauche
	if (keys[SDLK_LEFT])
	{
		if ((Collision(H.GetCharac_i(), H.GetCharac_j()-1)) == false)
		{
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'x');
			H.Left();
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'h');
			Display();
			CheckKey();
			CheckDoor();
		}
	}
	//touche haut
	if (keys[SDLK_UP])
	{
		if ((Collision(H.GetCharac_i()-1, H.GetCharac_j())) == false)
		{
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'x');
			H.Up();
			SetPlate(H.GetCharac_i(),H.GetCharac_j(),'h');
			Display();
			CheckKey();
			CheckDoor();
		}
	}
}
