/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  * Spacecraft object
  *************************************/
#ifndef CRAFT_H
#define CRAFT_H

#include <glew.h>
#include <glut.h>

class Craft {
	private:
		float x, y, z;									//Position of spacecraft
		GLuint vertexID, normalID, texCoordsID, imageID, pboID;
	public:
		Craft (float x, float y, float z, GLuint ID);	//Initiate spacecraft
		void draw(int yaw, int roll);					//Draws spacecraft
};

#endif