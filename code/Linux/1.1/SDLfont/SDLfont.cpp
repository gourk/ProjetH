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
#include "SDLfont.h"
#include <cstdarg>
 
// Constructeur : prend pour arguments :
//   - le chemin et le nom de la font .ttf avec une string ->FontName
//   - la taille de la font g�n�r�e avec un int ->size
//   - la couleur de la font g�n�r�e avec un SDL_Color -> color
SDLFont::SDLFont(const char* FontName,int size)
{
    FontName = FontName;
 
    // On ouvre la font
    font=TTF_OpenFont(FontName,size);
    if(!font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(1);
    }
}
 
// Destructeur
SDLFont::~SDLFont()
{
    TTF_CloseFont(font);
}
 
// Affiche du texte
void SDLFont::Text(int x,int y,int r,int g,int b,SDL_Surface* surf,
                   const char* format,...)
{
    va_list liste;
    va_start(liste,format);
 
    SDL_Rect rect = {x,y};
 
    char texte[512];
    vsprintf(texte,format,liste);
 
    SDL_Surface* text_surface;
    
    SDL_Color color = {r,g,b};
 
    if(!(text_surface = TTF_RenderText_Blended(font,texte,color)))
        printf("%s\n", TTF_GetError());
 
    else
    {
        SDL_BlitSurface(text_surface,NULL,surf,&rect);
        SDL_FreeSurface(text_surface);
    }
}
 
// Fonction qui renvoit la longueur du texte affich� avec la font
int SDLFont::Length(const char* format,...)
{
    va_list liste;
    va_start(liste,format);
 
    int w,h;
    
    char texte[512];
    vsprintf(texte,format,liste);
 
    if (TTF_SizeText(font,texte,&w,&h) == 0)
        return w;
    else
        return -1;
}
 
// Fonction qui renvoit la hauteur du texte affich� avec la font
int SDLFont::Height(const char* format,...)
{
    va_list liste;
    va_start(liste,format);
 
    int w,h;
 
    char texte[512];
    vsprintf(texte,format,liste);
 
    if (TTF_SizeText(font,texte,&w,&h) == 0)
        return h;
    else
        return -1;
}

