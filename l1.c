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
	gluOrtho2D (0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void desen (void) // procedura desenare  
{
 
  // segmentele
   glLineWidth (2.0);
   glBegin (GL_LINES); 
	   glColor3f (1.0, 0.0, 0.5);  // culoarea primului segment: rosu
       glVertex2i (370,30);
	   glVertex2i (20, 380);
	   glColor3f (0.3, 1.0, 0.0);  // culoarea celui de-al doilea segment: verde
	   glVertex2i (10, 10);
	   glVertex2i (500, 500);
   glEnd ( );
 
   // punctul de intersectie
    
   glPointSize(10.0);
   glEnable(GL_POINT_SMOOTH);
   glBegin (GL_POINTS);
		glColor3f (0.0, 0.0, 1.0); // culoarea punctului de intersectie: albastru
	    glVertex2i (200, 200);
   glEnd ( );
 
   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}
void main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (200, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (400, 300); // dimensiunile ferestrei 
	glutCreateWindow ("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
 
	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}