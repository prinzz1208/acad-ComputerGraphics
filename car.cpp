#include <iostream>
#include <math.h>
#include <ctime>
#include <GL/glut.h>
using namespace std;

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

float starX[40],starY[40];

float roadX=-10.0;
			
float roadx=0,roady=0;
int plane=80;
int i=0,j=0;
float x=0.0,y=0.0;
void keyboard(int key,int ,int)
{
	float move=1;
	switch (key)
	{
		case GLUT_KEY_LEFT:
			x-=move;
			break;
		case GLUT_KEY_RIGHT:
			x+=move;
			break;
		
		case GLUT_KEY_UP:
			y+=move;
			break;
		
		case GLUT_KEY_DOWN:
			y-=move;
			break;
		
		default:{
			cout<<key;
		}
				
	}
	
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //flag for frame buffer
	glLoadIdentity(); //reset the matrix from previous frame
	
	glPointSize(1.0);

	//----STARS----
	for (int i = 0; i < 40; i++)
	{
		glBegin(GL_POINTS);
			glVertex2f(starX[i],starY[i]);
		glEnd();
	}
	
	//----STARS----
	
	//----MOON----
	glColor3f(1.0,1.0,1.0);		DrawCircle(50,50,10,20);
	//----MOON----
	
	glPointSize(10.0);
	
	//glBegin(GL_POLYGONS) should always be given coordinates in anticlockwise order to get the front size
	
	//----ROAD----
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-plane-10,-16);
		glVertex2f(-plane-10,-plane);
		glVertex2f(plane,-plane);
		glVertex2f(plane,-16);
	glEnd(); 
	//----ROAD----

	//----road MARK----
	glColor3f(1.0,1.0,1.0);
	//float roadMarkX4=60;
	//float roadMarkX2=80;
	int gap=10,width=20;
	//roady-=50;
	for (i = 0; i < 5; i++)
	{		
		glBegin(GL_POLYGON);
			glVertex2f(roadx-plane+i*gap+i*width,roady-40);
			glVertex2f(roadx-plane+i*gap+i*width,roady-50);
			glVertex2f(roadx-plane+20+i*gap+i*width,roady-50);
			glVertex2f(roadx-plane+20+i*gap+i*width,roady-40);
		glEnd(); 
		
		glBegin(GL_POLYGON);
			glVertex2f(-80+(roadX-plane+i*gap+i*width),roady-40);
			glVertex2f(-80+(roadX-plane+i*gap+i*width),roady-50);
			glVertex2f(-80+(roadX-plane+20+i*gap+i*width),roady-50);
			glVertex2f(-80+(roadX-plane+20+i*gap+i*width),roady-40);
		glEnd(); 
	
	}

	//----road MARK----

	//----CAR HEAD----
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(x-15,y+22);
		glVertex2f(x-25,y+10);
		glVertex2f(x+20,y+10);
		glVertex2f(x+15,y+22);
	glEnd(); 
	//----CAR WINDOW----
	glColor3f(0.52,0.80,0.92);
	glBegin(GL_POLYGON);
		glVertex2f(x-13,y+19);
		glVertex2f(x-19,y+12);
		glVertex2f(x-2,y+12);
		glVertex2f(x-2,y+19);
	glEnd(); 
	glBegin(GL_POLYGON);
		glVertex2f(x+12,y+19);
		glVertex2f(x+15,y+12);
		glVertex2f(x+2,y+12);
		glVertex2f(x+2,y+19);
	glEnd(); 
	
	////----CAR WINDOW----
	
	//----CAR HEAD----
	
	//----CAR BOTTOM----
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
		glVertex2f(x-45,y+10);
		glVertex2f(x-48,y-10);
		glVertex2f(x+35,y-10);
		glVertex2f(x+30,y+10);
	glEnd(); 
	//----CAR BOTTOM----
	
	//----CAR RADIATOR----
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.0,0.0);
		glVertex2f(x-39,y+13);
		glVertex2f(x-39,y+11);
		glVertex2f(x-31,y+11);
		glVertex2f(x-31,y+13);
	glEnd(); 	
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.0,0.0);
		glVertex2f(x-36,y+13);
		glVertex2f(x-36,y+10);
		glVertex2f(x-34,y+10);
		glVertex2f(x-34,y+13);
	glEnd(); 	
	//----CAR RADIATOR----
	
	
	//----CAR TIRES----
	
	glColor3f(0.0,0.0,0.0);		DrawCircle(x+17,y-10,10,20);
	glColor3f(1.0,1.0,1.0);		DrawCircle(x+17,y-10,6,20);
	
	glColor3f(0.0,0.0,0.0);		DrawCircle(x-17,y-10,10,20);
	glColor3f(1.0,1.0,1.0);		DrawCircle(x-17,y-10,6,20);
	//----CAR TIRES----
	
	//----CAR HEADLIGHTS----
	//glColor3f(1.0,0.0,0.0);
	//DrawCircle(-49-10,10,5,8);
	//DrawCircle(-49-10,3,5,8);

	//----CAR HEADLIGHTS----
	//glFlush(); //displays the buffer on the screen
		//glutKeyboardFunc(keyboard);

	glutSwapBuffers();
}
void reshape(int width,int height) //arguments passed by API
{
	//viewport- the rectangular area in which we'll work
	glViewport(1,1,(GLsizei)width,(GLsizei)height);
	//we are currently in model view matrix GL_MODELVIEW
	glMatrixMode(GL_PROJECTION);
	//we can manipulate GL_PROJECTION matrix for projection 
	glLoadIdentity(); // resets the projection matrix

	gluOrtho2D(-plane,plane,-plane,plane);
	glMatrixMode(GL_MODELVIEW);
	
}
void init()
{	
	glClearColor(0.0,0.078,0.15,0.0);
}
void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/30,timer,0);
	roadx+=0.4;
	roadX+=0.4;
	if((roadx-plane+20)>plane){
		roadx=-80+(roadX-plane+20)-plane-10;
		i=0;
	}
	if(-80+(roadX-plane+20)>plane){
		roadX=-80.0;
		i=0;
	}

}

int main(int argc,char** argv)
{
	//srand(time(0));
	for (int i = 0; i < 40; i++)
	{
		starX[i]=rand()%(plane-(-plane)+1)+(-plane);
		starY[i]=rand()%(plane-(-plane)+1)+(-plane);
	}
		
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Window 1");
	
	glutReshapeFunc(reshape); //called whenever window in reshaped
	glutTimerFunc(1000,timer,0);
	glutSpecialFunc(keyboard);
	init() ;//to fill the color in frame buffer
	glutDisplayFunc(display);

	glutMainLoop();
}

