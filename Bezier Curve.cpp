#include <iostream>
#include <math.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
using namespace std;
struct point{
	double x;
	double y;
	point( double x, double y ) {
		this->x = x;
		this->y = y;
	}
};

point P[4] = {point(2,1),point(3,2),point(5,0),point(6,2) };
point P2[4] = {point(6,2),point(8,6),point(8,0),point(11,1) };
	
void BezierCurve(point P[4])
{	
		double x = 0.0,y = 0.0;
		for (double t = 0.0; t <=1.0; t += 0.005 )
		{
			x = P[0].x * pow((1 - t),3) + P[1].x * ((3 * t)*(pow((1 - t),2)))
				+ P[2].x * ((3 * pow(t,2))*(1 - t)) + P[3].x * (pow(t,3));
			y = P[0].y * pow((1 - t),3) + P[1].y * ((3 * t)*(pow((1 - t),2)))
				+ P[2].y * ((3 * pow(t,2))*(1 - t)) + P[3].y * (pow(t,3));

			glVertex2d(x,y);
			cout<<"\tx:"<<x<<"\ty:"<<y;
			cout<<endl;
		}
		
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //flag for frame buffer
	glLoadIdentity(); //reset the matrix from previous frame

	glPointSize(1.0);
	//draw stuff
	//glBegin(GL_POLYGONS) should always be given coordinates in anticlockwise order to get the front size
	glBegin(GL_POINTS);
		BezierCurve(P);
	glEnd(); 
	
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
		BezierCurve(P2);
	glEnd(); 
	
	//glFlush(); //displays the buffer on the screen
	glutSwapBuffers(); //to swap buffer
}
void reshape(int width,int height) //arguments passed by API
{
	//viewport- the rectangular area in which we'll work
	glViewport(2,2,(GLsizei)width,(GLsizei)height);
	//we are currently in model view matrix GL_MODELVIEW
	glMatrixMode(GL_PROJECTION);
	//we can manipulate GL_PROJECTION matrix for projection 
	glLoadIdentity(); // resets the projection matrix
	gluOrtho2D(-5,15,-5,15);
	glMatrixMode(GL_MODELVIEW);
	
}

void init()
{
	glClearColor(0.0,0.0,0,0.0);
}

int main(int argc,char** argv)
{
	cout<<"Enter Vertices:\n";
	
	//for (int i = 0; i <4 ; i++)
	//{
		//cout<<endl;
		//cout<<"\tx:";	cin>>P[i].x;
		//cout<<"\ty:";	cin>>P[i].y;
	//}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(500,100);
	glutInitWindowSize(1000,1000);
	
	glutCreateWindow("Window 1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape); //called whenever window in reshaped
	//glutTimerFunc(1000,timer,0);
	init() ;//to fill the color in frame buffer
	glutMainLoop();
}



