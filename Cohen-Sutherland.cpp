#include <iostream>
using namespace std;

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
void CSLC(double x0,double y0,double x1,double y1,double xmin,double xmax,double ymin,double ymax,int val)
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
		MidpointLineReal(x0,y0,x1,y1,value);
	
}
int main()
{
	cout<<0x4;
}
