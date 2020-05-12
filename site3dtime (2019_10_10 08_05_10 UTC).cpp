#include <iostream>
#include <vector>
#include<list>
#include <iterator>
#include <algorithm>
#include <queue>
#include <ctime>
#include <fstream>
#include <string>  
#include <iomanip> 
#include <cmath>  
#include <cstdlib> 
using namespace std;

#define F first
#define S second


const double INFINITE = 1000000.0;
const int SIZEE=40;
const int NoOfLines = 10;
const int MaxPressure=25;

//----------------------------------------------------------
float roundme(float var) 
{ 
    float value = (int)(var * 1000 + .5); 
    return (float)value / 1000; 
} 



class qdata
{
public:
	double press;
	int loc[3];
	qdata(double press1,int loc1[]){
		press=press1;
		loc[0]=loc1[0];
		loc[1]=loc1[1];
		loc[2]=loc1[2];
	}
};
struct mindist
{
    bool operator() (qdata const &a, qdata const &b) { return a.press > b.press; }
};
class Graph 
{ 
    int V;   

  
public: 
    Graph(int V);  
    int shortestPath(double copy[][SIZEE][SIZEE]); 
	void printPath(int j[]);
	int Path(int j[3]);
	double distend;
	int parent[SIZEE][SIZEE][SIZEE][3];
	double pressure[SIZEE][SIZEE][SIZEE];
	vector <int> time;
	vector <int> sites;
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
	distend = INFINITE;
	for (int why=0;why<V;why++)
		for (int why2=0;why2<V;why2++)
			for (int why3=0;why3<V;why3++){
				pressure[why][why2][why3]=INFINITE;
				parent[why][why2][why3][0]=-1;
				parent[why][why2][why3][1]=-1;
				parent[why][why2][why3][2]=-1;
			}
} 

