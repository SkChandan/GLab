#include<Gl/glut.h>
#include<stdio.h>

/*void draw_pixel(GLint x,GLint y)
{
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	 glVertex2i(x,y);
	glEnd();
}*/

void plot_pixel(GLint h,GLint k,GLint x,GLint y)
{
	/*draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(-y+h,-x+k);*/

	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	 glVertex2i(x+h,y+k);
	 glVertex2i(-x+h,y+k);
	 glVertex2i(+x+h,-y+k);
	 glVertex2i(-x+h,-y+k);
	 glVertex2i(y+h,x+k);
	 glVertex2i(y+h,-x+k);
	 glVertex2i(-y+h,x+k);
	 glVertex2i(-y+h,-x+k);
	glEnd();
	 
	return;
}

void circle_draw(GLint h,GLint k,GLint r)
{
	GLint d=1-r,x=0,y=r;
	while(y>x)
	{
		plot_pixel(h,k,x,y);
		if(d<0) d+=2*x+3;
		else
		{
			--y;
			d+=2*(x-y)+5;
		}
		++x;
	}
	plot_pixel(h,k,x,y);
}

void cylinder_draw()
{
	GLint xc=100,yc=100,r=50;
	GLint i,n=40;
	for(i=0; i<n; i+=1)
		circle_draw(xc,yc+i,r);
}

void parallelpiped(GLint x1,GLint y1,GLint x2,GLint y2,GLint y3)
{
	glColor3f(1.0,0.75,0.0);
	glPointSize(1.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2i(x1,y1);
	 glVertex2i(x2,y2);
	 glVertex2i(x2,y3);
	 glVertex2i(x1,y3);
	glEnd();
	return;

}

void parallelpiped_draw()
{
	GLint x1=200,y1=100,x2=300,y2=100,y3=175;
	GLint i,n=50;
	for(i=0; i<n; i+=1)
		parallelpiped(x1+i,y1+i,x2+i,y2+i,y3+i);
}

void myinit()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,400.0,0.0,300.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	cylinder_draw();
	parallelpiped_draw();
	glFlush();
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cylinder_ParallelPiped");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}



