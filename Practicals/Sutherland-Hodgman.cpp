#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
using namespace std;
float xPos=-10;

struct point {
	int x;
	int y;
	point(){
		x = 1;
		y = 1;
	}
	point(int x1,int y1){
		x = x1;	
		y = y1;
	}
};

struct upoint{
	int i;
	point x;
	upoint(int index,point x1){
		i = index;
		x = x1;
	}
};

vector<int> rm;
vector<upoint> ins;
vector<point> p;
vector<point> initP;

point boundary[4];

const string boundType[4] = {"LEFT","RIGHT","TOP","BOTTOM"};


bool dup(point x)		//to check for duplicate
{
	for(point t : p)
		if(t.x == x.x && t.y == x.y)
			return true;
	
	return false;
}
void update()			//to update clipping
{
	for(int t : rm){
		p.erase(p.begin() + t);
	}	
	for(upoint t : ins){
		if(!dup(t.x)) 
			p.insert(p.begin() + t.i,t.x);
	}
	ins.clear();
	rm.clear();
}
void show()
{
	
	for(point t : p){
		glVertex2i(t.x+200,t.y);
	}
	glVertex2i(p[0].x+200,p[0].y);	
}
void showInit()
{
	for(point t : initP){
		glVertex2i(t.x,t.y);
	}
	glVertex2i(initP[0].x,initP[0].y);

}
void showBound(int shift)
{
	for (int i = 0; i <4; i++)
		glVertex2i(boundary[i].x + shift,boundary[i].y);
}
bool inside(point p,int xmin,int ymin,int xmax,int ymax,string edge)
{
	if(edge == "LEFT"){
		if(p.x < xmin)
			return false;
	}
	else if (edge == "RIGHT"){
		if(p.x > xmax )
			return false;
	}
	else if (edge == "TOP"){
		if(p.y > ymax)
			return false;

	}
	else if (edge == "BOTTOM"){
		if(p.y < ymin)
			return false;
	}
	return true;
	
}
point intercept(int xmin,int ymin,int xmax,int ymax,point p1,point p2,string edge)
{
	int x0 = p1.x,
		y0 = p1.y,
		x1 = p2.x,
		y1 = p2.y;
	int x = 0,y = 0;
	if(edge == "LEFT")
	{
		x = xmin;
		y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
		return point(x,y);
	}
	else if(edge == "RIGHT")
	{
		y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
		x = xmax;		
		return point(x,y);	
	}
	else if(edge == "TOP")
	{
		x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
		y = ymax;
		return point(x,y);
	}
	else
	{
		x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
		y = ymin;
		return point(x,y);
	}
}
void SH(int xmin,int ymin,int xmax,int ymax,string edge)
{		
		int n = p.size();
		for (int i = 0,j = 1; i < n; i++,j++)
		{
			if(j == n)
				j = 0;
				
			if(edge == "LEFT"){
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						//cout<<"\nelse1\n";
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						//cout<<"\nelse if1\n";
						ins.push_back(upoint(i,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "RIGHT"){
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						//cout<<"\nelse1\n";
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						//cout<<"\nelse if1\n";
						ins.push_back(upoint(i	,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "TOP"){
				//cout<<"\nTOP\n";
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						//cout<<"\nelse1\n";
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						//cout<<"\nelse if1\n";
						ins.push_back(upoint(i	,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "BOTTOM"){
				if(inside(p[i],xmin,ymin,xmax,ymax,edge)){
					if(( inside(p[j],xmin,ymin,xmax,ymax,edge)));
					else
					{
						cout<<"\nelse1\n";
						if(j<i)
							p.push_back(intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge));
						else
							ins.push_back(upoint(j,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						
					}
				}else
					if(inside(p[j],xmin,ymin,xmax,ymax,edge))
					{	
						
						cout<<"\nelse if1\n";
						ins.push_back(upoint(i	,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			
		}
		update();
		
	

}
void SHCheck()
{
	
	int xmin = boundary[0].x,
		ymin = boundary[0].y,
		xmax = boundary[2].x,
		ymax = boundary[1].y;

	for( auto s:boundType)
		SH(xmin,ymin,xmax,ymax,s);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //flag for frame buffer
	glLoadIdentity(); //reset the matrix from previous frame

	glPointSize(10.0);
	//draw stuff
	//glBegin(GL_POLYGON) should always be given coordinates in anticlockwise order to get the front size
	glBegin(GL_POLYGON);
		showInit();
	glEnd(); //vertices are specified and drawing of shapes can be done now

	glBegin(GL_POLYGON);
		show();
	glEnd(); //vertices are specified and drawing of shapes can be done now

	glBegin(GL_LINE_LOOP);
		glColor3i(0,0,0);
		showBound(0);
	glEnd(); //vertices are specified and drawing of shapes can be done now

	glBegin(GL_LINE_LOOP);
		glColor3i(0,0,0);
		showBound(200);
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
	int plane = 500;
	gluOrtho2D(0,plane,0,plane);
	glMatrixMode(GL_MODELVIEW);
	
}
void init()
{
	glClearColor(1.0,0.0,0,1.0);
}
int main(int argc,char** argv)
{
	p.push_back(point(100,150));
	p.push_back(point(200,250));
	p.push_back(point(300,200));
	
	boundary[0] = point(150,150);
	boundary[1] = point(150,200);
	boundary[2] = point(200,200);
	boundary[3] = point(200,150);
	
	//USER INPUT

	//int n = 0, x = 0,y = 0;
	//cout<<"Enter no. of vertices:";
	//cin>>n;
	//for (int i = 0; i < n; i++)
	//{
		//cout<<"\n\tx:";
		//cin>>x;
		//cout<<"\ty:";
		//cin>>y;
		
		//p.push_back(point(x,y));
	//}	
	
	
	//for (int i = 0; i < 4; i++)
	//{
		//cout<<alpha<<"\n\tx:";
		//cin>>x;
		//cout<<"\ty:";
		//cin>>y;
		
		//boundary[i] = point(x,y);
	//}
	
	//USER INPUT

	
	initP = p;
	SHCheck();
	
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


