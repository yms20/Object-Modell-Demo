/*
 * SkySkraper.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: johannes
 */

#include "SkySkraper.h"


SkySkraper::~SkySkraper() {
	// TODO Auto-generated destructor stub
}
void SkySkraper::draw()
{
	beginDraw();


	endDraw();
}

void SkySkraper::calc(GLfloat time )
{
	init();
	Rect * r;
	for (int i = 0; i < 4; ++i) {
		r = getSide(i);
		r->texrepeat[0]  = r->dim[0];
		r->texrepeat[1]  = r->dim[1];
	}

}
