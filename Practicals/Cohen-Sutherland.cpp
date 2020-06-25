//TEST CASE:
//Enter no. of lines:3

//Line 1
	//x0:5
	//y0:5
	//x1:7
	//y1:7

//Line 2
	//x0:7 
	//y0:9
	//x1:11
	//y1:4

//Line 3
	//x0:1
	//y0:5
	//x1:1
	//y1:4


#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
using namespace std;

struct point{
	double x;
	double y;
	point()
	{
		x = 0;
		y = 0;
	}
	point(double x1,double y1)
	{
		x = x1;	
		y = y1;
	}
};
vector<pair<point,point>> p;
vector<pair<point,point>> outPoints;
point boundary[4];

void showBound(double shiftx,double shifty)
{
	for (int i = 0; i <=4; i++)
	{
		if(i == 4)
			glVertex2d(boundary[0].x + shiftx,boundary[0].y + shifty);
		else
			glVertex2d(boundary[i].x + shiftx,boundary[i].y + shifty);
	}
	
}
void show(double shiftx,double shifty)
{
	for(pair<point,point> t : outPoints)
	{
		glBegin(GL_LINES);
			glVertex2d(t.first.x + shiftx,t.first.y + shifty);
			glVertex2d(t.second.x + shiftx,t.second.y  + shifty);
		glEnd();
	}
	
}

void showInit()
{
	for(pair<point,point> t : p)
	{
		glBegin(GL_LINES);
			glVertex2d(t.first.x,t.first.y);
			glVertex2d(t.second.x,t.second.y);
		glEnd();
	}

}
typedef unsigned int outcode;
enum{TOP = 0x1,BOTTOM = 0x2,RIGHT = 0x4,LEFT = 0x8};

outcode CompOutCode(double x,double y,double xmin,double xmax,double ymin,double ymax)
{
	outcode code = 0;
	if(y > ymax)
		code |= TOP;
	else if(y < ymin)
		code |= BOTTOM;
	if(x > xmax)
		code |= RIGHT;
	else if(x < xmin)
		code |= LEFT;
	return code;
}
void CSLC(double x0,double y0,double x1,double y1,double xmin,double xmax,double ymin,double ymax)
{
	outcode outcode0,outcode1,outcodeOut;
	bool accept = false, done = false;
	outcode0 = CompOutCode(x0,y0,xmin,xmax,ymin,ymax);
	outcode1 = CompOutCode(x1,y1,xmin,xmax,ymin,ymax);
	
	do
	{
		if(!(outcode0 | outcode1)){
			accept = true; done = true;
		}else if (outcode0 & outcode1)
			done = true;
		else{
			double x,y;
			outcodeOut = outcode0 ? outcode0 : outcode1;
			if (outcodeOut & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			}else if (outcodeOut & BOTTOM)
			{
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			}else if (outcodeOut & RIGHT)
			{
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}else{
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}
			if (outcodeOut == outcode0){
				x0 = x; y0 = y; outcode0 = CompOutCode(x0,y0,xmin,xmax,ymin,ymax);
			}else{
				x1 = x; y1 = y; outcode1 = CompOutCode(x0,y0,xmin,xmax,ymin,ymax);

			}
		}
	} while (done == false);
	if (accept)
	{
		//cout<<"\n\tx0:"<<x0<<"\ty0:"<<y0;
		//cout<<"\n\tx1:"<<x1<<"\ty1:"<<y1;
		outPoints.push_back(make_pair(point(x0,y0),point(x1,y1)));
	}else
		cout<<"\nRejected: x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1;
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //flag for frame buffer
	glLoadIdentity(); //reset the matrix from previous frame

	glPointSize(10.0);
	//draw stuff
	//glBegin(GL_POLYGON) should always be given coordinates in anticlockwise order to get the front size

	showInit();
	show(0,-10);
	glBegin(GL_LINE_STRIP);
		glColor3i(0,0,0);
		showBound(0,-10);
	glEnd(); //vertices are specified and drawing of shapes can be done now

	glBegin(GL_LINE_STRIP);
		glColor3i(0,0,0);
		showBound(0,0);
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
	gluOrtho2D(-10,20,-10,20);
	glMatrixMode(GL_MODELVIEW);
	
}


void init()
{
	glClearColor(1.0,0.0,0,1.0);
}
int main(int argc,char** argv)
{
	boundary[0] = point(4,4);
	boundary[1] = point(4,8);
	boundary[2] = point(10,8);
	boundary[3] = point(10,4);

	//USER INPUT
	cout<<"Enter no. of lines:";
	int n; cin>>n;
	double x0 = 0,y0 = 0,x1 = 0,y1 = 0;
	for (int i = 0; i < n ; i++)
	{
		cout<<"\nLine "<<i+1<<endl;
		cout<<"\tx0:";		cin>>x0;
		cout<<"\ty0:";		cin>>y0;

		cout<<"\tx1:";		cin>>x1;
		cout<<"\ty1:";		cin>>y1;
				
		p.push_back(make_pair(point(x0,y0),point(x1,y1)));
	}
	
	//cout<<"\nEnter boundary vertices:";	
	//for (int i = 0; i < 4; i++)
	//{
		//cout<<"\n\tx:";		cin>>x;
		//cout<<"\ty:";		cin>>y;
		//boundary[i] = point(x,y);
	//}
	
	//USER INPUT


	int xmin = boundary[0].x,
		ymin = boundary[0].y,
		xmax = boundary[2].x,
		ymax = boundary[1].y;
	
	for( pair<point,point> t : p)
		CSLC(t.first.x,t.first.y,t.second.x,t.second.y,xmin,xmax,ymin,ymax);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Window 1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape); //called whenever window in reshaped
	init() ;//to fill the color in frame buffer
	glutMainLoop();
}
