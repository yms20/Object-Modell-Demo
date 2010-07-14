/*
 * Directory.cpp
 *
 *  Created on: Jan 12, 2010
 *      Author: johannes
 */

#include "Directory.h"
#include <string.h>
#include <stdio.h>

#include <malloc.h>
#include <sys/types.h>
#include <ctype.h>


Directory::Directory() {

}

Directory::~Directory() {
}

void  Directory::openDirectory(char * dirName)
{
	strcpy(this->path,dirName);
}

void Directory::toLowerCase(char * str)
{
	int cnt = strlen(str);
	char * p = str;
	for (int i = 0 ; i < cnt; i++)
	{
		if (*p >= 'A' && *p <= 'Z')
			*p += 32;
		p++;
	}
}
char * *  Directory::findFiles(char * pattern , int * count )
{
	int cnt = 0 ;
	 DIR *dp = opendir(path);
	struct dirent *ep;

	// Eintraege Finden
	while (ep = readdir (dp))
	{
		char name[128];
		strcpy(name,ep->d_name);
		toLowerCase(name);
		//printf("%s\n",name);
	  if (strstr(name,pattern) && ep->d_type == 8 && name[strlen(name)-1] != '.' )
	  {
		  cnt ++;
	  }
	}
	// Speicher Reservieren
	char * * result;
	result = (char * * ) malloc( sizeof (char *) *  cnt);
	for (int i = 0 ; i < cnt ; i ++)
		result[i] = (char * )malloc(256 * sizeof(char ));

	//Eintraege in ergebnisarry schreiben
	cnt = 0;
	dp = opendir(path);
	while (ep = readdir (dp))
	{
		char name[128];
		strcpy(name,ep->d_name);
		toLowerCase(name);
	  if (strstr(name,pattern) && ep->d_type == 8 && name[strlen(name)-1] != '.' )
	  {
		  strcpy(result[cnt],ep->d_name);
		  cnt ++;
	  }
	}
	// Anzalh eintraege uebertragen
	*count = cnt;
	return result;
}

char * *  Directory::listSubDirs(  int * count )
{
	int cnt = 0 ;
	 DIR *dp = opendir(path);
	struct dirent *ep;

	// Eintraege Finden
	while (ep = readdir (dp))
	{
	 // printf("%d\n",ep->d_type); // 4: Direcory  8 : File
	  if (ep->d_type == 4 )
	  {
		  cnt ++;
	  }
	}
	char * * result;
	// Speicher Reservieren
	result = (char * * ) malloc( sizeof (char *) *  cnt);
	for (int i = 0 ; i < cnt ; i ++)
		result[i] = (char * )malloc(256 * sizeof(char ));

	//Eintraege in ergebnisarry schreiben
	cnt = 0;
	dp = opendir(path);
	while (ep = readdir (dp))
	{
	 // printf("%d\n",ep->d_type); // 4: Direcory  8 : File
	  if (ep->d_type == 4 )
	  {
		  strcpy(result[cnt],ep->d_name);
		  cnt ++;
	  }
	}
	// Anzalh eintraege uebertragen
	*count = cnt;
 return result;
}
