#include <iostream>
#include <vector>
using namespace std;

const string boundType[4] = {"LEFT","RIGHT","TOP","BOTTOM"};

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
point boundary[4];

bool dup(point x)
{
	for(point t : p)
		if(t.x == x.x && t.y == x.y)
			return true;
	
	return false;
}
void update()
{
	cout<<"\nIn update \n";

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
		cout<<"\n\t x:"<<t.x<<"\ty:"<<t.y;
	}
}
	

bool inside(point p,int xmin,int ymin,int xmax,int ymax,string edge)
{
	//cout<<"\n----INSIDE----\n";
	//cout<<"edge:"<<edge<<endl;
	//cout<<" x:"<<point.first<<" y:"<<point.second<<endl;
	//cout<<" bx:"<<bound1.first<<" by:"<<bound1.second<<endl;
	//cout<<" b2x:"<<bound2.first<<" b2y:"<<bound2.second<<endl;
	//cout<<"\n----INSIDE----\n";

	if(edge == "LEFT"){
		//if(p.x < xmin && p.y <= ymax && p.y >= ymin)
		if(p.x < xmin)
			return false;
	}
	else if (edge == "RIGHT"){
		//if(p.x > xmax && p.y <= ymax && p.y >= ymin)
		if(p.x > xmax )
			return false;
	}
	else if (edge == "TOP"){
		//if(p.x <= xmax && p.x >=xmin && p.y > ymax)
		if(p.y > ymax)
			return false;

	}
	else if (edge == "BOTTOM"){
		//if(p.x < xmax && p.x > xmin && p.y < ymin)
		if(p.y < ymin)
			return false;
	}
	

	return true;
	
}
point intercept(int xmin,int ymin,int xmax,int ymax,point p1,point p2,string edge)
{
	cout<<"\nIn Intercept \n";
	int x0 = p1.x,
		y0 = p1.y,
		x1 = p2.x,
		y1 = p2.y;
	int x = 0,y = 0;
	if(edge == "LEFT")
	{
		x = xmin;
		y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y;
		return point(x,y);
	}
	else if(edge == "RIGHT")
	{
		y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
		x = xmax;		
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y;
		return point(x,y);	
	}
	else if(edge == "TOP")
	{
		x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
		y = ymax;
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y;
		return point(x,y);

	}
	else
	{
		x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
		y = ymin;
		//cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y<<" pointName: "<<temp->pointName;
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
						ins.push_back(upoint(i,intercept(xmin,ymin,xmax,ymax,p[i],p[j],edge)));
						rm.push_back(i);
					}	
			}
			if(edge == "RIGHT"){
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
			if(edge == "TOP"){
				cout<<"\nTOP\n";
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

	//for( auto s:boundType)
		//SH(xmin,ymin,xmax,ymax,s);
	SH(xmin,ymin,xmax,ymax,boundType[0]);
	SH(xmin,ymin,xmax,ymax,boundType[1]);
	SH(xmin,ymin,xmax,ymax,boundType[2]);
	SH(xmin,ymin,xmax,ymax,boundType[3]);
}

int main()
{
	//int n = 0, x = 0,y = 0;
	//cout<<"Enter no. of vertices:";
	//cin>>n;
	//char alpha = 'A';
	//for (int i = 0; i < n; i++)
	//{
		//cout<<alpha<<"\tx:";
		//cin>>x;
		//cout<<"\ty:";
		//cin>>y;
		
		//p.push_back(point(x,y));
	//}
	//cout<<"Enter no. of vertices for boundary:";
	
	//alpha = 'P';
	
	p.push_back(point(100,150));
	p.push_back(point(200,250));
	p.push_back(point(300,200));
	//for (int i = 0; i < 4; i++)
	//{
		//cout<<alpha<<"\tx:";
		//cin>>x;
		//cout<<"\ty:";
		//cin>>y;
		
		//boundary[i] = point(x,y);
	//}
	boundary[0] = point(150,150);
	boundary[1] = point(150,200);
	boundary[2] = point(200,200);
	boundary[3] = point(200,150);
	SHCheck();
	show();
}
