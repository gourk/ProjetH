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

class SDLFont {
 
public:
    // Constructeur et destructeur
    SDLFont(const char* FontName,int size);
    ~SDLFont();
 
    // Affichage en utilisant la font
    void Text(int x,int y,int r,int g,int b,SDL_Surface* surf,
              const char* format,...);
 
    // Donne la longueur d'un texte
    int Length(const char* format,...);
 
    // Donne la hauteur d'un texte
    int Height(const char* format,...);
 
private:
    // Pointeur sur la font
    TTF_Font* font;
    
    // Nom de la font TTF
    std::string FontName;
 
};
