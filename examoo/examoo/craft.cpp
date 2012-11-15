/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  *************************************/
#include "craft.h"
#include <glew.h>
#include <glut.h>
#include "craftNormals.h"
#include "craftVertices.h"
#include "craftTexCoords.h"
#include "materials.h"

Craft::Craft (float x, float y, float z, GLuint ID) {
	this->x = x;
	this->y = y;
	this->z = z;
	imageID = ID;

	glGenBuffers(1, &vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *(1500*3), _cvertices, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glGenBuffers(1, &normalID);
	glBindBuffer(GL_ARRAY_BUFFER, normalID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *(1500*3), _cnormals, GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glGenBuffers(1, &texCoordsID);//
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsID);//
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (1500*2), _ctexCoords, GL_STATIC_DRAW);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glGenBuffers(1, &pboID);
	glBindTexture(GL_TEXTURE_2D, imageID);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, /*texturew*/1280 * /*textureh*/850 * 3, 0, GL_STATIC_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Craft::draw(int yaw, int roll) {
	glPushMatrix();
	{
		glTranslatef(x,y,z);
		glRotatef(-90, 1, 0, 0);
		glRotatef(yaw, 0, 0, 1);
		glRotatef(roll, 0, 1, 0);

		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		{
			glMaterialfv(GL_FRONT, GL_DIFFUSE, material[0]);
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
			// draw a craft
			glDrawArrays(GL_TRIANGLES, 0, 1500);
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
	glPopMatrix();
}