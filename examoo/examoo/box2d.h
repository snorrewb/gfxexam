/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  *	2D box class for the GUI, used for
  *	making sliders.
  *************************************/
#ifndef BOX2D_H
#define BOX2D_H

class Box2d {
	private:
		int color, x, y, w, l;				//Position and dimensions of 2D box
	public:
		Box2d (float w, float l, int c);	//Initiate 2D box
		void draw(int x, int y);			//Draws 2D box
		void draw(int x, int y, int i);		//Draws 2D slider
		int getx();							//Returns value of x
		int gety();							//Returns value of y
		int getw();							//Returns value of w
		int getl();							//Returns value of l
};

#endif