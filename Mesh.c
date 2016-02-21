#include<GL/glut.h>
#include<stdio.h>

#define maxx 30
#define maxy 25
#define dx 15
#define dy 10

GLfloat x[maxx]={0.0},y[maxy]={0.0};
GLint x0,y0;
int i,j;

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,450.0+2*x0,0.0,250.0+2*y0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);

	for(i=0; i<maxx; i++)
		x[i]=x0+i*dx;
	
	for(j=0; j<maxy; j++)
		y[j]=y0+j*dy;

	for(i=0; i<maxx-1; i++)
		for(j=0; j<maxy-1; j++)
		{
			glBegin(GL_LINE_LOOP);
			 glVertex2f(x[i],y[j]);
			 glVertex2f(x[i+1],y[j]);
			 glVertex2f(x[i+1],y[j+1]);
			 glVertex2f(x[i],y[j+1]);
			glEnd();
			glFlush();
		}
}

int main(int argc,char **argv)
{
	printf("Enter the value of x0 and y0:\n");
	printf("x0=");
	scanf("%d",&x0);
	printf("y0=");
	scanf("%d",&y0);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Mesh_Window");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();

	return 0;
}


