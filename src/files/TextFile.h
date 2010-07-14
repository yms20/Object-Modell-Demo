/*
 * TextFile.h
 *
 *  Created on: Jan 27, 2010
 *      Author: johannes
 */

#ifndef TEXTFILE_H_
#define TEXTFILE_H_

class TextFile {
public:
	TextFile();
	// Reads Text file Instantly
	TextFile(char * filename);
	char * filename;
	char * content;
	int length;

	// Reads out a text file and stores content in this->content
	void read(char * filename);
	// Prints out the content
	void print();
	// Returns true if no Text is stored in cotent
	bool isEmpty();

	virtual ~TextFile();
};

#endif /* TEXTFILE_H_ */
