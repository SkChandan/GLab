#include<GL/glut.h>
#include<stdio.h>

void displaySolid(void)
{
	GLfloat mat_ambient[]={0.7,0.7,0.7,1.0};
	GLfloat mat_diffuse[]={0.5,0.5,0.5,1.0};
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};
	GLfloat lightintensity[]={0.7,0.7,0.7,1.0};
	GLfloat lightposition[]={2.0,6.0,3.0,0.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightintensity);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-2.0,2.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	gluLookAt(2.0,1.0,2.0,0.0,0.2,0.2,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();// teapot
	  glTranslated(0.4,0.0,0.4);
	  glRotated(30,0,1,0);
	  glutSolidTeapot(0.2);
	glPopMatrix();

	glPushMatrix();// table top
	  glTranslated(0.0,-0.3,0.0);
	  glScaled(7.0,0.5,7.0);
	  glutSolidCube(0.2);
	glPopMatrix();

	glPushMatrix();// front leg
	  glTranslated(0.5,-0.7,0.5);
	  glScaled(0.5,7.0,0.5);
	  glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();// left leg
	  glTranslated(-0.5,-0.7,0.5);
	  glScaled(0.5,7.0,0.5);
	  glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();// right leg
	  glTranslated(0.5,-0.7,-0.5);
	  glScaled(0.5,7.0,0.5);
	  glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();// back leg
	  glTranslated(-0.5,-0.7,-0.5);
	  glScaled(0.5,7.0,0.5);
	  glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();// left wall
	   glTranslated(-1.0,0.0,0.0);
	   glScaled(0.1,10.0,10.0);
	   glutSolidCube(0.2);
	glPopMatrix();

	glPushMatrix();// Bottom floor
	   glTranslated(0.0,-1.0,0.0);
	   glScaled(10.0,0.1,10.0);
	   glutSolidCube(0.2);
	glPopMatrix();

	glPushMatrix();// Right Wall
	   glTranslated(0.0,0.0,-1.0);
	   glScaled(10.0,10.0,0.1);
	   glutSolidCube(0.2);
	glPopMatrix();

	glFlush();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(400,300);
	glutCreateWindow("Shaded Scene");
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.1,0.1,0.1,0.0);
	glViewport(0,0,640,480);
	glutMainLoop();
}
