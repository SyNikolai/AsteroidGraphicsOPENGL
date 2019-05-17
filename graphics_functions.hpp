#ifndef GRAPHICS_FUNCTIONS_HPP_
#define GRAPHICS_FUNCTIONS_HPP_
#include <GL/glut.h>  				// GLUT, include glu.h and gl.h
#include "data.hpp"
void create_data_arrays();
void initGL();
void display();
void processSpecialKeys(int key, int xx, int yy);
void timer(int value);
void reshape(GLsizei width, GLsizei height);

#endif /* GRAPHICS_FUNCTIONS_HPP_ */
