/*
 * TextFile.cpp
 *
 *  Created on: Jan 27, 2010
 *      Author: johannes
 */

#include "TextFile.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
TextFile::TextFile() {
	length = 0;

}
void  TextFile::read(char * filename){

    strcpy(this->filename,filename);
	FILE *fp;
	fp = fopen(filename,"rt");

    fseek(fp, 0, SEEK_END);
    this->length = ftell(fp);
    rewind(fp);
	this->content = (char *)malloc(sizeof(char) * (this->length+1));
	this->length = fread(this->content, sizeof(char), this->length, fp);
	this->content[this->length] = '\0';

	fclose(fp);
	return;
}

bool TextFile::isEmpty()
{
	if (length <= 0 )
		return true;
	else
		return false;
}

void TextFile::print()
{
	if (!isEmpty()){
		printf("%s",content);
	}
}

TextFile::~TextFile() {
	// TODO Auto-generated destructor stub
}
