/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  * Plane object
  *************************************/
#ifndef PLANE_H
#define PLANE_H

#include <glew.h>
#include <glut.h>

class Plane {
	private:
		float x, y, z;									//Dimensions
		GLuint vertexID, normalID, texCoordsID, imageID, pboID;
	public:
		Plane (float x, float y, float z, GLuint ID);	//Initiate plane
		void draw();									//Draws plane
};

#endif