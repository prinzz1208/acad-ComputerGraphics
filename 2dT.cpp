#include <iostream>
#include <math.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#define M 20
#define N 20
using namespace std;
float xPos=-5;

int inputM[M][N];
int outputM[M][N];
int n = 0;
void show(int n)
{
	cout<<endl;
	int x = 0,y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
			switch (j)
			{
				case 0:
					x = inputM[j][i];
					break;
				case 1:
					y = inputM[j][i];
					break;

				case 2:
					break;
			}		
		glVertex2i(x,y);
	}
}
void show2(int n)
{
	cout<<endl;
	int x = 0,y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
			switch (j)
			{
				case 0:
					x = outputM[j][i];
					break;
				case 1:
					y = outputM[j][i];
					break;

				case 2:
					break;
			}		
		glVertex2i(x,y);
	}
}
void matrixMul(int T[][N],int n1,int m1,int n,int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m ; k++)
		{
			int sum = 0;
			for (int j = 0; j < m ; j++)
			{
				//cout<<"\ninputM[j][k]:"<<inputM[j][k];
				//cout<<"\nT[i][j]:"<<T[i][j];
				sum += inputM[j][k] * T[i][j];
			}
			outputM[i][k] = sum;
		}
	}
}
void scaling(int n,int m,int dx,int dy)
{
	int S[M][N] = { {dx,0,0},
					{0,dy,0},
					{0,0,1}};
	
	matrixMul(S,3,3,n,m);
	show2(m);
}
void rotation(int n,int m,int theta)
{
	int R[M][N] = { {(int)cos(theta),(int)(-sin(theta)),0},
					{(int)sin(theta),(int)cos(theta),0},
					{0,0,1}};
	
	matrixMul(R,3,3,n,m);
	show2(m);

}
void translate(int n,int m,int dx,int dy)
{
	int T[M][N] = { {1,0,dx},
					{0,1,dy},
					{0,0,1}};
	
	matrixMul(T,3,3,n,m);
	show2(m);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //flag for frame buffer
	glLoadIdentity(); //reset the matrix from previous frame

	glPointSize(10.0);
	//draw stuff
	//glBegin(GL_POLYGONS) should always be given coordinates in anticlockwise order to get the front size
	glBegin(GL_LINE_LOOP);
		show(n);
		//glVertex2f(xPos,1);
		//glVertex2f(xPos+2,0);
		//glVertex2f(xPos,0);	
	glEnd(); //vertices are specified and drawing of shapes can be done now
	glColor3i(0,0,0);
	glBegin(GL_LINE_LOOP);
		translate(3,n,2,2);
		//glVertex2f(xPos,1);
		//glVertex2f(xPos+2,0);
		//glVertex2f(xPos,0);	
	glEnd(); //vertices are specified and drawing of shapes can be done now
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
	gluOrtho2D(-10,10,-10,10);
	glMatrixMode(GL_MODELVIEW);
	
}

void init()
{
	glClearColor(1.0,0.0,0,1.0);
}
int main(int argc,char** argv)
{
	cout<<"Enter number of vertices:";
	cin>>n;
	cout<<"\nEnter vertices:\n"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (j)
			{
				case 0:
					cout<<"\tx:";
					cin>>inputM[j][i];
					break;
				case 1:
					cout<<"\ty:";
					cin>>inputM[j][i];
					break;

				case 2:
					inputM[j][i] = 1;
					break;
			}	
		}	
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Window 1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape); //called whenever window in reshaped
	//glutTimerFunc(1000,timer,0);
	init() ;//to fill the color in frame buffer
	glutMainLoop();
}
