#include<stdlib.h>
#include<GL/glut.h>
#define outcode int

const int TOP=8;
const int BOTTOM=4;
const int LEFT=1;
const int RIGHT=2;

double xmin=50,ymin=50,xmax=200,ymax=200;
double xvmin=250,yvmin=250,xvmax=450,yvmax=450;

outcode compute(double x,double y);

void csl(double x0,double y0,double x1,double y1)
{
	outcode outcode0,outcode1,outcodeout;
	bool accept=false,done=false;
	outcode0=compute(x0,y0);
	outcode1=compute(x1,y1);
	do
	{
		double x,y;
		if(!(outcode0 | outcode1))
		{
			accept=true;
			done=true;
		}
	/*	else if(outcode0 & outcode1)
			done=true;*/
		else
		{
			outcodeout=outcode0?outcode0:outcode1;
			float slop=(y1-y0)/(x1-x0);
			if(outcodeout & TOP)
			{
				x=x0+(1/slop)*(ymax-y0);
				y=ymax;
			}
			else if(outcodeout & BOTTOM)
			{
				x=x0+(1/slop)*(ymin-y0);
				y=ymin;
			}
			else if(outcodeout & LEFT)
			{
				y=y0+slop*(xmin-x0);
				x=xmin;
			}
			else
			{
				y=y0+slop*(xmax-x0);
				x=xmax;
			}
			if(outcodeout == outcode0)
			{
				x0=x;
				y0=y;
				outcode0=compute(x0,y0);
			}
			else
			{
				x1=x;
				y1=y;
				outcode1=compute(x1,y1);
			}

		}
	}while(!done);
	if(accept)
	{
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double sy=(yvmax-yvmin)/(ymax-ymin);
		double vx0=xvmin+(x0-xmin)*sx;
		double vy0=yvmin+(y0-ymin)*sy;
		double vx1=xvmin+(x1-xmin)*sx;
		double vy1=yvmin+(y1-ymin)*sy;
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(xvmin,yvmin);
		    glVertex2f(xvmin,yvmax);
			glVertex2f(xvmax,yvmax);
			glVertex2f(xvmax,yvmin);
			glEnd();
			glColor3f(0.0,0.0,1.0);
			glBegin(GL_LINES);
				glVertex2d(vx0,vy0);
			    glVertex2d(vx1,vy1);
			glEnd();
	}
}
outcode compute(double x,double y)
{
	outcode code=0;
	if(x>xmax)
		code |= RIGHT;
	if(x<xmin)
		code |= LEFT;
	if(y>ymax)
		code|= TOP;
	if(y<ymin)
		code |= BOTTOM;
	return code;
}
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}
void display(void)
{
	double x0=60,y0=20,x1=80,y1=220;
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmin,ymax);
	glVertex2f(xmax,ymax);
	glVertex2f(xmax,ymin);
	glEnd();
	glFlush();
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(x0,y0);
	glVertex2d(x1,y1);
	
	glVertex2d(50,50);
	glVertex2d(200,200);
	glVertex2d(25,50);
	glVertex2d(25,125);

	glEnd();
	glFlush();
	

    csl(x0,y0,x1,y1);
	glFlush();
	csl(50.0,50.0,200.0,200.0);
	glFlush();
	csl(25.0,50.0,25.0,125.0);
	glFlush();
}
 
void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1024,786);
	glutCreateWindow("2lab");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}



