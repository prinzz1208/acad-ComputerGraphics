#include <iostream>
using namespace std;
struct node{
	pair<int,int> point;
	string pointName;
	node* next;
	bool out;
};

const string boundary[4] = {"LEFT","TOP","RIGHT","BOTTOM"};
node *head,*head2;

node *temp,*temp2;

void out(node* root)
{
	temp = root;
	cout<<endl;
	//cout<<temp->pointName;
	//cout<<temp->next->pointName;
	do
	{		
		cout<<temp->pointName<<" "<<"("<<temp->point.first<<","<<temp->point.second<<") -> ";
		temp = temp->next;
	} while (temp != root);
	
	cout<<endl;
}
node* newNode(pair<int,int> val,string pointName)
{
	node* p = new node();
	p->point = val;
	p->pointName = pointName;
	p->next = NULL;
	p->out = false;
	return p;
}
bool inside(pair<int,int> point,int xmin,int ymin,int xmax,int ymax,string edge)
{
	//cout<<"\n----INSIDE----\n";
	//cout<<"edge:"<<edge<<endl;
	//cout<<" x:"<<point.first<<" y:"<<point.second<<endl;
	//cout<<" bx:"<<bound1.first<<" by:"<<bound1.second<<endl;
	//cout<<" b2x:"<<bound2.first<<" b2y:"<<bound2.second<<endl;
	//cout<<"\n----INSIDE----\n";

	if(edge == "LEFT"){
		if(point.first < xmin && point.second <= ymax && point.second >= ymin)
			return false;
	}
	else if (edge == "RIGHT"){
		if(point.first > xmax && point.second <= ymax && point.second >= ymin)
			return false;
	}
	else if (edge == "TOP"){
		if(point.first <= xmax && point.first >=xmin && point.second > ymax)
			return false;

	}
	else if (edge == "BOTTOM"){
		if(point.first < xmax && point.first > xmin && point.second < ymin)
			return false;
	}
	

	return true;
	
}
void intercept(int xmin,int ymin,int xmax,int ymax,int x0,int y0,int x1,int y1,string edge)
{
	int x = 0,y = 0;
	if(edge == "LEFT")
	{
		x = xmin;
		y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y<<" pointName: "<<temp->pointName;

		node* newPoint = newNode(make_pair(x,y),temp->pointName + '\''); 
		newPoint->out = true;
		newPoint->next = temp->next;
		temp->next = newPoint;
		temp = temp->next;

	}
	else if(edge == "RIGHT")
	{
		y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
		x = xmax;		
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y<<" pointName: "<<temp->pointName;

		node* newPoint = newNode(make_pair(x,y),temp->pointName + '\''); 
		newPoint->out = true;
		newPoint->next = temp->next;
		temp->next = newPoint;
		temp = temp->next;
	
	}
	else if(edge == "TOP")
	{
		x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
		y = ymax;
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y<<" pointName: "<<temp->pointName;

		node* newPoint = newNode(make_pair(x,y),temp->pointName + '\''); 
		newPoint->out = true;
		newPoint->next = temp->next;
		temp->next = newPoint;
		temp = temp->next;
	
	}
	else
	{
		x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
		y = ymin;
		cout<<"\n"<<edge<<" CLIP"<<" x0:"<<x0<<" y0:"<<y0<<" x1:"<<x1<<" y1:"<<y1<<" x:"<<x<<" y:"<<y<<" pointName: "<<temp->pointName;


		node* newPoint = newNode(make_pair(x,y),temp->pointName + '\''); 
		newPoint->out = true;
		newPoint->next = temp->next;
		temp->next = newPoint;
		temp = temp->next;
	}
}
void SH(int xmin,int ymin,int xmax,int ymax,string edge)
{
	temp = head;
	
		
	do{
			int x0 = temp->point.first,
			y0 = temp->point.second,
			x1 = temp->next->point.first,
			y1 = temp->next->point.second;

		if(edge == "LEFT"){
			if( inside(temp->point,xmin,ymin,xmax,ymax,edge)){
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
					temp->next->out = true;
				else
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);
				}
			}else
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
				{ intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);}
		}
		
		else if(edge == "RIGHT"){
			if( inside(temp->point,xmin,ymin,xmax,ymax,edge)){
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
					temp->next->out = true;
				else
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);
					

				}
			}else
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);
					
				}
		}
		else if(edge == "TOP"){

			if( inside(temp->point,xmin,ymin,xmax,ymax,edge)){
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
					temp->next->out = true;
				else
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);
					

				}
			}else
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);
				}
		}
		else if(edge == "BOTTOM"){

			if( inside(temp->point,xmin,ymin,xmax,ymax,edge)){
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
					temp->next->out = true;
				else
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);

				}
			}else
				if(( inside(temp->next->point,xmin,ymin,xmax,ymax,edge)))
				{
					intercept(xmin,ymin,xmax,ymax,x0,y0,x1,y1,edge);
				}
		}
		cout<<"\n---- temp:"<<temp->point.first<<" "<<temp->point.second<<endl;
		temp = temp->next; 	
		
	} while (temp != head);
	

}

void SH2()
{
	char alpha = 'P';
	int x = 0,y = 0;
		
	for (int i = 0; i < 4; i++)
	{
		cout<<alpha<<"\tx:";cin>>x;
		cout<<"\ty:";
		cin>>y;
		cout<<endl;
		if(head2 == NULL)
		{	
			head2 = newNode(make_pair(x,y),string(1,alpha++));
			temp2 = head2;
		}else{
			temp2->next = newNode(make_pair(x,y),string(1,alpha++));
			temp2 = temp2->next;
		}
	}
	temp2->next = head2;
	temp2 = head2;
	
	int xmin = temp2->point.first,
		ymin = temp2->point.second,
		xmax = temp2->next->next->point.first,
		ymax = temp2->next->point.second;

	for( auto s:boundary)
		SH(xmin,ymin,xmax,ymax,s);
	

	
}

int main()
{
	int n = 0, x = 0,y = 0;
	cout<<"Enter no. of vertices:";
	cin>>n;
	char alpha = 'A';
	for (int i = 0; i < n; i++)
	{
		cout<<alpha<<"\tx:";
		cin>>x;
		cout<<"\ty:";
		cin>>y;
		cout<<endl;
		if(head == NULL)
		{	
			head = newNode(make_pair(x,y),string(1,alpha++));
			temp = head;
		}else{
			temp->next = newNode(make_pair(x,y),string(1,alpha++));
			temp = temp->next;
		}
	}
	temp->next = head;
	
	SH2();
	out(head);
	//cout<<head->pointName<<endl;
	//cout<<head->next->pointName<<endl;
	//cout<<head->next->next->pointName<<endl;
	//cout<<head->next->next->next->pointName<<endl;
}	
