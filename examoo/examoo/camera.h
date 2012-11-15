/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  *************************************/
 /* While I have made/edited some of the
  *	functions here, the main
  *	functionality was taken from
  *	http://www.codecolony.de
  *************************************/
#include <glut.h>		// Need to include it here because the GL* types are required
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0
/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////
struct SF3dVector{  //Float 3d-vect, normally used
	GLfloat x,y,z;
};
struct SF2dVector{
	GLfloat x,y;
};
class CCamera{
private:
	SF3dVector Position;
	SF3dVector ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
	int glidespeed;
public:
	CCamera();				//inits the values (Position: (0|100|600) Target: (0|-0.2|-1) )
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move (SF3dVector Direction);
	void RotateXYZ (SF3dVector Angles);
	void MoveForwards (GLfloat Distance);
	void strafe (GLfloat Distance);	//Strafe camera
	void yaw (GLfloat y);		//Sets camera yaw
	void roll (GLfloat z);		//Sets camera roll
	void pitch (GLfloat x);		//Sets camera pitch
	void glide (GLfloat g);		//Sets camera glide speed
};
SF3dVector F3dVector (GLfloat x, GLfloat y, GLfloat z);
SF3dVector AddF3dVectors (SF3dVector * u, SF3dVector * v);
void AddF3dVectorToVector (SF3dVector * Dst, SF3dVector * V2);