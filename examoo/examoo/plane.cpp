/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  *************************************/
#include "plane.h"
#include <string.h>
#include <glew.h>
#include <glut.h>
#include "planeNormals.h"
#include "planeVertices.h"
#include "planeTexCoords.h"
#include "materials.h"

Plane::Plane (float x, float y, float z, GLuint ID) {
	this->x = x;
	this->y = y;
	this->z = z;
	imageID = ID;

	float temp [] = {
		-x, y, z,
		x, y, z,
		x, y,-z,
		-x, y,-z
	};
	memcpy(_pvertices, temp, sizeof(float)*(4*3));

	glGenBuffers(1, &vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *(4*3), _pvertices, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glGenBuffers(1, &normalID);
	glBindBuffer(GL_ARRAY_BUFFER, normalID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *(4*3), _pnormals, GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glGenBuffers(1, &texCoordsID);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (4*2), _ptexCoords, GL_STATIC_DRAW);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glGenBuffers(1, &pboID);
	glBindTexture(GL_TEXTURE_2D, imageID);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, /*texturew*/1280 * /*textureh*/850 * 3, 0, GL_STATIC_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Plane::draw() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material[1]);
		////////////////////////////////////////
		GLfloat textures[] = { 1, animation-0.1,  0, animation-0.1,  0, animation,  1, animation };
		animation -= 0.0005;
		if(animation < 0.1){	// If it's passed the size of the picture.
			animation = 0.4;
		}
		glBindBuffer(GL_ARRAY_BUFFER, texCoordsID);//
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (4*2), textures, GL_STATIC_DRAW);
		////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, imageID);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexID);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, normalID);
		glNormalPointer(GL_FLOAT, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, texCoordsID);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		// activate vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		// draw a plane
		glDrawArrays(GL_QUADS, 0, 4);
		// deactivate vertex arrays after drawing
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}