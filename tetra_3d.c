#include<GL/glut.h>
#include<stdio.h>

typedef float point[3];
point v[]={{-1.0,-0.5,0.0},{1.0,-0.5,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};

GLfloat color[4][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0}};
int n;

void triangle(point va,point vb,point vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}

void tetra(point a,point b,point c,point d)
{
	glColor3fv(color[0]);
	triangle(a,b,c);
	glColor3fv(color[1]);
	triangle(a,c,d);
	glColor3fv(color[2]);
	triangle(a,d,b);
	glColor3fv(color[3]);
	triangle(b,d,c);
}

void divide_tetra(point a,point b,point c,point d,int m)
{
	point mid[6];
    int j;

	if(m>0)
	{
		/*for(j=0; j<3; j++) mid[0][j]=(a[j]+c[j])/2.0;
		for(j=0; j<3; j++) mid[1][j]=(a[j]+d[j])/2.0;
		for(j=0; j<3; j++) mid[2][j]=(a[j]+b[j])/2.0;
		for(j=0; j<3; j++) mid[3][j]=(b[j]+d[j])/2.0;
		for(j=0; j<3; j++) mid[4][j]=(b[j]+c[j])/2.0;
		for(j=0; j<3; j++) mid[5][j]=(c[j]+d[j])/2.0;

		divide_tetra(a,mid[0],mid[1],mid[2],m-1);
		divide_tetra(b,mid[2],mid[3],mid[4],m-1);
		divide_tetra(c,mid[4],mid[5],mid[0],m-1);
		divide_tetra(d,mid[1],mid[3],mid[5],m-1);*/

		for(j=0; j<3; j++)
		{
		   mid[0][j]=(a[j]+c[j])/2.0;
		   mid[1][j]=(a[j]+d[j])/2.0;
		   mid[2][j]=(a[j]+b[j])/2.0;
		   mid[3][j]=(b[j]+d[j])/2.0;
		   mid[4][j]=(b[j]+c[j])/2.0;
		   mid[5][j]=(c[j]+d[j])/2.0;
		}

		divide_tetra(a,mid[2],mid[0],mid[1],m-1);
		divide_tetra(mid[2],b,mid[4],mid[3],m-1);
		divide_tetra(mid[0],mid[4],c,mid[5],m-1);
		divide_tetra(mid[1],mid[3],mid[5],d,m-1);
	}

	else
		tetra(a,b,c,d);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0],v[1],v[2],v[3],n);
	glEnd();
	glFlush();
}

void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-1.0,1.0,-1.0*(GLfloat) h/(GLfloat) w,1.0*(GLfloat) h/(GLfloat) w,-1.0,1.0);
	else
		glOrtho(-1.0*(GLfloat) w/(GLfloat) h,1.0*(GLfloat) w/(GLfloat) h,-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc,char **argv)
{

	printf("Enter no of divisions: ");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
    glutCreateWindow("Sierpenski_Recurssion");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}

