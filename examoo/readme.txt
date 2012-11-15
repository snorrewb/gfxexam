/****************************************\
*	Graphics programming home exam		 *
* Snorre Brecheisen (101023)			 *
* 10HBSPA								 *
\****************************************/
/****************************************\
IMPORTANT INFORMATION
Much of this code is based on Nils'
examples from fronter and the code handed
out with the exam, as well as drawing
heavily from our previous assignments in
OpenGL. There has also been collaboration
with classmates in several areas. The
camera is from the net, as described in
examoo.cpp and camera.h.

I originally coded this without any kind
of OO design, and later converted it to
its current form. Because of this, there
are some odd design choices where I have
either not completed the conversion to OO,
or not wanted to rewrite a certain
segment.

Explanation of variables and functions are
in their respective *.h files. Aside from
this, *.cpp files are only sparsely
commented where I felt it was necessary.
\****************************************/
/****************************************\
KNOWN BUGS/ISSUES
-	Slider buttons sometimes do not
	readjust correctly when resizing the
	window.
-	If window width or height is 10px at
	any point, slider(s) will draw
	incorrectly for the remainder of
	runtime. Not likely to be a problem.
-	Shadow does not look good if camera is
	too far up.
-	Camera does not support multiple
	commands at once.
\****************************************/
/****************************************\
CAMERA CONTROLS (also found in examoo.cpp)
Adjust speed:	+/-
Move forwards:	w
Move backwards:	s	
Spin left:		left
Spin right:		right
Spin down:		up
Spin up:		down
Move up:		z
Move down:		c
Strafe left:	a
Strafe right:	d
Roll left:		q
Roll right:		e
\****************************************/