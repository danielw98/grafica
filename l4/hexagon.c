#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500;
GLuint regHex1;
GLuint regHex2;
GLuint regHex3;
GLuint regHex4;
GLuint regHex5;
static GLfloat rotTheta = 0.0;
int center1 = 150;
int rho1 = 10;
int center2 = 200;
int rho2 = 20;
int center3 = 250;
int rho3 = 15;
int center4 = -200;
int rho4 = 30;
int center5 = 0;
int rho5 = 50;
	
typedef struct scrPt 
{
	GLint x, y;
}scrPt;

static void init (void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;
    glClearColor (1.0,1.0, 1.0, 1.0);
	regHex1 = glGenLists (1);
	glNewList (regHex1, GL_COMPILE);
		glColor3f (1.0, 0.0, 0.0);
		glBegin (GL_POLYGON);
		for (k=0; k < 100; k++)
		{
			hexTheta = TWO_PI * k / 100;
			hexVertex.x = center1 + rho1 * cos (hexTheta);
			hexVertex.y = center1 + rho1 * sin (hexTheta);
			glVertex2i (hexVertex.x, hexVertex.y);
		}
		glEnd ( );
	glEndList ( );
    regHex2 = glGenLists (1);
	glNewList (regHex2, GL_COMPILE);
		glColor3f (1.0, 1.0, 0.0);
		glBegin (GL_POLYGON);
		for (k=0; k < 100; k++)
		{
			hexTheta = TWO_PI * k / 100;
			hexVertex.x = center2 + rho2 * cos (hexTheta);
			hexVertex.y = center2 + rho2 * sin (hexTheta);
			glVertex2i (hexVertex.x, hexVertex.y);
		}
		glEnd ( );
	glEndList ( );

    regHex3 = glGenLists (1);
	glNewList (regHex3, GL_COMPILE);
		glColor3f (1.0, 0.5, 0.7);
		glBegin (GL_POLYGON);
		for (k=0; k < 100; k++)
		{
			hexTheta = TWO_PI * k / 100;
			hexVertex.x = center3 + rho3 * cos (hexTheta);
			hexVertex.y = center3 + rho3 * sin (hexTheta);
			glVertex2i (hexVertex.x, hexVertex.y);
		}
		glEnd ( );
	glEndList ( );

    regHex4 = glGenLists (1);
	glNewList (regHex4, GL_COMPILE);
		glColor3f (0, 0.5, 0.7);
		glBegin (GL_POLYGON);
		for (k=0; k < 100; k++)
		{
			hexTheta = TWO_PI * k / 100;
			hexVertex.x = center4 + rho4 * cos (hexTheta);
			hexVertex.y = center4 + rho4 * sin (hexTheta);
			glVertex2i (hexVertex.x, hexVertex.y);
		}
		glEnd ( );
	glEndList ( );

    regHex5 = glGenLists (1);
	glNewList (regHex5, GL_COMPILE);
		glColor3f (0.0, 0.7, 0.9);
		glBegin (GL_POLYGON);
		for (k=0; k < 100; k++)
		{
			hexTheta = TWO_PI * k / 100;
			hexVertex.x = center5 + rho5 * cos (hexTheta);
			hexVertex.y = center5 + rho5 * sin (hexTheta);
			glVertex2i (hexVertex.x, hexVertex.y);
		}

		glEnd ( );
        
	glEndList ( );
}
void displayHex (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

 
	glCallList (regHex1);
    glColor3f(0.0,0.0,0.0);
    glRasterPos2i(center1, center1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
    glPopMatrix ( );
    glCallList(regHex2);
    glColor3f(0.0,0.0,0.0);
    glRasterPos2i(center2, center2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
    glPopMatrix ( );
    glCallList(regHex3);
    glColor3f(0.0,0.0,0.0);
    glRasterPos2i(center3, center3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
    glPopMatrix ( );
    glCallList(regHex4);
    glColor3f(0.0,0.0,0.0);
    glRasterPos2i(center4, center4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
    glPopMatrix ( );
    glCallList(regHex5);
    glColor3f(0.0,0.0,0.0);
    glRasterPos2i(center5, center5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c');
    glPopMatrix ( );

	

 
	glFlush ( );
}

 

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	gluOrtho2D (-320.0, 320.0, -320.0, 320.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ( );

	glClear (GL_COLOR_BUFFER_BIT);
}

 
void main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (150, 150);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Hexagon - utilizarea listelor de display");

	init ( );
	glutDisplayFunc (displayHex);
	glutReshapeFunc (winReshapeFcn);

	glutMainLoop ( );

}