int Graph::shortestPath(double copy[SIZEE][SIZEE][SIZEE])
{
	//iPair= <pressure, node location>
	priority_queue< qdata, vector <qdata> , mindist> pq; 
	int loc[3]={(SIZEE-1)/2, (SIZEE-1)/2 , (SIZEE-1)/2};
	qdata fir(0.0, loc);
	pq.push(fir);
	int i;
	parent[((SIZEE-1)/2)][((SIZEE-1)/2)][((SIZEE-1)/2)][0] =-1 ;
	parent[((SIZEE-1)/2)][((SIZEE-1)/2)][((SIZEE-1)/2)][1] =-1 ;
	parent[((SIZEE-1)/2)][((SIZEE-1)/2)][((SIZEE-1)/2)][2] =-1 ;
	pressure[((SIZEE-1)/2)][((SIZEE-1)/2)][((SIZEE-1)/2)]=0.0;

	time.push_back(1);
	sites.push_back(1);
	int timecount=1;
	int sitecount=1;
	while (!pq.empty())
	{
		int u[3];
		u[0]= pq.top().loc[0];
		u[1]= pq.top().loc[1];
		u[2]= pq.top().loc[2];
		pq.pop();
		timecount+=1;
		time.push_back(timecount);
		if (u[0]-1 >=0)
		 if (copy[u[0]-1][u[1]][u[2]]!=INFINITE)
			if ( pressure[u[0]-1][u[1]][u[2]]>pressure[u[0]][u[1]][u[2]]+copy[u[0]-1][u[1]][u[2]])
			{ 
				pressure[u[0]-1][u[1]][u[2]]=pressure[u[0]][u[1]][u[2]]+copy[u[0]-1][u[1]][u[2]];
				int array[3]={u[0]-1, u[1] , u[2]};
				qdata data(pressure[u[0]-1][u[1]][u[2]], array);
				pq.push(data); 
				if (parent[u[0]-1][u[1]][u[2]][0]==-1)
					sitecount+=1;
				parent[u[0]-1][u[1]][u[2]][0] = u[0];
				parent[u[0]-1][u[1]][u[2]][1] = u[1];
				parent[u[0]-1][u[1]][u[2]][2] = u[2];

			}
		if (u[0]+1 <SIZEE)
		 if (copy[u[0]+1][u[1]][u[2]]!=INFINITE)
			if ( pressure[u[0]+1][u[1]][u[2]]>pressure[u[0]][u[1]][u[2]]+copy[u[0]+1][u[1]][u[2]])
			{ 
				pressure[u[0]+1][u[1]][u[2]]=pressure[u[0]][u[1]][u[2]]+copy[u[0]+1][u[1]][u[2]];
				int array[3]={u[0]+1, u[1] , u[2]};
				qdata data(pressure[u[0]+1][u[1]][u[2]], array);
				pq.push(data);
				if (parent[u[0]+1][u[1]][u[2]][0]==-1)
					sitecount+=1; 
				parent[u[0]+1][u[1]][u[2]][0] = u[0];
				parent[u[0]+1][u[1]][u[2]][1] = u[1];
				parent[u[0]+1][u[1]][u[2]][2] = u[2];

			}
		if (u[1]-1 >=0)
		 if (copy[u[0]][u[1]-1][u[2]]!=INFINITE)
			if ( pressure[u[0]][u[1]-1][u[2]]>pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]-1][u[2]])
			{ 
				pressure[u[0]][u[1]-1][u[2]]=pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]-1][u[2]];
				int array[3]={u[0], u[1]-1 , u[2]};
				qdata data(pressure[u[0]][u[1]-1][u[2]], array);
				pq.push(data); 
				if (parent[u[0]][u[1]-1][u[2]][0]==-1)
					sitecount+=1;
				parent[u[0]][u[1]-1][u[2]][0] = u[0];
				parent[u[0]][u[1]-1][u[2]][1] = u[1];
				parent[u[0]][u[1]-1][u[2]][2] = u[2];

			}
		if (u[1]+1 <SIZEE)
		 if (copy[u[0]][u[1]+1][u[2]]!=INFINITE)
			if ( pressure[u[0]][u[1]+1][u[2]]>pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]+1][u[2]])
			{ 
				pressure[u[0]][u[1]+1][u[2]]=pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]+1][u[2]];
				int array[3]={u[0], u[1]+1 , u[2]};
				qdata data(pressure[u[0]][u[1]+1][u[2]], array);
				pq.push(data); 
				if (parent[u[0]][u[1]+1][u[2]][0]==-1)
					sitecount+=1;				
				parent[u[0]][u[1]+1][u[2]][0] = u[0];
				parent[u[0]][u[1]+1][u[2]][1] = u[1];
				parent[u[0]][u[1]+1][u[2]][2] = u[2];

			}
		if (u[2]-1 >=0)
		 if (copy[u[0]][u[1]][u[2]-1]!=INFINITE)
			if ( pressure[u[0]][u[1]][u[2]-1]>pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]][u[2]-1])
			{ 
				pressure[u[0]][u[1]][u[2]-1]=pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]][u[2]-1];
				int array[3]={u[0], u[1] , u[2]-1};
				qdata data(pressure[u[0]][u[1]][u[2]-1], array);
				pq.push(data); 
				if (parent[u[0]][u[1]][u[2]-1][0]==-1)
					sitecount+=1;				
				parent[u[0]][u[1]][u[2]-1][0] = u[0];
				parent[u[0]][u[1]][u[2]-1][1] = u[1];
				parent[u[0]][u[1]][u[2]-1][2] = u[2];

			}
		if (u[2]+1 <SIZEE)
		 if (copy[u[0]][u[1]][u[2]+1]!=INFINITE)
			if ( pressure[u[0]][u[1]][u[2]+1]>pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]][u[2]+1])
			{ 
				pressure[u[0]][u[1]][u[2]+1]=pressure[u[0]][u[1]][u[2]]+copy[u[0]][u[1]][u[2]+1];
				int array[3]={u[0], u[1] , u[2]+1};
				qdata data(pressure[u[0]][u[1]][u[2]+1], array);
				pq.push(data); 
				if (parent[u[0]][u[1]][u[2]+1][0]==-1)
					sitecount+=1;	
				parent[u[0]][u[1]][u[2]+1][0] = u[0];
				parent[u[0]][u[1]][u[2]+1][1] = u[1];
				parent[u[0]][u[1]][u[2]+1][2] = u[2];
			}
		sites.push_back(sitecount);

		//cout<<"at node number "<<quo<<" "<<u-quo*SIZEE<<endl;
	}	

	/*for (i=0; i<V; i++){
		cout<<"Grid number: "<<i<<endl;
		for (int why=0; why<V; why++){
			for (int why2=0; why2<V; why2++)
				if (pressure[i]==INFINITE)
					printf("inff ");
				else
					printf("%.2f ",pressure[i]);
			cout<<endl;}
	}
    for (i=0; i<V; i++){
		cout<<"Grid number: "<<i<<endl;
		for (int why=0; why<V; why++){
			for (int why2=0; why2<V; why2++)
				printf("[%d %d %d]",parent[i][why][why2][0], parent[i][why][why2][1], parent[i][why][why2][2]);
			cout<<endl;}
	} */
	int endindex[3]={-1, -1, -1} ;
	distend=INFINITE;
	for (i = 0; i <SIZEE ; i++){
		for(int why=0; why<SIZEE; why++){
		//cout<<"heya "<<Path(ff);
			int array[3];
			array[0]=0;
			array[1]=i;
			array[2]=why;
			if (Path(array)==1)
				if(pressure[0][i][why] < distend)
				{
					endindex[0] = 0;
					endindex[1] = i;
					endindex[2] = why;
					distend = pressure[0][i][why];
				}
			array[0]=SIZEE-1;
			if (Path(array)==1)
				if(pressure[SIZEE-1][i][why] < distend)
				{
					endindex[0] = SIZEE-1;
					endindex[1] = i;
					endindex[2] = why;
					distend = pressure[SIZEE-1][i][why];
				}
			array[0]=i;
			array[1]=why;
			array[2]=0;
			if (Path(array)==1)
				if(pressure[i][why][0] < distend)
				{
					endindex[0] = i;
					endindex[1] = why;
					endindex[2] = 0;
					distend = pressure[i][why][0];
				}
			array[2]=SIZEE-1;
			if (Path(array)==1)
				if(pressure[i][why][SIZEE-1] < distend)
				{
					endindex[0] = i;
					endindex[1] = why;
					endindex[2] = SIZEE-1;
					distend = pressure[i][why][SIZEE-1];
				}
			array[0]=i;
			array[1]=0;
			array[2]=why;
			if (Path(array)==1)
				if(pressure[i][0][why] < distend)
				{
					endindex[0] = i;
					endindex[1] = 0;
					endindex[2] = why;
					distend = pressure[i][0][why];
				}
			array[1]=SIZEE-1;
			if (Path(array)==1)
				if(pressure[i][SIZEE-1][why] < distend)
				{
					endindex[0] = i;
					endindex[1] = SIZEE-1;
					endindex[2] = why;
					distend = pressure[i][SIZEE-1][why];
				}
		}	
	}
	

	if ((endindex[0]==-1)&&(endindex[1]==-1)&&(endindex[2]==-1))
		{cout<<"NO PATH"<<endl; return 0;}
	else {
	printf("Vertex\t Distance\tPath");
	printf("\n(%d,%d,%d) -> (%d,%d,%d) \t\t %f\t\t 0 ",loc[0], loc[1], loc[2], endindex[0],endindex[1],endindex[2],distend);
	//printPath(endindex);
	cout<<endl;
	return 1;}
}

