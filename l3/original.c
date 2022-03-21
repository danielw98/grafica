#include <GL/gl.h>
#include <GL/glut.h>   // freeglut.h might be a better alternative, if available.
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

typedef struct
{
    float x;
    float y;
}Point;

int X[NMAX];
int Y[NMAX];
int nr_puncte;
 
int flag;
int nr_intersectii;
float iX[NMAX];
float iY[NMAX];

float XF[NMAX];
float YF[NMAX];

int culoare_segment[NMAX-1];
 
/* A * x = b; x = A^(-1) * b;
 
  / xc-xd xb-xa \ * /s0\ = /xc-xa\
  \ yc-yd yb-ya /   \t0/   \yc-ya/
 
*/
 void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-1, 1, -1, 1); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
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
           " %.1fs0 + %.1ft0 = %.1f\n"
           " %.1fs0 + %.1ft0 = %.1f\n\n",
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
  
  if(B.x == C.x && B.y == C.y)
  {
    printf("Cazul liniei poligonale.\n");
    return -1;
  }
    
    rezolva(x,M_inversa,b);
   
  printf("Solutiile sunt: <s0,t0> = <%.1f/%.1f, %.1f/%.1f>\n",  x[0],det,x[1],det);
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
    int point = 'A';

    glBegin(GL_POINTS);
      glVertex2i(250,250);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
        glColor3f(0,1,0);
        for(int i = 1; i < nr_puncte; i++){
            
            
            if(culoare_segment[i-1])
                glColor3f(1,0,0);
            else
                glColor3f(0,1,0);
            printf("coords : %f %f\n", XF[i-1], -YF[i-1]);
            glVertex2f(XF[i-1],-YF[i-1]);
            glVertex2f(XF[i],-YF[i]);
        }
    glEnd();
    for(int i = 1; i < nr_puncte; i++){
      glColor3f(1,1,1);
      glRasterPos2f(XF[i-1], -YF[i-1]);            
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'A'+i-1);
    }
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


void initializ(Point *A, Point *B, Point *C, Point *D, int i)
{
    A->x = XF[i-2]; A->y = YF[i-2];
    B->x = XF[i-1]; B->y = YF[i-1];
    C->x = XF[nr_puncte-2]; C->y = YF[nr_puncte-2];
    D->x = XF[nr_puncte-1]; D->y = YF[nr_puncte-1];
}

void verifica_autointersectii()
{
    Point A, B, C, D;
    
    int autointersectie = 0;
    int i;
    for(i = 2; i < nr_puncte; i++){
        initializ(&A,&B,&C,&D, i);
        if(se_intersecteaza(A,B,C,D) != -1){
            printf("Intersectie datorata punctului P%d(%.3f,%.3f)\n",i,D.x,D.y);
            printf("Desenez diferit segmentul (%.2f,%.2f) -> (%.2f,%.2f)\n",C.x,C.y,D.x,D.y);
            autointersectie = 1;
            break;
        }
    }
    if(autointersectie == 1)
        culoare_segment[nr_puncte-2] = 1;
}


void functie_mouse(int button, int state, int x, int y){
    if(!(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)) return;
    if(nr_puncte == NMAX){ printf("Maximul atins!\n"); exit(0);}
    X[nr_puncte] = x; Y[nr_puncte] = y;
    XF[nr_puncte] = tf(x); YF[nr_puncte] = tf(y);
    nr_puncte++;
    printf("Am adaugat %d %d -> %d\n",x,y,nr_puncte);
      
    if(nr_puncte >= 3)
    {
        verifica_autointersectii();
        
    }    
    glutPostRedisplay();
}


int main( int argc, char** argv ) {  // Initialize GLUT and 
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    init();
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    glutMouseFunc(functie_mouse);
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;
}