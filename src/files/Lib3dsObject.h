/*
 * Lib3ds.h
 *
 *  Created on: Jan 11, 2010
 *      Author: johannes
 */

#ifndef LIB3DS_H_
#define LIB3DS_H_
#include <lib3ds/mesh.h>
//#include <lib3ds.h>
#include <lib3ds/file.h>
#include <lib3ds/material.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <string.h>
#include "../objs/object.h"
class Lib3dsObject :  public Object{
public:
	char * filename;
	unsigned int m_TotalFaces;
	// GLuint m_VertexVBO, m_NormalVBO;
	Lib3dsFile * m_model;
	Lib3dsVector * vertices;
	Lib3dsVector * normals;
	Lib3dsVector * colors;

	virtual ~Lib3dsObject();


// Copy vertices and normals to the memory of the GPU


	void getMaterial(){
		lib3ds_file_dump_materials(m_model);

	}
	void  CreateVBO()
	{
		getMaterial();
		// Calculate the number of faces we have in total
		GetFaces();

		// Allocate memory for our vertices and normals
		  vertices = new Lib3dsVector[m_TotalFaces * 3];
		  normals = new Lib3dsVector[m_TotalFaces * 3];
		  colors = new Lib3dsVector[m_TotalFaces * 3];

		Lib3dsMesh * mesh;
		unsigned int FinishedFaces = 0;
		// Loop through all the meshes
		for(mesh = m_model->meshes;	mesh != NULL;mesh = mesh->next )
		{
			//lib3ds_mesh_dump(mesh);

			//lib3ds_mesh_calculate_vertex_normals(mesh,&normals[FinishedFaces*3]);
			lib3ds_mesh_calculate_normals(mesh, &normals[FinishedFaces*3]);
			// Loop through every face
			for(unsigned int cur_face = 0; cur_face < mesh->faces;cur_face++)
			{

				Lib3dsFace * face = &mesh->faceL[cur_face];
				Lib3dsMaterial * material  = lib3ds_file_material_by_name(m_model, face->material);
			float r = material->ambient[0];
			float g = material->ambient[1];
			float b = material->ambient[2];

			printf("Material %f %f %f \n",r,g,b);

				for(unsigned int i = 0;i < 3;i++)
				{
					for (int j = 0 ; j < 3; j++ )
						colors[FinishedFaces*3+i][j] = material->ambient[j];


					memcpy(&colors[FinishedFaces*3 + i], material->ambient, sizeof(Lib3dsVector));
					memcpy(&vertices[FinishedFaces*3 + i], mesh->pointL[face->points[i]].pos, sizeof(Lib3dsVector));
				}
				FinishedFaces++;
			}
		}

		// Generate a Vertex Buffer Object and store it with our vertices
		//glGenBuffers(1, &m_VertexVBO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces, vertices, GL_STATIC_DRAW);

		// Generate another Vertex Buffer Object and store the normals in it
		//glGenBuffers(1, &m_NormalVBO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces, normals, GL_STATIC_DRAW);

		// Clean up our allocated memory
		//delete vertices;
		//delete normals;

		// We no longer need lib3ds
		//lib3ds_file_free(m_model);
		//m_model = NULL;
	}

	void draw(){
		beginDraw();
		//Lib3dsVector * vertices = new Lib3dsVector[m_TotalFaces * 3];
		//Lib3dsVector * normals = new Lib3dsVector[m_TotalFaces * 3];
				// if (f % 2 == 0)
				//	glBegin(GL_QUADS );
				// else
				/*
				 *
				glBegin(GL_TRIANGLES );
					glBegin(GL_LINES );
				 */

			for(int f = 0 ;f < m_TotalFaces ;f++)
			{
				glBegin(GL_POLYGON );
				for(unsigned int i = 0; i < 3;i++)
				{
					glColor3fv(colors[f*3+i ] );
					glNormal3fv(normals[f*3 + i ]);
					glVertex3fv(vertices[f*3 + i] );
				}
				glEnd();
			}

endDraw();
	}
// Count the total number of faces this model has
	void  GetFaces()
	{

		m_TotalFaces = 0;
		Lib3dsMesh * mesh;
		// Loop through every mesh
		for(mesh = m_model->meshes; mesh != NULL; mesh = mesh->next)
		{
			// Add the number of faces this mesh has to the total faces
			m_TotalFaces += mesh->faces;
		}
	}

	Lib3dsObject(char * filename)
	{
		FILE *file;
		//this->filename = filename;
		file = fopen(filename, "rb");
		m_model = lib3ds_file_load(filename);
			if (!m_model)
			{
					printf( "***ERROR***\nLoading file failed: %s\n", filename);
					//exit(1);
			}else
			{
			CreateVBO();
			printf("Gsichter : %d\n",m_TotalFaces);
			}
	}

	void calc(GLfloat time)
	{

	}

	Object *  clone()
	{
		return 0;
	}

};
#endif /* LIB3DS_H_ */