int Graph::Path(int j[])
{
	if ((j[0]==-1)&&(j[1]==-1)&&(j[2]==-1))
		 return 0;
	else if ((j[0]==((SIZEE-1)/2))&&(j[1]==((SIZEE-1)/2))&&(j[2]==((SIZEE-1)/2)))
		 return 1;
	else {
		int array[3];
		array[0]=parent[j[0]][j[1]][j[2]][0];
		array[1]=parent[j[0]][j[1]][j[2]][1];
		array[2]=parent[j[0]][j[1]][j[2]][2];
		return Path(array);
	}
}
void Graph::printPath(int j[])
{
	// Base Case : If j is source 
	if ((parent[j[0]][j[1]][j[2]][0]==-1)&&(parent[j[0]][j[1]][j[2]][1]==-1)&&(parent[j[0]][j[1]][j[2]][2]==-1))
		return;
	//int x=parent[j[0]][j[1]][j[2]];
	//int array[3]={x[0], x[1], x[2]};
	printPath(parent[j[0]][j[1]][j[2]]);

	printf("[%d %d %d] ", j[0],j[1],j[2]);
}



int main(int argc, char* argv[])
{

	int count = 0;
	int n=SIZEE;
	//int n = 20, count = 0;
	float interval = atof(argv[1]);
	float margin = atof(argv[2]);
	int threshold=NoOfLines;
	float maxpressavg=0;
	
	
	
	srand(time(NULL));
	for (int k = 0; k < NoOfLines; k++) 
	{

		int count = 0;
	    double arr[SIZEE][SIZEE][SIZEE];
	    for (int i = 0; i < n; i++)
	    {
			for (int j = 0; j < n; j++)
				for(int k=0; k<n; k++)
				{
					arr[i][j][k] = roundme(((double)rand() / (RAND_MAX)));
					if (arr[i][j][k] > margin || arr[i][j][k]==0.0) 
					{
						arr[i][j][k] = INFINITE;
						count++;
					}
				}
			
		}
		arr[((SIZEE-1)/2)][((SIZEE-1)/2)][((SIZEE-1)/2)]=0.0;
		/*
		for (int index1=0; index1<SIZEE; index1++)
			{for(int index2=0;index2<SIZEE;index2++)
				if(arr[index1][ index2]>1)
					printf("inff ");
				else
					printf("%.2f ",arr[index1][index2]);
			cout<<endl;}
		*/
		float blockage = (float)(count*100) / (float)((n * n)*n);
		cout<<"Open Percentage= "<<100-blockage<<endl;
		Graph g(n);
		int temp=g.shortestPath(arr);
		if(temp==0)
			threshold-=1;
		double fin_p = g.distend;
		double maxpress=0;
		for (int i=1; i<n; i++)
			for(int j=1; j<n; j++)
				for(int k=1; k<n; k++)
					if (g.pressure[i][j][k]>maxpress && g.pressure[i][j][k]<INFINITE)
						maxpress=g.pressure[i][j][k];
		cout<<"MAX PRESSURE for line "<<k+1<<" = "<<maxpress<<endl;
		ofstream X;
		X.open("result/time"+to_string(k)+".txt");
		for (int i = 0; i < g.time.size(); i++)
			X << g.time[i] << " ";
		X << endl;
		X.close();
		ofstream Y;
		Y.open("result/sitey" + to_string(k) + ".txt");
		for (int i = 0; i < g.sites.size(); i++)
			Y << g.sites[i] << " ";
		Y << endl;
		Y.close();
	}

	system("python3 plot3dtime.py");

	cout<<"No. of solutions out of "<<NoOfLines<<" is "<<threshold<<endl;


}
