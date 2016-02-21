#include<stdio.h>
#include<GL/glut.h>
GLfloat x1,x2,x3,x4,y1,y2,y3,y4;

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLint *le,GLint *re)
{
	GLfloat mx,x,temp;
	GLint i;
	if((y2-y1)<0)
	{
		temp=y2; y2=y1; y1=temp;
		temp=x2; x2=x1; x1=temp;
	}
	
	if((y2-y1)!=0)
		mx=(x2-x1)/(y2-y1);
	else
		mx=(x2-x1);

	x=x1;
	for(i=y1; i<=y2; i++)
	{
		if(x<(GLfloat)le[i])
			le[i]=(GLint)x;
		if(x>(GLfloat)re[i])
			re[i]=(GLint)x;
		x=x+mx;
	}
}

void draw_pixel(GLint x,GLint y)
{
	glColor3f(0.25,0.75,0.25);
	glBegin(GL_POINTS);
	 glVertex2i(x,y);
	glEnd();
}

void scanfill(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat x3,GLfloat y3,GLfloat x4,GLfloat y4)
{
	GLint le[500],re[500];
	GLint i,y;
	for(i=0; i<500; i++)
	{
		le[i]=500;
		re[i]=0;
	}
	
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x4,y4,le,re);
	edgedetect(x4,y4,x1,y1,le,re);

	for(y=0; y<500; y++)
	{
		if(le[y]<=re[y])
			for(i=(GLint)le[y]; i<(GLint)re[y]; i++)
				draw_pixel(i,y);
	}
}

void display(void)
{
	x1=200.0;y1=200.0;x2=100.0;y2=300.0;x3=200.0;y3=400.0;x4=300.0;y4=300.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(x1,y1);
	 glVertex2f(x2,y2);
	 glVertex2f(x3,y3);
	 glVertex2f(x4,y4);
	glEnd();
	scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Scan_Line Filling");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();

	return 0;
}