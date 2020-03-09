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
#include <stdio.h>


typedef struct
{
    float x;
    float y;
}Point;

int X[100];
int Y[100];
int nr_puncte;
 
int flag;
int nr_intersectii;
float iX[100];
float iY[100];

float XF[100];
float YF[100];

 
/* A * x = b; x = A^(-1) * b;
 
  / xc-xd xb-xa \ * /s0\ = /xc-xa\
  \ yc-yd yb-ya /   \t0/   \yc-ya/
 
*/
 
void rezolva(float x[], float M_inversa[], float *b)
{
    x[0] = M_inversa[0] * b[0] + M_inversa[1] * b[1];
    x[1] = M_inversa[2] * b[0] + M_inversa[3] * b[1];
}
 
float inversa(float *M, float *M_inversa)
{
    float det = M[0]*M[3] - M[1]*M[2];
    M_inversa[0] =  M[3];
    M_inversa[1] = -M[1];
    M_inversa[2] = -M[2];
    M_inversa[3] =  M[0];
    return det;
}
 
void print_puncte(Point *A, Point *B, Point *C, Point *D)
{
  printf("Punctele:\n"
         "A = <%.3f, %.3f>\n"
         "B = <%.3f, %.3f>\n"
         "C = <%.3f, %.3f>\n"
         "D = <%.3f, %.3f>\n\n",
         A->x,A->y,B->x,B->y,C->x,C->y,D->x,D->y);
 
}

int se_intersecteaza(Point A, Point B, Point C, Point D)
{
  printf("\n**************************************************\n");
  print_puncte(&A,&B,&C,&D);
    float M[4] ={C.x - D.x, B.x - A.x, C.y - D.y, B.y - A.y};
    float x[2];
    float b[2] = {C.x - A.x, C.y - A.y};
 
    printf("Sistemul:\n"
           " %.3fs0 + %.3ft0 = %.3f\n"
           " %.3fs0 + %.3ft0 = %.3f\n\n",
        M[0],M[1],b[0],M[2],M[3],b[1]);
   
    float M_inversa[4];
   
    float det = inversa(M,M_inversa);
 
  if(det == 0){
      if(b[0] == b[1])
        printf("Punctele sunt coliniare!!!\n");
      else
        printf("Dreptele sunt paralele!!!\n");
      return -1;
  }
    rezolva(x,M_inversa,b);
   
  printf("Solutiile sunt: <s0,t0> = <%.3f/%.3f, %.3f/%.3f>\n",  x[0],det,x[1],det);
  printf("                <s0,t0> = <%.3f, %.3f>\n\n",x[0]/det,x[1]/det);
  float s0 = x[0]/det, t0 = x[1]/det;
  if(s0 <= 1 && s0 >= 0 && t0 <= 1 && t0 >= 0){
    printf("Dreptele se intersectaza!\n");
    Point P;
    P.x = (1-t0) * A.x + t0 * B.x;
    P.y = (1-t0) * A.y + t0 * B.y;
    printf("Punctul de intersectie: <%.3f,%.3f>\n\n", P.x,P.y);
    iX[nr_intersectii] = P.x;
    iY[nr_intersectii] = P.y;
    nr_intersectii++;
    return 0;
  }
  else {
    printf("Nu se intersectaza segmentele, insa se intersectaza dreptele!\n");
    return -1;
  }
}
 
 
void linie_poligonala(Point *p, int nr){
  // deseneaza p[0]p[1]
  int autointersectie;
  for(int i = 2; i < nr; i++){
      autointersectie = 0;
      for(int j = 2; j< i; j++)
        if(se_intersecteaza(p[j-2],p[j-1],p[i-1],p[i]) != -1){
              printf("Intersectie datorata punctului P%d(%.3f,%.3f)\n",i,p[i].x,p[i].y);
              printf("Desenez diferit segmentul (%.3f,%.3f) -> (%.3f,%.3f)\n",p[i-1].x,p[i-1].y,p[i].x,p[i].y);
              autointersectie = 1;
              break;
        }
  }
}
 
 
void initializeaza(Point *p){
  p[0].x = 0; p[0].y = 0;
  p[1].x = 0; p[1].y = 1;
  p[2].x = 0; p[2].y = 2;
  p[3].x = 2; p[3].y = 2;
  p[4].x = 2; p[4].y = 1;
  p[5].x = -1;p[5].y = 1.5;
  p[6].x = -1;p[6].y = 0.5;
  p[7].x = 2 ;p[7].y = 0.5;
}




float tf(int k){
    float f;
    f = k - 250;
    f /= 250;
    printf("%f\n",f);
    return f;
}


void display() {  // Display function will draw the image.
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    glLineWidth(5);
    glPointSize(5);
    glBegin(GL_LINES);
        glColor3f(0,1,0);
        for(int i = 0; i < nr_puncte; i++) 
            glVertex2f(XF[i],-YF[i]);
    glEnd();
    
    glBegin(GL_POINTS);
        glColor3f(1,0,0);
        for(int i = 0; i < nr_intersectii; i++)
            glVertex2f(iX[i],-iY[i]);
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


void initializ(Point *A, Point *B, Point *C, Point *D)
{
    A->x = XF[nr_puncte-4]; A->y = YF[nr_puncte-4];
    B->x = XF[nr_puncte-3]; B->y = YF[nr_puncte-3];
    C->x = XF[nr_puncte-2]; C->y = YF[nr_puncte-2];
    D->x = XF[nr_puncte-1]; D->y = YF[nr_puncte-1];
}

void functie_mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        X[nr_puncte] = x; Y[nr_puncte] = y;
        XF[nr_puncte] = tf(x); YF[nr_puncte] = tf(y);
        nr_puncte++;
        printf("Am adaugat %d %d -> %d\n",x,y,nr_puncte);
        
        if(nr_puncte % 4 == 0)
        {
            Point A, B, C, D;
            initializ(&A,&B,&C,&D);
            se_intersecteaza(A,B,C,D);
        }    
        glutPostRedisplay();
    }
}


/*
int main(){
    //Point p[4];
    //citeste_mouse(p,4);
    Point A = {0,4}, B = {4,0}, C = {-1,-1}, D = {3,7};
    //int k1 = se_intersecteaza(A,B,C,D);
 
  Point X = {0,0}, Y = {1,1}, Z = {2,2}, T = {3,3};
  //int k2 = se_intersecteaza(X,Y,Z,T);
 
  Point Q = {0,0}, W = {1,1}, E = {1,0}, R = {2,1};
  //int k3 = se_intersecteaza(Q,W,E,R);
 
  Point M = {0,0}, N = {1,1}, O = {0,2}, P = {1,2};
  //int k4 = se_intersecteaza(M,N,O,P);
 
  Point pts[100];
  initializeaza(pts);
  linie_poligonala(pts,8);
    return 0;
}*/

int main( int argc, char** argv ) {  // Initialize GLUT and 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    glutMouseFunc(functie_mouse);
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;

}

