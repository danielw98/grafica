/*
 *          gcc -o first-triangle first-triangle.c -lGL -lglut
 */
 
 
 // calcul produs vectorial
 // varfuri convexe-concave
#include <GL/gl.h>
#include <GL/glut.h>   // freeglut.h might be a better alternative, if available.
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    float x;
    float y;
    float z;
}Point3;

typedef struct {
    float x;
    float y;
}Point2;

typedef struct{
    float x;
    float y;
    float z;
}Vector3;

typedef struct{
    Point2 p[100];
    int dim;
}Poligon2;


void display() {  // Display function will draw the image.
 
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    glBegin(GL_TRIANGLES);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0, 0.9 );
    glEnd(); 
    
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
 
}

/*
    | i   k  j |
    | a0 a1 a2 |
    | b0 b1 b2 |
*/

Vector3 calcul_produs_vectorial(Vector3 a, Vector3 b){
   Vector3 V;
   V.x = a[1]*b[2] - a[2]*b[1];
   V.y = a[2]*b[0] - a[0]*b[2];
   V.z = a[0]*b[1] - a[1]*b[0];
   return V;
}


Vector3 line2_to_vector3(Point2 p1, Point2 p2)
{
    Vector3 V;
    V.x = p2.x - p1.x;
    V.y = p2.y - p1.y;
    V.z = 0;
    return V;
}

void varfuri_convexe_concave(Poligon2* p){
    int i;
    Vector3 a;
    Vector3 b;
    Vector3 rez;
    
    int semn = 0;
    for(i = 3; i<p->dim; i++)
    {
        a = line2_to_vector3(p->p[i-3],p->p[i-2]);
        b = line2_to_vector3(p->p[i-1],p->p[i]);
        rez = calcul_produs_vectorial(a,b);
        
        if(semn==0) semn = (rez.z>0)?1:-1;
        else{
            if(rez.z * semn > 0) printf("Convex\n");
            else                 printf("Concav\n");
        }
    }
}

void exercitiu()
{
    srand(time(NULL));
    Point3 A = {1,2,3};
    Point3 B = {1,1,0};
    Point3 C = {1,0,1};

    P
}
int main( int argc, char** argv ) {  // Initialize GLUT and 

    exercitiu();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;

}

