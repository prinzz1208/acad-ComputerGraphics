#include <iostream>
#include <math.h>
#include <ctime>
#include <GL/glut.h>
using namespace std;
float theta=0;
float angle=45.0f;

struct poly{
	int x1,x2,x3,y1,y2,y3,incX,incY;
};
void DrawSemiCircle(int centerX,int centerY,int radius)   // the filled one
{

	float PI = 3.1415926f;
	float step=5.0;
	glBegin(GL_POLYGON);
	for(float angle=0.0f; angle<=180; angle+=step)
	 {
		float rad  = PI*angle/180;
		int x  = centerX+radius*cos(rad);
		int y  = centerY+radius*sin(rad);
		glVertex3f(x,y,0.0f);

	}
	glEnd();
}
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}



void windmill(){
	
	glTranslatef(400.0f,575.0f,0.0f);
	glRotatef(-angle,0.0f,0.0f,1.0f);
	glTranslatef(-400.0f,-575.0f,0.0f);
	
	glColor3f(1,1,1);

	int bladeWidth = 20;
	int bladeDist = 20;
	
	//BLADES
	glBegin(GL_TRIANGLES);
		glVertex2f(400,575);
		glVertex2f(550,375+bladeDist);
		glVertex2f(450-bladeWidth,475);	
	glEnd(); //vertices are specified and drawing of shapes can be done now

	glBegin(GL_TRIANGLES);
		glVertex2f(400,575);
		glVertex2f(250,375+bladeDist);
		glVertex2f(290-bladeWidth,475+bladeWidth);	
	glEnd(); //vertices are specified and drawing of shapes can be done now

	glBegin(GL_TRIANGLES);
		glVertex2f(400,575);
		glVertex2f(250,775-bladeDist);
		glVertex2f(340+bladeWidth,675+bladeWidth);	
	glEnd(); //vertices are specified and drawing of shapes can be done now
	
	
	glBegin(GL_TRIANGLES);
		glVertex2f(400,575);
		glVertex2f(550,775-bladeDist);
		glVertex2f(510+bladeWidth,675-bladeWidth);	
	glEnd(); //vertices are specified and drawing of shapes can be done now

	//BLADES
	glColor3f(0,0,0);
	DrawCircle(400,575,20,20);
    
	angle+=0.2f;
   
}

poly branch;

void tree(int incX,int incY)
{
	branch.incX = incX; branch.incY = incY;
	branch.x1 = 70 + branch.incX;
	branch.x2 = 110 + branch.incX;
	branch.y1 = 100 + branch.incY;
	branch.y2 = 190 + branch.incY;
	
	glBegin(GL_POLYGON);
       glColor3f(0.5,0.3,0.1);
        glVertex2i(branch.x1,branch.y1);
        glVertex2i(branch.x1,branch.y2);
        glVertex2i(branch.x2,branch.y2);
        glVertex2i(branch.x2,branch.y1);
    glEnd();
	
	glColor3f(0,0.6,0.3);		DrawCircle(90 + branch.incX,280 + branch.incY,60,20);
	glColor3f(0.0,0.6,0.3);		DrawCircle(60 + branch.incX,220 + branch.incY,60,20);
	glColor3f(0.0,0.6,0.3);		DrawCircle(120 + branch.incX,220 + branch.incY,60,20);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //flag for frame buffer
	glLoadIdentity(); //reset the matrix from previous frame
	
	//BUILDING
	glBegin(GL_POLYGON);
	  glColor3f(0.8,0.3,0.2);
		glVertex2i(300,200);
        glVertex2i(350,550);
        glVertex2i(450,550);
        glVertex2i(500,200);
    glEnd();
    
	glColor3f(0.3,0.4,0.4);	DrawSemiCircle(400,525,100);
	//BUILDING
	
	//GRASS
	glBegin(GL_POLYGON);
       glColor3f(0.4,1.0,0.1);
        glVertex2i(0,0);
        glVertex2i(0,200);
        glVertex2i(800,200);
        glVertex2i(800, 0);
    glEnd();
	//GRASS

	//TREES
	tree(0,0);

	tree(600,0);

	tree(400,-50);

	tree(200,-50);
	//TREES
	
	
	glPushMatrix();     
	windmill();
	glPopMatrix();
	glutSwapBuffers();
	
	glFlush();
	glutPostRedisplay();

}
void reshape(int width,int height) //arguments passed by API
{
	//viewport- the rectangular area in which we'll work
	glViewport(2,2,(GLsizei)width,(GLsizei)height);
	//we are currently in model view matrix GL_MODELVIEW
	glMatrixMode(GL_PROJECTION);
	//we can manipulate GL_PROJECTION matrix for projection 
	glLoadIdentity(); // resets the projection matrix
	gluOrtho2D(0,800,0,800);
	glMatrixMode(GL_MODELVIEW);
	
}
void init()
{	
	glClearColor(0.52,0.807,0.92,0.0);	//SKYBLUE BACKGROUND
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(60,timer,0);
}

int main(int argc,char** argv)
{
		
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Window 1");
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape); //called whenever window in reshaped
	glutTimerFunc(0,timer,0);
	init() ;//to fill the color in frame buffer

	glutMainLoop();
}

