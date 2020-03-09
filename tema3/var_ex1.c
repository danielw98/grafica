/*
 *  As a first example of using OpenGL in C, this program draws the
 *  classic red/green/blue triangle.  It uses the default OpenGL
 *  coordinate system, in which x, y, and z are limited to the range
 *  -1 to 1, and the positive z-axis points into the screen.  Note
 *  that this coordinate system is hardly ever used in practice.
 *
 *  When compiling this program, you must link it to the OpenGL library
 *  and to the glut library. For example, in Linux using the gcc compiler, 
 *  it can be compiled with the command:
 *
 *          gcc -o first-triangle first-triangle.c -lGL -lglut
 */
 
#include <GL/gl.h>
#include <GL/glut.h>   // freeglut.h might be a better alternative, if available.
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define N_MAX 100
#define N_SIDES 128
#define PI 3.1415


float X[N_MAX];
float Y[N_MAX];
float R[N_MAX/2];

GLuint idx;
int nr_puncte;

float tf(int k){
    float f = k - 250;
    return f/250;
}

static void init(){
    idx = glGenLists(1);
}

void display() {  // Display function will draw the image.
 
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    float theta;
    float x_coord, y_coord;
    
    glCallList(idx);
    glFlush();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
 
}

void functie_mouse(int button, int state, int x, int y){
    if(!(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)) return;

    X[nr_puncte] = tf(x); Y[nr_puncte] = tf(y);
    nr_puncte++;
    printf("Am adaugat %d %d -> %d\n",x,y,nr_puncte);
    
    if(nr_puncte % 2 == 0){
      float theta;
      float x_coord, y_coord;
      glNewList(idx,GL_COMPILE);
          glBegin(GL_LINE_STRIP);
             glColor3f(1,0,0);
             for(int i = 0; i < N_SIDES; i++){
                  theta = i * (2*PI/N_SIDES);
                  x_coord = 0 + 0.5*cos(theta);
                  y_coord = 0 + 0.5*sin(theta);
                  glVertex2f(x_coord,y_coord);
             }     
          glEnd();
      glEndList();
    }
    glutPostRedisplay();   
}


int main( int argc, char** argv ) {  // Initialize GLUT and 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    srand(time(NULL));
    init();
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;

}

