#include <windows.h>  				// for MS Windows
#include "graphics_functions.hpp"
#include <math.h>
char title[] = "3D Graphical Simulation of Asteroid's Didymos Surface";
GLfloat spin = 0.0f;  												// Rotational angle for the object
int refreshMills = 15;        											// refresh interval in milliseconds
#define FACES 2292.0f
#define POINTS  10000
/*----------------------------------------------final object arrays--------------------------------------*/
GLfloat fixed_varray[1148][3];											// fixed_varray
GLuint 	fixed_indarray[2292][3];										// define fixed_indarray
GLfloat fixed_trajectory_array[POINTS][3];									// define fixed_trajectory_array
/*-------------------------------------------------------------------------------------------------------*/
void create_data_arrays(){
    int number_of_vertices;
    int number_of_indices;
    int nm;
    vector< vector <float> > vertices;
    data(vertices, &number_of_vertices,3,1);								        // read vertices coordinates
	for (int row = 0; row < number_of_vertices; row++){							//(x,y,z) -> (z,x,y) -> (y,z,x)
		fixed_varray[row][0]=vertices[row][1];
		fixed_varray[row][1]=vertices[row][2];
		fixed_varray[row][2]=vertices[row][0];
	}
    vector< vector <int> > indices;
    data(indices, &number_of_indices,3,2);									// read indices
        for (int row = 0; row < number_of_indices; row++){
        	for (int col =0; col < 3; col++){
        		fixed_indarray[row][col]= indices[row][col] - 1;					//change values from (from 1 to 1148) to (from 0 to 1147)
        }
    }
    vector< vector <float> > points;
    data(points, &nm,7, 3);											// read trajectory points' coordinates
    for (int row = 0; row < nm; row++){
    	fixed_trajectory_array[row][0]=points[row][1];
        fixed_trajectory_array[row][1]=points[row][2];
        fixed_trajectory_array[row][2]=points[row][3];
    }

}
/*-------------------------------------------lists for ready to render objects---------------------------*/
static GLuint axes_list;
static GLuint faces_list;
static GLuint ind_list;
static GLuint graph_list;
/*--------------------------------------camera position variables-----------------------------------------*/
float cam_angle=0.0;												// angle of rotation for the camera direction
float lx=0.0f,lz=-1.0f;												// vector pointing to the camera's direction
float x=0.0f,z=1.0f;												// XZ position of the camera
/*------------------------------------------- Initialize OpenGL Graphics----------------------------------*/
void initGL() {
   glClearColor(0.0f, 0.0f, 0.3f, 0.0f);									// Set background color
   glClearDepth(10.0f);												// Set background depth to farthest
   glEnable(GL_DEPTH_TEST);											// Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);											// Set the type of depth-test
   glShadeModel(GL_SMOOTH);											// Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   							// Nice perspective corrections
/*--------------------------------------------create the 3D axes list--------------------------------------*/
   axes_list = glGenLists(1);
       glNewList(axes_list, GL_COMPILE);

       glColor4ub(255, 0, 0, 255);

       glBegin(GL_LINE_STRIP);
       glVertex3f(0.0f, 0.0f, 0.0f);
       glVertex3f(1.0f, 0.0f, 0.0f);
       glEnd();

       glBegin(GL_LINE_STRIP);
       glVertex3f(0.0f, 0.0f, 0.0f);
       glVertex3f(0.0f, 1.0f, 0.0f);
       glEnd();

       glBegin(GL_LINE_STRIP);
       glVertex3f(0.0f, 0.0f, 0.0f);
       glVertex3f(0.0f, 0.0f, 1.0f);
       glEnd();

       glColor4ub(255, 255, 0, 255);
       glRasterPos3f(0.9f, 0.0f, 0.0f);
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
       glRasterPos3f(0.0f, 0.9f, 0.0f);
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
       glRasterPos3f(0.0f, 0.0f, 0.9f);
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');

       glEndList();
/*--------------------------------------------create the faces list------------------------------------------*/
   faces_list = glGenLists(1);
       glNewList(faces_list, GL_COMPILE);
       int i;
       glBegin(GL_TRIANGLES);
       for (i = 0; i < FACES ; i++){
          glColor3f((FACES-i)/FACES, (FACES-i)/FACES, (FACES-i)/FACES);	// from dark to bright
            glVertex3fv(&fixed_varray[fixed_indarray[i][0]][0]);
            glVertex3fv(&fixed_varray[fixed_indarray[i][1]][0]);
            glVertex3fv(&fixed_varray[fixed_indarray[i][2]][0]);
       }
       glEnd();
       glEndList();
/*-------------------------------------------create the lines list--------------------------------------------*/
   ind_list = glGenLists(1);
       glNewList(ind_list, GL_COMPILE);
       glColor3f(0.0f, 0.0f, 0.0f);
       glBegin(GL_LINES);
       for (i = 0; i < FACES; i++){
         glVertex3fv(&fixed_varray[fixed_indarray[i][0]][0]);	// connect vert[i][0] to vert[i][1]
         glVertex3fv(&fixed_varray[fixed_indarray[i][1]][0]);
       }

       for (i=0; i < FACES; i++){
       	 glVertex3fv(&fixed_varray[fixed_indarray[i][0]][0]);	// connect vert[i][0] to vert[i][2]
       	 glVertex3fv(&fixed_varray[fixed_indarray[i][2]][0]);
       }

       for (i=0; i < FACES; i++){
         glVertex3fv(&fixed_varray[fixed_indarray[i][1]][0]);	// connect vert[i][1] to vert[i][2]
         glVertex3fv(&fixed_varray[fixed_indarray[i][2]][0]);
       }
       glEnd();
       glEndList();
/*-------------------------------------------create the trajectory line----------------------------------------*/
   graph_list =  glGenLists(1);
       glNewList(graph_list, GL_COMPILE);
       glColor3f(1.0f, 1.0f, 0.0f);
       glBegin(GL_POINTS);
       for(int i = 0; i < POINTS; i++){		//change according to the number of trajectory points in file3
    	   glVertex3f(fixed_trajectory_array[i][1],fixed_trajectory_array[i][2],fixed_trajectory_array[i][3]);
       }
       glEnd();
       glEndList();
}

