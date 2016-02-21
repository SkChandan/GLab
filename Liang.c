#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

int n;
double x[100],y[100];
double xmin=50,ymin=50,xmax=250,ymax=250;
double xvmin=275,yvmin=275,xvmax=500,yvmax=500;

int cliptest(double p,double q,double *t1,double *t2)
{
	double t=q/p;
	if(p<0.0)
	{
		if(t>*t1) *t1=t;
		if(t>*t2) return 0;
	}
	
	else if(p>0.0)
	{
		if(t<*t2) *t2=t; 
		if(t<*t1) return 0;
	}

    else if(p==0.0)
		if(q<0.0) return 0;
	return 1;	
}

void liang_barsky(double x0,double y0,double x1,double y1)
{
	double dx=x1-x0,dy=y1-y0,tl=0.0,tu=1.0;
	double vx0,vy0,vx1,vy1,sx,sy;
	if(cliptest(-dx,x0-xmin,&tl,&tu))
		if(cliptest(dx,xmax-x0,&tl,&tu))
			if(cliptest(-dy,y0-ymin,&tl,&tu))
				if(cliptest(dy,ymax-y0,&tl,&tu))
				{
					if(tu<1.0)
					{
						x1=x0+tu*dx;
						y1=y0+tu*dy;
					}
					if(tl>0.0)
					{
						x0=x0+tl*dx;
						y0=y0+tl*dy;
					}
					
					sx=(xvmax-xvmin)/(xmax-xmin);
					sy=(yvmax-yvmin)/(ymax-ymin);
					
					vx0=xvmin+(x0-xmin)*sx;
					vy0=yvmin+(y0-ymin)*sy;
					vx1=xvmin+(x1-xmin)*sx;
					vy1=yvmin+(y1-ymin)*sy;

					glColor3f(1.0,0.0,0.0);
                 	glBegin(GL_LINE_LOOP);
					  glVertex2f(xvmin,yvmin);
					  glVertex2f(xvmax,yvmin);
					  glVertex2f(xvmax,yvmax);
					  glVertex2f(xvmin,yvmax);
					glEnd();

					glColor3f(0.0,0.0,1.0);
					glBegin(GL_LINES);
					 glVertex2d(vx0,vy0);
					 glVertex2d(vx1,vy1);
					glEnd();
					
				}
	return;
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,600.0,0.0,600.0);
	//glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Plot the lines in the Window 
	glColor3f(1.0,0.0,0.0);
	for(i=0; i<(n*2); i=i+2)
	{
		glBegin(GL_LINES);
		 glVertex2d(x[i],y[i]);
		 glVertex2d(x[i+1],y[i+1]);
		glEnd();
	}
	
    //Draw the window
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(xmin,ymin);
	 glVertex2f(xmax,ymin);
	 glVertex2f(xmax,ymax);
	 glVertex2f(xmin,ymax);
	glEnd();

 
	//Draw the Viewport
    

	for(i=0; i<(n*2); i=i+2)
	{
		liang_barsky(x[i],y[i],x[i+1],y[i+1]);
		glFlush();
	}
	
}

int main(int argc,char **argv)
{
	int cnt=1,i;
	printf("Enter the number of lines n= ");
	scanf("%d",&n);
    printf("\nEnter the Co-Ordinates of the Lines:\n");
	for(i=0; i<(n*2); i+=2)
	{
		printf("\n--Line %d Co-Ordinates--\n",(cnt++));
		printf("x0=");
		scanf("%lf",&x[i]);
		printf("y0=");
		scanf("%lf",&y[i]);
		printf("\nx1=");
		scanf("%lf",&x[i+1]);
		printf("y1=");
		scanf("%lf",&y[i+1]);
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1024,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Liang_barsky_Clipping");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();

	return 0;
}







