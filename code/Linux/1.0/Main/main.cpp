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
#include "../Motor/Motor.h"
#include "../Character/Character.h"
#include "../SDLfont/SDLfont.h"

bool ConsistensyChk (const char *Level);

int main(int argc, char **argv)
{
	//Definition et initialisation des variables
	bool		bExit = false, bCollision = true, bEnd = false;
	int		AfficheLevel = 1;
	int		iCollision, jCollision;
	const char	*BmpPath, *LevelPath;
	double		a;
	Uint8		*keys;
	Motor		Game;
	BmpPath = "Images/h.bmp";
	Character	H (BmpPath,'h');
	char		cH = 'h', cvide = 'x';
	string 		Level;
	SDL_Event	event;

	//Initialisation de l'affichage
	Game.Init();
	//Initialisation du texte
	SDLFont		fonte("Police/police.ttf",48);

	LevelPath = "1";
	bExit = ConsistensyChk(LevelPath);
	if (bExit == true)
	{ 
		cout << " Le fichier 1.txt correspondant au premier niveau est incorrect!! " <<endl;
		cout << " Appuyez sur y et valider pour quitter  ";
		cin >> a;
	}
	cout << Game.GetLevel()<< endl;
	cout << LevelPath <<endl;

	//Lecture du fichier 1 et chargement du niveau
	Game.Display(H.GetSurface(), H.GetRect(), LevelPath);
	H.SetCharac_i(Game.GetCharac_i());
	H.SetCharac_j(Game.GetCharac_j());
	SDL_EventState (SDL_KEYUP, SDL_ENABLE);
	SDL_EventState (SDL_KEYDOWN, SDL_ENABLE);
	fonte.Text(300,400,255,255,255,Game.GetScreen(),"LEVEL 1");
	Game.Display(H.GetSurface(), H.GetRect());
	SDL_Delay(100);
	fonte.Text(300,350,255,255,255,Game.GetScreen(),"");
	while (!bExit)
	{
		//Evenements
		if(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				//case SDL_MOUSEBUTTONDOWN:
				case SDL_QUIT:
					bExit=true;
					exit(0);
					break;
			}
		}
		keys = SDL_GetKeyState(NULL);
		
				if ( keys[SDLK_ESCAPE])
				{
					bExit=true;
					break;
				}
				
		 if (bEnd == false)
		 {
				if ( keys[SDLK_r])
				{
					Game.Reset();
				}

				if(keys[SDLK_DOWN])
				{	Game.CheckDoor();
					iCollision = H.GetCharac_i()+1;
					bCollision = Game.Collision(iCollision, H.GetCharac_j());
					if (bCollision == false)
					{	
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cvide);
						H.Down();
						Game.SetCharac_i(H.GetCharac_i());
						Game.SetCharac_j(H.GetCharac_j());
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cH);
						Game.Display(H.GetSurface(), H.GetRect());
						/*Game.CheckObj1();
						Game.CheckObj2();*/
						Game.CheckKey();
						Game.CheckDoor();
					}
				}
				if ( keys[SDLK_RIGHT])
				{	Game.CheckDoor();
					iCollision = H.GetCharac_j()+1;
					bCollision = Game.Collision(H.GetCharac_i(), iCollision);
					if (bCollision == false)
					{
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cvide);
						H.Right();
						Game.SetCharac_i(H.GetCharac_i());
						Game.SetCharac_j(H.GetCharac_j());
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cH);
						Game.Display(H.GetSurface(), H.GetRect());
						/*Game.CheckObj1();
						Game.CheckObj2();*/
						Game.CheckKey();
						Game.CheckDoor();
					}
				}
				if ( keys[SDLK_LEFT])
				{	Game.CheckDoor();
					iCollision = H.GetCharac_j()-1;
					bCollision = Game.Collision(H.GetCharac_i(), iCollision);
					if (bCollision == false)
					{
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cvide);
						H.Left();
						Game.SetCharac_i(H.GetCharac_i());
						Game.SetCharac_j(H.GetCharac_j());
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cH);
						Game.Display(H.GetSurface(), H.GetRect());
						/*Game.CheckObj1();
						Game.CheckObj2();*/
						Game.CheckKey();
						Game.CheckDoor();
					}
				}
				if ( keys[SDLK_UP])
				{	Game.CheckDoor();
					iCollision = H.GetCharac_i()-1;
					bCollision = Game.Collision(iCollision, H.GetCharac_j());
					if (bCollision == false)
					{
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cvide);
						H.Up();
						Game.SetCharac_i(H.GetCharac_i());
						Game.SetCharac_j(H.GetCharac_j());
						Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cH);
						Game.Display(H.GetSurface(), H.GetRect());
						/*Game.CheckObj1();
						Game.CheckObj2();*/
						Game.CheckKey();
						Game.CheckDoor();
					}
				}
		}
		SDL_Flip(Game.GetScreen());
		if (Game.NextLevel() == true)
		{
			//Suppression des objets principaux
			//Game.SetPlate(H.GetCharac_i(),H.GetCharac_j(),cvide);
			//H.Delete();
			Game.Delete();
			//Affichage plateau vide
			Game.Display(H.GetSurface(), H.GetRect());
			//Recr�ation de ces objets
			BmpPath = "h.bmp";
			H.New(BmpPath,'h');
			if (Game.GetLevel() == 1)
			{
				AfficheLevel = Game.GetLevel();
			}
			else
			{
				AfficheLevel = Game.GetLevel() - 1;
			}
			fonte.Text(150,350,255,255,255,Game.GetScreen(),"LEVEL %i CLEARED", AfficheLevel);
			SDL_Flip(Game.GetScreen());
			//SDL_Delay(500);
			//Passage au niveau sup�rieur
			ostringstream oss;
			oss << Game.GetLevel();
			Level = oss.str();
			LevelPath = Level.c_str();
			cout << Game.GetLevel() << endl;
			cout << LevelPath << endl;
			if (Game.CheckFile(LevelPath) == true)
			{
				if (Game.ReadTable(LevelPath)==1)
				{	
					fonte.Text(300,350,255,255,255,Game.GetScreen(),"");
					SDL_Flip(Game.GetScreen());
					bEnd = true;
					cout << "Pas de niveau suivant � charger : fin du jeu" << endl;
					fonte.Text(200,350,255,255,255,Game.GetScreen(),"GAME'S END");
					SDL_Flip(Game.GetScreen());
					SDL_Delay(100);
				}
				else
				{
					H.SetCharac_i(Game.GetCharac_i());
					H.SetCharac_j(Game.GetCharac_j());
					//fonte.Text(300,350,255,255,255,Game.GetScreen(),"LEVEL %i",Game.GetLevel());
					//SDL_Flip(Game.GetScreen());
					cout << "Affichage Niveau superieur" << endl;
					SDL_Delay(1000);
					Game.New();
				}
			}
			else
			{
				Game.Display(H.GetSurface(), H.GetRect());
				fonte.Text(300,350,255,255,255,Game.GetScreen(),"");
				SDL_Flip(Game.GetScreen());
				bEnd=true;
				fonte.Text(195,350,255,255,255,Game.GetScreen(),"GAME'S END");
				SDL_Flip(Game.GetScreen());
				SDL_Delay(2000);
			}

		}
		Game.Cycle();
		//R�initialation des variables de collision
		iCollision = 0;
		jCollision = 0;
		bCollision = true;
		//Game.MoveAuto();
		//Game.Menu();
		Game.Display(H.GetSurface(), H.GetRect());
	}
	return 0;
}

bool ConsistensyChk (const char *Level)
{
	ifstream	File;
	int		i, j, k, l, x, y = 0;
	bool		b1,b2,bH,bK,bD = false;
	char		_Plate [25][25];
	
	//Traitement du fichier txt
	File.open(Level, ios::in);
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
	{return false;}
	else
	{return true;}
}
