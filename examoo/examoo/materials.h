/** Graphics programming home exam
  * Snorre Brecheisen (101023)
  * 10HBSPA
  **************************************
  * IMPORTANT:
  *	View the readme (readme.txt,
  *	included with the project) first!
  **************************************
  * Materials used by the program
  *************************************/
#ifndef MATERIALS_H
#define MATERIALS_H

//Colored materials
static float material [5][4] = {{0.8f, 0.8f, 0.8f, 1.0f},		//grey (for craft)
								{0.0f, 0.0f, 1.0f, 0.9f},		//blue (transparent, for plane)
								{0.0f, 0.0f, 1.0f, 1.0f},		//blue (for yaw button)
								{1.0f, 0.0f, 0.0f, 1.0f},		//red (for roll button)
								{0.6f, 0.6f, 0.6f, 1.0f}};		//grey (for sliders)
#endif