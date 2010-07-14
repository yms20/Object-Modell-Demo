/*
 * Directory.h
 *
 *  Created on: Jan 12, 2010
 *      Author: johannes
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_
#include <dirent.h>

class Directory {
public:

	char path[1024];
	void toLowerCase(char * str);
	void  openDirectory(char * dirName);
	char ** findFiles(char * pattern, int * count);
	char  ** listSubDirs( int * count);
	Directory();
	virtual ~Directory();
};

#endif /* DIRECTORY_H_ */
