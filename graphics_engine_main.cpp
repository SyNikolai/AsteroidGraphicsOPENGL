/*------------------------------------------include necessary libraries--------------------------------------------*/
#include "graphics_functions.hpp"
/*---------------Main function:GLUT runs as a console application starting at main()-------------------------------*/
int main(int argc, char** argv) {
   create_data_arrays();
/*----------------------------------------------------------GRAPHICS-----------------------------------------------*/
   char title[] = "3D Graphical Simulation of Asteroid's Didymos Surface";
   glutInit(&argc, argv);                                   // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE);                        // Enable double buffered mode
   glutInitWindowSize(1280, 720);                           // Set the window's initial width & height
   glutInitWindowPosition(50, 50);                          // Position the window's initial top-left corner
   glutCreateWindow(title);                                 // title
   glutDisplayFunc(display);                                // window display
   glutReshapeFunc(reshape);                                // size of the window
   initGL();                                                // initialize the objects
   glutTimerFunc(0, timer, 0);                              // timer function
   glutSpecialFunc(processSpecialKeys);                     // move around the camera
   glutMainLoop();                                          // event loop
   return 0;
}




