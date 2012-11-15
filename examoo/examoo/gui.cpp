/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  *************************************/
#include "gui.h"
#include <glew.h>
#include <glut.h>
#include "box2d.h"
#include "materials.h"

GUI::GUI(int ws, int hs, int wb, int hb, int cs, int cb1, int cb2){
	boxes[0] = new Box2d(wb, hb, cb1);
	boxes[1] = new Box2d(ws, hs, cs);
	boxes[2] = new Box2d(hb, wb, cb2);
	boxes[3] = new Box2d(hs, ws, cs);
}
void GUI::drawBox(int x, int y, int i){
	boxes[i]->draw(x, y);
}
void GUI::drawSlide(int x, int y, int i, int l){
	boxes[i]->draw(x, y, l);
}
int GUI::getx(int i){
	return boxes[i]->getx();
}
int GUI::gety(int i){
	return boxes[i]->gety();
}
int GUI::getw(int i){
	return boxes[i]->getw();
}
int GUI::getl(int i){
	return boxes[i]->getl();
}