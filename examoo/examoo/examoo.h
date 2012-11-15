/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  * Declarations for examoo.cpp.
  *************************************/
#ifndef EXAMOO_H
#define EXAMOO_H

void initOpenGL();												//Initiates our OpenGL project
void display(void);												//OpenGL Display function
void reshape(int bredde, int hoyde);							//OpenGL Reshape function
void keyboard(unsigned char key, int x, int y);					//OpenGL Keyboard function
void idle();													//OpenGL Idle function
void special(int key, int x, int y);							//OpenGL Special function
void mouse(int button, int state, int x, int y);				//OpenGL Mouse function
void motion(int x, int y);										//OpenGL Movement function
void close();													//OpenGL Close function

bool inRollButton(int x, int y);								//Checks if cursor is over roll slider button
bool inYawButton(int x, int y);									//Checks if cursor is over yaw slider button
void stencil();													//Sets stencil (for shadows) and draws reflections
void shadow();													//Draws shadows
void orthoOn();													//Enables orthagonal projection (for UI)
void orthoOff();												//Disables orthagonal projection
void drawControls();											//Draws all sliders and buttons
GLuint textureRaw(const char * filename, int wrap);				//Loads *.raw image to a GLuint
float *localLightSource(int nx, int ny, int nz, float lx, float ly, float lz);	//Local lightsource for shadows
void readRaw(char *fileName);									//Loads *.raw image
void setMipMapTexture();										//Sets the mipmaptexture
void setVars(int nw, int nh);									//Sets size vars
void ortho();													//Runs all ortho functions
void scene();													//Draws 3d scene

int w = 800, h = 800;											//Initial size of window
int startx, starty;												//Used for tracking mouse movement
int texturew = 1280, textureh = 850;							//Size of texture
float craftx = 0, crafty = 100, craftz = 0;						//Initial values for craft
float planex = 800, planey = 0, planez = 800;					//Initial values for plane

int blue = w/2, red = h/2;										//Starting position of sliders
int redslidermax = w-100, blueslidermax = h-100,				//How near edge sliders are drawn
	redslidermid = w/2, blueslidermid = h/2,					//Center of sliders
	redsliderlength = w/2, bluesliderlength = h/2;				//Length of sliders
const int buttonlong = 80, buttonshort = 40;					//Dimensions of buttons
bool roll = false, yaw = false;									//Bools for slider movement
float rolltimediff = 0, yawtimediff = 0;						//Variables for timing doubleclicks

GLuint imageID;													//GLuint for buffer objects
unsigned char* image;											//Char for reading raw image

static float offsetX = -16, offsetY = 0, offsetZ = -16;			//Variables for lighting
static float phi = 0, theta = 0;								//Variables for pitch and yaw

float m[16];													//For localLightSource()
static float lightsource [4] =  {350, 350, 350, 1};				//Light position

#endif