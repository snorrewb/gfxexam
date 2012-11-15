/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  *************************************/
#include "box2d.h"
#include <glew.h>
#include <glut.h>
#include "materials.h"

Box2d::Box2d (float w, float l, int c){
	this->x = 0;
	this->y = 0;
	this->w = w;
	this->l = l;
	this->color = c;
}
void Box2d::draw (int x, int y){
	this->x = x;
	this->y = y;
	glPushMatrix();
	{
		glTranslatef(x,y,0);
		glColor3f(material[color][0], material[color][1], material[color][2]);
		glBegin(GL_QUADS);
		{
			glVertex2f(-(l/2), -(w/2));	//tleft
			glVertex2f(-(l/2), (w/2));	//bleft
			glVertex2f((l/2), (w/2));	//bright
			glVertex2f((l/2), -(w/2));	//tright
		}
		glEnd();
	}
	glPopMatrix();
}
void Box2d::draw (int x, int y, int i){
	this->x = x;
	this->y = y;
	if (w < l) {
		this->l = i;
	} else if (w > l) {
		this->w = i;
	}

	glPushMatrix();
	{
		glTranslatef(x,y,0);
		glColor3f(material[color][0], material[color][1], material[color][2]);
		glBegin(GL_QUADS);
		{
			glVertex2f(-(l/2), -(w/2));	//tleft
			glVertex2f(-(l/2), (w/2));	//bleft
			glVertex2f((l/2), (w/2));	//bright
			glVertex2f((l/2), -(w/2));	//tright
		}
		glEnd();
	}
	glPopMatrix();
}
int Box2d::getx(){
	return x;
}
int Box2d::gety(){
	return y;
}
int Box2d::getw(){
	return w;
}
int Box2d::getl(){
	return l;
}