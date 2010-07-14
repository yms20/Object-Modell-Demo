#include "texture.h"
#include <Magick++/Include.h>
#include <Magick++/Image.h>
#include <Magick++/Pixels.h>
#include <Magick++/STL.h>
#include <math.h>
using namespace Magick;

void Texture::magickLoad(){
	//if (fileName.size() > 0 )
	{
		Image  hallo(fileName);
		int h = hallo.baseRows();
		int w = hallo.baseColumns();
		printf("w %d, h %d \n",w,h);
		PixelPacket * ps = hallo.getPixels(0,0,w,h);
		unsigned char  rawData[w*h*3];// = (unsigned char *)malloc(w*h*3 * sizeof(char));

		printf("%s\n",hallo.format().c_str());
		int i =0;
		GLfloat t =0 ;
		for (i  = 0 ; i < (w*h) ; i ++)
		{
			rawData[i*3 + 0 ] = (unsigned char) (ps[i].red/256);
			rawData[i*3 + 1 ] = (unsigned char) (ps[i].green/256);
			rawData[i*3 + 2 ] = (unsigned char) (ps[i].blue/256);

			t +=  (2*M_PI)/(w);

			//rawData[i*3 + 0 ] =   127 + (int)(127* sin(t));
			//rawData[i*3 + 1 ] =  0;//127 + 127* sin(t);
			//rawData[i*3 + 2 ] =  0;//127 + 127* cos(t);
		//	printf("%d ",rawData[i*3 + 0 ]);
		}
		// First attempt to bind the texture;
		glGenTextures( 1, &textureID );
		//textureID = 0;
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, textureID );
	//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, 1, w,  h, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, rawData);
		printf("DeBUG\n");
	}
}

void  Texture::loadImageLQ( char * filename)
{
      image = IMG_Load(filename);
      GLenum texture_format;
      GLint nOfColors = image->format->BytesPerPixel;

       if (nOfColors == 4)     // contains an alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = 0x80E1;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = 0x80E0;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }

    // Scale Image Down
	int scaler= 8;
	int w = image->w / scaler;
	int h = image->h / scaler;

	unsigned char smalData[w * h * nOfColors];
	unsigned char * pixels = (unsigned char*)image->pixels;

	for (int i =0 ; i < h ; i ++)
	{
		for (int j =0; j < w  ; j++)
		{
			for (int n = 0 ; n < nOfColors ; n++)
			{
				smalData[( (i  * w) + j ) * nOfColors  +n ] =
					pixels[( (i * scaler *  image->w ) + (j * scaler) ) * nOfColors   + n];
			}
		}
	}

	// Bind the texture object
    glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, w, h, 0,
                      texture_format, GL_UNSIGNED_BYTE,smalData );
      width = image->w;
      height = image->h;
     printf("H %d , W: %d  texID %d\n", image->w, image->h,textureID);

     pixels = 0;
    // free (smalData);
    // free (image);

}
void  Texture::loadImage( char * filename)
{
	printf("Texture Loader %s\n",filename);
      image = IMG_Load(filename);
      GLenum texture_format;
      GLint nOfColors = image->format->BytesPerPixel;

       if (nOfColors == 4)     // contains an alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = 0x80E1;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = 0x80E0;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }
    glGenTextures( 1, &textureID );
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, textureID );

	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        //REpaeting
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, image->w, image->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, image->pixels );
      width = image->w;
      height = image->h;
     printf("H %d , W: %d  texID %d\n", image->w, image->h,textureID);
}


void Texture::enable()
{

//printf("BIND and ENABLE TEXTURE\n");
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D, textureID);

}
void Texture::disable()
{
   glDisable(GL_TEXTURE_2D);
}
