/*
 * FileBrowser.h
 *
 *  Created on: Mar 18, 2010
 *      Author: johannes
 */

#ifndef FILEBROWSER_H_
#define FILEBROWSER_H_
#include "objs/object.h"
#include "objs/Ball.h"
#include "files/Directory.h"
#include "misc/Text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class FileBrowser : public Object {
public:

	Directory * dir;
	Text * writer;
	char ** dirNames;
	int countSubDirs;
	char ** fileNames;
	int countFiles;

	Ball * selector;
	int seletedFolder;


	FileBrowser()
	{
		selector = new Ball(1,0,1,1);
		seletedFolder = -1;
		dir = new Directory();
		openDir("/");
		writer = new Text();
		last_calc_time = 0;
	}

	void openDir(string s){

		dir->openDirectory((char*)s.c_str());
		dirNames = dir->listSubDirs(&countSubDirs);
		fileNames = dir->findFiles("",&countFiles);
	//	printf("%s\n",dir->path);
	}

	void draw(){
		int i ;
		writer->pos[1] = 0;
		writer->setColor3f(1,1,1);
		for (i = 0; i < countSubDirs; ++i)
		{
			string s = dirNames[i];
			writer->text = s;

			writer->draw();
			writer->pos[1]+= 5;
		}
		writer->setColor3f(0,0,1);
		for (i = 0; i < countFiles; ++i)
		{
			string s = fileNames[i];
			writer->text = s;

			writer->pos[1]+= 10;
			writer->draw();
		}
			selector->setPos3f(-2.5,seletedFolder*5,0);
		selector->draw();
	}

	void checkSelectedFolder(){
		if (seletedFolder > countSubDirs)
			seletedFolder = 0;
	}
	void calc(GLfloat time){
		checkSelectedFolder();
		static GLfloat delta  = 0;
		static int newFolderChoosen = 0;
		delta+= time - last_calc_time;

		if (delta > 1000 && !newFolderChoosen  && 0){
			srand(time);
			seletedFolder = rand()%countSubDirs;
			newFolderChoosen = 1;
		}
		if (delta > 2000 && 0)
		{
			char newdir[1024];
			sprintf(newdir,"%s/%s",dir->path,dirNames[seletedFolder]);
			openDir(newdir);
			newFolderChoosen = 0;
			delta = 0;
		}

		last_calc_time = time;
	}

	void keyPressed(GLint key)
	{
	}

	void specialKeyPressed(GLint key)
	{
			int max ;
			int pos = 0;
		switch(key)
		{
			case GLUT_KEY_LEFT :
				max = strlen(dir->path);
				for (int i = max ; i > 0 ; i --)
				{
					if (dir->path[i] == '/'){
					pos = i ;
					break;
					}
				}
				for (int i = pos; i < max; ++i) {
					dir->path[i] = '\0';
				}
				openDir(dir->path);
				break;
			case GLUT_KEY_UP :  seletedFolder = (seletedFolder +1 ) %countSubDirs; break;
			case GLUT_KEY_RIGHT :
				char newdir[1024];
				sprintf(newdir,"%s/%s",dir->path,dirNames[seletedFolder]);
				openDir(newdir);
				break;
			case GLUT_KEY_DOWN :
				if (seletedFolder > 0 )
					seletedFolder --;
				else
					seletedFolder = countSubDirs - 1;

				break;

			}

	}
	virtual Object *  clone(){ return new FileBrowser();}
	virtual ~FileBrowser();
};

#endif /* FILEBROWSER_H_ */
