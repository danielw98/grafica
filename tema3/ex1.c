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
GLubyte lists[N_MAX/2];
int curr_size;
int nr_puncte;

void init(){
    idx = glGenLists(N_MAX/2);
}

float tf(int k){
    float f = k - 250;
    return f/250;
}

float r2(){
    return rand()/RAND_MAX;
}

void display() {  // Display function will draw the image.
 
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    glListBase(idx);
    for(int i = 0; i < curr_size; i++)
        lists[i] = i;
 
    glCallLists(curr_size,GL_UNSIGNED_BYTE,lists);
    
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
 
}

float raza(){
    int n = nr_puncte;
    float x = X[n-2]-X[n-1];
    float y = Y[n-2]-Y[n-1];
    return sqrt(x*x+y*y);
}

void gestioneaza_liste(){
    float R = r2();
    float G = r2();
    float B = r2();
    
    float x = X[nr_puncte-2];
    float y = Y[nr_puncte-2];
    float r = raza();
    
    float theta;
    float x_coord, y_coord;
    
    printf("Cerc cu centrul (%.3f,%.3f) si raza %.3f\n",x,y,r);   
    glNewList(idx+curr_size,GL_COMPILE);
        glBegin(GL_LINES);
            glColor3f(1-R,1-G,B);
            glVertex2f(X[nr_puncte-2],Y[nr_puncte-2]);
            glVertex2f(X[nr_puncte-1],Y[nr_puncte-1]);
        glEnd();
        
        glBegin(GL_POINTS);
             glColor3f(R,1-G,1-B);
             glVertex2f(X[nr_puncte-2],Y[nr_puncte-2]);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
           glColor3f(R,G,B);
           for(int i = 0; i < N_SIDES; i++)
           {
                theta = i * (2*PI/N_SIDES);
                x_coord = x + r*cos(theta);
                y_coord = y + r*sin(theta);
                glVertex2f(x_coord,y_coord);
           }     
        glEnd();
    glEndList();
    printf("Am initializat lista %d\n", idx+curr_size);
    curr_size++;
}
void functie_mouse(int button, int state, int x, int y){
    if(!(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)) return;

    X[nr_puncte] = tf(x); Y[nr_puncte] = tf(y);
    nr_puncte++;
    printf("Am adaugat %d %d -> %d\n",x,y,nr_puncte);
    
    if(nr_puncte % 2 == 0){
        gestioneaza_liste();
        glutPostRedisplay(); 
    }    
}


int main( int argc, char** argv ) {  // Initialize GLUT and 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    glutMouseFunc(functie_mouse);
    srand(time(NULL));
    init();
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;

}

