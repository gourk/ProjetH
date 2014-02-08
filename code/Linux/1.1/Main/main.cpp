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

int main(int argc, char **argv)
{
////////////////////////////////////////////////////////////
//Definition et initialisation des variables et des objets//
////////////////////////////////////////////////////////////
	int		AfficheLevel = 1;
	const char	*LevelPath;
	Motor		Game;
	string 		Level;
	SDL_Event	event;

	//Initialisation du moteur de jeu
	Game.Init();
	//Initialisation du texte
	SDLFont	fonte("Police/police.ttf",48);

////////////////////////////
//Chargement du 1er niveau//
////////////////////////////
	LevelPath = "1";
	if ((Game.CheckFile(LevelPath)) == false)
	{ 
		cout << " Le fichier 1.txt correspondant au premier niveau est incorrect!! " <<endl;
		Game.Exit = true;
	}
	cout << Game.GetLevel()<< endl;
	cout << LevelPath <<endl;
	Game.ReadTable(LevelPath);
	fonte.Text(300,400,255,255,255,Game.GetScreen(),"LEVEL 1");
	Game.Display();
	SDL_Delay(100);
	fonte.Text(300,350,255,255,255,Game.GetScreen(),"");

////////////////////////////////////////////////////////////////////
///////////////////BOUCLE PRINCIPALE DU PROGRAMME///////////////////
////////////////////////////////////////////////////////////////////
	while (!Game.Exit)
	{
//////////////////////////
//Gestion des evenements//
//////////////////////////
		if(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					Game.Exit=true;
					exit(0);
					break;
				default:
					break;
			}
		}

////////////////////////
//Changement de niveau//
////////////////////////
		if (Game.NextLevel() == true)
		{
			//Suppression des objets principaux
			Game.Delete();
			//Affichage plateau vide
			Game.Display();
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
					cout << "Pas de niveau suivant � charger : fin du jeu" << endl;
					fonte.Text(200,350,255,255,255,Game.GetScreen(),"GAME'S END");
					SDL_Flip(Game.GetScreen());
					SDL_Delay(100);
				}
				else
				{
					cout << "Affichage Niveau superieur" << endl;
					SDL_Delay(1000);
					Game.New();
				}
			}
			else
			{
				SDL_Quit();
			}

		}
		Game.Cycle();
		Game.Display();
		//Game.Menu();
	}
	SDL_Quit();
	return 0;
}

