/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  *	Controller class for the GUI. This
  *	is supposed to handle more of the
  *	slider functionality, but I didn't
  *	have time to finish it.
  *************************************/
#ifndef GUI_H
#define GUI_H

#include "box2d.h"

class GUI {
	private:
		Box2d *boxes [4];							//Array of GUI boxes
	public:
		GUI (int ws, int hs, int wb, int hb, int cs, int cb1, int cb2);	//Creates all GUI boxes
		void drawBox(int x, int y, int i);			//Draw GUI box in boxes[i]
		void drawSlide(int x, int y, int i, int l);	//Draw GUI slider in boxes[i]
		int getx(int i);							//Get x from box i
		int gety(int i);							//Get y from box i
		int getw(int i);							//Get w from box i
		int getl(int i);							//Get l from box i
};

#endif