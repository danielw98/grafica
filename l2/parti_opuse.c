#include <GL/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)

#include<stdio.h>
int vx[50];
int vy[50];
int n;
int clicked = 0;
void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        if(clicked <= 1)
            clicked++;
		vx[n] = mx;
		vy[n] =600-my;//schimbam in functie de ecran
        n++;
		//printf("%d %d\n",x,y);
        glutPostRedisplay();
	}
	
}

void ecuatia_dreptei(int x1, int y1, int x2, int y2, int *a, int *b, int *c){
    int ma = y1-y2;
    int mb = x2-x1;
    int mc = (x1-x2)*y1 + x1*(y2-y1);

    //printf("Ecuatia: %dx+%dy+%d=0\n",ma,mb,mc);
    if(a != NULL) *a = ma;
    if(b != NULL) *b = mb;
    if(c != NULL) *c = mc;
}

void parti_opuse(int a, int b, int c, int x1, int y1, int x2, int y2)
{
	int val1 = a*x1 + b*y1 + c;
	int val2 = a*x2 + b*y2 + c;

	if(val1*val2 < 0)
		printf("Parti opuse\n");
	else
		printf("Aceeasi parte\n");
}
void desen(void)
{
    static int a, b, c;
    if(clicked <= 1)
        return;
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(10.0);
	glBegin(GL_LINES);
        for(int i = 0; i < 2; i++){

            glVertex2i(vx[i], vy[i]);
            if(i%2 == 1)
                ecuatia_dreptei(vx[i-1],vy[i-1],vx[i],vy[i],&a,&b,&c);
        }

	glEnd();
    glBegin(GL_POINTS);
        for(int i = 2; i < n; i++)
            glVertex2i(vx[i],vy[i]);
    glEnd();
	if(n>=4){
		parti_opuse(a,b,c,vx[2],vy[2],vx[3],vy[3]);
	}
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(800, 600); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutMouseFunc(mouse);
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}