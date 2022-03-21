#include <GL/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
 
 // schimbati dimensiunea si pozitionarea ferestrei
 // schimbati culorile
 // desenam punctele rotude - glEnable(GL_POINT_SMOOTH)
 // schimbati universul vizual
 // scrieti initialele din linii intr-o functie de desenare
void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
 
    glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (0.0, 800, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void deseneaza_RGB()
{
   	glLineWidth (2);
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
   	
	glBegin (GL_LINES);
		glColor3f (0, 0, 0);
		glVertex2i(300,100);
		glVertex2i(300,200);
		//glColor3f (1, 1, 0);		
		glVertex2i(300,200);
		glVertex2i(400,200);
		//glColor3f (1, 1, 1);
		glVertex2i(300,100);
		glVertex2i(400,100);
		//glColor3f(0,1,1);
		glVertex2i(400,100);
		glVertex2i(400,200);
	glEnd();
	glBegin (GL_LINES);
		glVertex2i(350,150);
		glVertex2i(350,250);
		glVertex2i(350,250);
		glVertex2i(450,250);
		glVertex2i(350,150);
		glVertex2i(450,150);
		glVertex2i(450,150);
		glVertex2i(450,250);
	glEnd();
	glBegin(GL_LINES);
		glVertex2i(300,100);
		glVertex2i(350,150);
		glVertex2i(300,200);
		glVertex2i(350,250);
		glVertex2i(450,150);
		glVertex2i(400,100);
		glVertex2i(450,250);
		glVertex2i(400,200);
	glEnd();
	glBegin (GL_POINTS);
		glColor3f (0, 1, 0); // green
		glVertex2i(300,100);
		//glVertex2i(300,200);
		glColor3f (1, 1, 0);// yellow	
		glVertex2i(300,200);
		//glVertex2i(400,200);
		glColor3f (1, 1, 1); // white
		//glVertex2i(300,100);
		glVertex2i(400,100);
		glColor3f(0,1,1);
		//glVertex2i(400,100);
		glVertex2i(400,200);
	glEnd();
	glBegin (GL_POINTS);
		glColor3f (0, 0, 0); // black
		glVertex2i(350,150);
		glColor3f (1, 0, 0); // red		
		glVertex2i(350,250);
		glColor3f (1, 0, 1);
		glVertex2i(450,150); // magenta
		glColor3f(0,0,1);
		glVertex2i(450,250);
	glEnd();
}

void desen (void) // procedura desenare  
{
 
   deseneaza_RGB();

   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}
void main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (200, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (800, 600); // dimensiunile ferestrei 
	glutCreateWindow ("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
 
	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}