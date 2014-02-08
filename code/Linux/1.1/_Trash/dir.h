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
#if !defined _DIR_
#define _DIR_

 #include "iblock.h"

#define FDNLEN  10                      /* length of file name + 1      */
 #define NFDES   20                      /* number of files per directory*/

struct  fdes    {                       /* description of each file     */
     long        fdlen;                  /* length in bytes              */
    IBADDR      fdiba;                  /* first index block            */
     char        fdname[FDNLEN];         /* zero-terminated file name    */
    long mtime;
    unsigned int is_directory : 1;
 };

 struct  dir     {
    DBADDR dir_block;
    
       int     d_iblks;                /* i-blocks on this disk        */
        DBADDR  d_fblst;                /* pointer to list of free blks */
        IBADDR  d_filst;                /* pointer to list of free iblks*/
        int     d_id;                   /* disk identification integer  */
        int     d_nfiles;               /* current number of files      */
       struct  fdes    d_files[NFDES]; /* descriptions of the files    */
 };

 struct  freeblk {                       /* shape of block on free list  */
         DBADDR  fbnext;                 /* address of next free block   */
 };
 
 #endif /* _DIR_ */

