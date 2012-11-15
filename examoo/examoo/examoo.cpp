/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  * Main.
  **************************************
  *	CAMERA CONTROLS (also in readme.txt)
  *	Adjust speed:	+/-
  *	Move forwards:	w
  *	Move backwards:	s	
  *	Spin left:		left
  *	Spin right:		right
  *	Spin down:		up
  *	Spin up:		down
  *	Move up:		z
  *	Move down:		c
  *	Strafe left:	a
  *	Strafe right:	d
  *	Roll left:		q
  *	Roll right:		e
  *************************************/
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <time.h>
#include <glew.h>
#include <glut.h>
#include "examoo.h"
#include "camera.h"
#include "craft.h"
#include "gui.h"
#include "plane.h"

#pragma comment(lib,"glew32.lib") 
using namespace std;

Craft *craft;			//Declaring our classes
GUI *gui;
Plane *plane;
CCamera *camera;		//Adapted from code by http://www.codecolony.de (provided to me by Magnus Duun)

time_t rolltime1 = 0, rolltime2 = 0, yawtime1 = 0, yawtime2 = 0;	//Variables for timing doubleclicks

int main (int argc, char* argv[]) {
	atexit(close);
	printf("Adjust speed:\t+/-\n");
	printf("Move forwards:\tw\n");
	printf("Move backwards:\ts\n");
	printf("Spin left:\tleft\n");
	printf("Spin right:\tright\n");
	printf("Spin down:\tup\n");
	printf("Spin up:\tdown\n");
	printf("Move up:\tz\n");
	printf("Move down:\tc\n");
	printf("Strafe left:\ta\n");
	printf("Strafe right:\td\n");
	printf("Roll left:\tq\n");
	printf("Roll right:\te\n");
	//These 5 functions must be present
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Exam; GFX Programming");

	//Callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//Setting parameters
	glewInit();
	initOpenGL();
	printf("Version : %s\n", (char *) glGetString(GL_VERSION));
	//This function begins event processing
	glutMainLoop();
	return 0;
}
void initOpenGL(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//White background
	//Funksjonene under setter koordinatene til systemet vi vil tegne i
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 1, 0.1, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera = new CCamera;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	readRaw("ocean.raw");
	craft = new Craft(craftx, crafty, craftz, imageID);
	plane = new Plane(planex, planey, planez, imageID);
	gui = new GUI(redsliderlength, 10, buttonlong, buttonshort, 4, 3, 2);
}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_POSITION, lightsource);
	
	glLoadIdentity();
	camera->Render();
	
	glPushMatrix();
	{
		scene();

		ortho();
	}
	glPopMatrix();
	
	glutSwapBuffers();
}
void reshape(int bredde, int hoyde){
	setVars(bredde, hoyde);
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(50, (GLfloat)w / (GLfloat)h, 0.1, 10000);
	glMatrixMode (GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y){
	switch (key) 
	{
	case 27:		//ESC
		exit(0);
		break;
	case 'a':
		camera->strafe(-5);
		break;
	case 'd':
		camera->strafe(5);
		break;
	case 'w':		
		camera->MoveForwards(-5);
		break;
	case 's':		
		camera->MoveForwards(5);
		break;	
	case 'c':
		camera->Move(F3dVector(0.0,-5,0.0));
		break;
	case 'z':
		camera->Move(F3dVector(0.0,5,0.0));
		break;
	case '+':		//increase glide
		camera->glide(1);
		break;
	case '-':		//decrease glide
		camera->glide(-1);
		break;
	case 'q':		//roll left
		camera->roll(5);
		break;
	case 'e':		//roll right
		camera->roll(-5);
		break;
	default:
		break;
	}
}
void idle(){
	glutPostRedisplay();
}
void special(int key, int x, int y){
	switch(key)  {					
		case GLUT_KEY_LEFT:			
			camera->yaw(5.0);				
			break;
		case GLUT_KEY_DOWN:		
			camera->pitch(5.0);
			break;
		case GLUT_KEY_UP:		
			camera->pitch(-5.0);
			break;
		case GLUT_KEY_RIGHT:
			camera->yaw(-5.0);
			break;
	}
}
void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {	//for resetting of sliders
		time(&rolltime1);
		time(&yawtime1);
		rolltimediff = difftime(rolltime1,rolltime2);
		yawtimediff = difftime(yawtime1,yawtime2);
		if (inRollButton(x, y)){
			rolltime2 = rolltime1;
			if (rolltimediff < 0.02) {
				rolltimediff = rolltime1 = rolltime2 = 0;
				red = redslidermid;
				phi = 0;
			}
		} else if (inYawButton(x, y)){
			yawtime2 = yawtime1;
			if (yawtimediff < 0.02) {
				yawtimediff = yawtime1 = yawtime2 = 0;
				blue = blueslidermid;
				theta = 0;
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {	//for moving of sliders
		if (inRollButton(x, y)){
			startx = x;
			starty = y;
			roll = true;
		} else if (inYawButton(x, y)){
			startx = x;
			starty = y;
			yaw = true;
		} else {
			roll = yaw = false;
		}
	} else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		roll = yaw = false;
	}
}
void motion(int x, int y){
	if (roll) {	//moves red (right) slider
		if (red > 0.5*redslidermid || red < 1.5*redslidermid){
			red += y - starty;
			phi += y - starty;
			if (phi <= -180) {
				phi = -179;
			} else if (phi >= 180) {
				phi = 179;
			}
			startx = x;
			starty = y;
		}
		if (red >= 1.5*redslidermid){
			red = (1.5*redslidermid)-1;
		} else if (red <= 0.5*redslidermid){
			red = (0.5*redslidermid)+1;
		}
	} else if (yaw) { //moves blue (bottom) slider
		if (blue > 0.5*blueslidermid || blue < 1.5*blueslidermid){
			theta += (x - startx)/3;
			blue += x - startx;
			if (theta <= -45) {
				theta = -44;
			} else if (theta >= 45) {
				theta = 44;
			}
			startx = x;
			starty = y;
		}
		if (blue >= 1.5*blueslidermid){
			blue = (1.5*blueslidermid)-1;
		} else if (blue <= 0.5*blueslidermid){
			blue = (0.5*blueslidermid)+1;
		}
	}
}
void stencil(){
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // set false color mask
	glDisable(GL_DEPTH_TEST);			// turn off depth
	glEnable(GL_STENCIL_TEST);			// enable stencils

	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glPushMatrix();
	{
		plane->draw();						// the object which the shadow is drawn on
	}
	glPopMatrix();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightsource);
		craft->draw(theta, phi);
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, lightsource);

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void shadow(){
	glEnable(GL_STENCIL_TEST);			// enable stencils
	glStencilFunc(GL_EQUAL, 1, 0xff);	// set the stencil function properties
	glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO); // removes chance of 2 shadows or more from same object
	glEnable(GL_POLYGON_OFFSET_FILL);

	glEnable(GL_BLEND);					// enable blend functions
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);				// turn off light
	glColor4f(0.0, 0.0, 0.0, 0.6);		// 60% shadow

	float * m = localLightSource(0, 1, 0, lightsource[0], lightsource[1], lightsource[2]);

	glPushMatrix();
	{
		glTranslatef(0, 1, 0);		// moves the shadow abit above the plane
		glTranslatef(lightsource[0], lightsource[1], lightsource[2]);
		glMultMatrixf(m);
		glTranslatef(-lightsource[0], -lightsource[1], -lightsource[2]); 
		
		glPushMatrix();
		{
			craft->draw(theta, phi);// draw the shadow in the form of the aircraft
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_BLEND);				// disable blend again
	glEnable(GL_LIGHTING);				// turn on lights again
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_STENCIL_TEST);
}
void close(){

}
void drawControls(){
	gui->drawBox(redslidermax,red, 0);
	gui->drawSlide(redslidermax,redslidermid, 1, redsliderlength);
	
	gui->drawBox(blue, blueslidermax, 2);
	gui->drawSlide(blueslidermid,blueslidermax, 3, bluesliderlength);
}
void orthoOn(){	//turns on ortho
	glMatrixMode(GL_PROJECTION);	// projection matrix. 
	glPushMatrix();
	glLoadIdentity();				// loads the identity matrix. 
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);				// turns upside down. 
	glTranslatef(0, -h, 0);			// displays it correctly. 
	glMatrixMode(GL_MODELVIEW);		// modelview matrix. 
}
void orthoOff(){	//turns off ortho
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
float *localLightSource(int nx, int ny, int nz, float lx, float ly, float lz)
{
	float dotLys = nx * (lx - offsetX) + ny * (ly - offsetY) + nz * (lz - offsetZ); 
	//Col 1
	m[0] = dotLys;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	//Col 2
	m[4] = 0;
	m[5] = dotLys;
	m[6] = 0;
	m[7] = -1; //projection
	//Col 3
	m[8] = 0;
	m[9] = 0;
	m[10] = dotLys;
	m[11] = 0;
	//Col 4
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 0;
	return m;
}
bool inRollButton(int x, int y){	//right slider
	if (((w-75) > x && x > (w-125))&&((red-50) < y && y < (red+50))){
		return true;
	} else {
		return false;
	}
}
bool inYawButton(int x, int y){		//bottom slider
	if (((h-75) > y && y > (h-125))&&((blue-50) < x && x < (blue+50))){
		return true;
	} else {
		return false;
	}
}
void readRaw(char *fileName){
	FILE *file = 0;
	if (!(file = fopen(fileName, "r"))){
		return;
	}
	image = (unsigned char*) malloc(texturew * textureh * 3);
	fread((char *) image, texturew * textureh * 3, 1, file);
	fclose(file);
	setMipMapTexture();
	free(image);
}
void setMipMapTexture(){
	glGenTextures(1, &imageID);
	glBindTexture(GL_TEXTURE_2D, imageID);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texturew, textureh, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, /*GL_MODULATE*/GL_BLEND); //GL_MODULATE, GL_DECAL, GL_BLEND, or GL_REPLACE

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void setVars(int nw, int nh){
	blue = (float)(((float)nw/(float)w)*blue), red = (float)(((float)nh/(float)h)*red);
	w = nw;
	h = nh;
	redslidermax = w-100, blueslidermax = h-100, redslidermid = redsliderlength = h/2, blueslidermid = bluesliderlength = w/2;
}
void ortho(){
	glLoadIdentity();
	orthoOn();
	{
		glPushMatrix();
		{
			glLoadIdentity();
			glDisable(GL_LIGHTING);
			drawControls();
			glEnable(GL_LIGHTING);
		}
		glPopMatrix();
	}
	orthoOff();
}
void scene(){
	stencil();

	plane->draw();
		
	craft->draw(theta, phi);

	shadow();
}