/*-----window-repaint:Called when the window first appears and  whenever the window needs to be re-painted-----*/
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   			 // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);							 // To operate on model-view matrix

// Render object
/*---------------------basic opengl functions for object position , and any movement or rotation---------------*/
   glLoadIdentity();					// Reset the model-view matrix
   gluLookAt(	x, 0.15f, z,				// Set the camera
   			x+lx, 0.15f,  z+lz,
   			0.0f, 0.15f,  0.0f);
   glTranslatef(0.0f, 0.0f, -2.5f);			// Move  into the screen more than max distance  (zoom out)

/*-----------------------------------------------render the trajectory-----------------------------------------*/
   glPushMatrix();
   glCallList(graph_list);
   glPopMatrix();
   glRotatef(spin, 0.0f, 1.0f, 0.0f);  			// Enable to Rotate about the y-axis in computational space , (z axis)

/*-------------------------------------------render primitives: lines-------------------------------------------*/
   glPushMatrix();
   glCallList(ind_list);
   glPopMatrix();

/*-------------------------------------------render primitives: triangles---------------------------------------*/
   glPushMatrix();
   glCallList(faces_list);
   glPopMatrix();

/*-----------------------------------------------render the xyz axes---------------------------------------------*/
   glPushMatrix();					// put them before glRotate for  no rotation
   glCallList(axes_list);
   glPopMatrix();

   glutSwapBuffers();  					// Swap the front and back frame buffers (double buffering)
   spin += 0.5f;					// rotational angle after each refresh
}
/*-------------------------------------------keys input for camera------------------------------------------------*/
void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.2f;
	switch (key) {
		case GLUT_KEY_LEFT :
			cam_angle -= 0.01f;
			lx = sin(cam_angle);
			lz = -cos(cam_angle);
			break;
		case GLUT_KEY_RIGHT :
			cam_angle += 0.01f;
			lx = sin(cam_angle);
			lz = -cos(cam_angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}

/*-----------------------------------Timer function, it is called back when it expires----------------------------*/
void timer(int value) {
   glutPostRedisplay();     			 	// Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0);
}

/*--------Window re-size event. Called back when the window first appears and whenever the window is re-sized-----*/
void reshape(GLsizei width, GLsizei height)	{	// GLsizei for non-negative integer
   if (height == 0) height = 1;                		// aspect ratio of new window , error: divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  			// To operate on the Projection matrix
   glLoadIdentity();             			// Reset
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
