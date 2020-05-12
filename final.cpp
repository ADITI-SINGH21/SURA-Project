#include <iostream>
#include <vector>
#include<list>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <time.h>
#include <fstream>
#include <string>  

using namespace std;

#define F first
#define S second

typedef pair<double, int> iPair;

const double INFINITE = 1000000.0;
const int SIZEE=200;

//----------------------------------------------------------
float roundme(float var) 
{ 
    float value = (int)(var * 1000 + .5); 
    return (float)value / 1000; 
} 
struct mindist
{
    bool operator() (iPair const &a, iPair const &b) { return a.F > b.F; }
};
class Graph 
{ 
    int V;   

  
public: 
    Graph(int V);  
    void shortestPath(double copy[][SIZEE]); 
	void printPath(int j);
	double distend;
	vector <int> parent;
	vector <double> pressure;
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
	distend = 0;
	for (int why=0;why<V;why++){
		pressure.push_back(INFINITE);
		parent.push_back(-1);
	}
} 

void Graph::shortestPath(double copy[SIZEE][SIZEE])
{
	//iPair= <pressure, node number>
	int n = V;
	priority_queue< iPair, vector <iPair> , mindist> pq; 
	pq.push(make_pair(0.0, 0));
	for (int i = 0; i < n; i++)
	{
		pressure[i] = INFINITE;
		parent[0] = -1;
	}
	pressure[0]=0.0;
	while (!pq.empty())
	{
		int u = pq.top().S;
		pq.pop();
		for (int ver = 0; ver < V; ver++) 
		{
			if (copy[u][ver]!=INFINITE)
				if ( pressure[ver]>pressure[u]+copy[u][ver])
				{ 
                // Updating distance of ver 
					pressure[ver]=pressure[u] + copy[u][ver]; 
					pq.push(make_pair(pressure[ver], ver)); 
					parent[ver] = u;
				}
		}
	}	
	int endindex = V - 5;
	distend=pressure[endindex];
	for (int ff = 1; ff < 5; ff++)
	{
		if (pressure[V - 5 + ff] < distend)
		{
			endindex = V - 5 + ff;
			distend = pressure[endindex];
		}
	}
	int src = 0;
	printf("Vertex\t Distance\tPath");
	printf("\n%d -> %d \t\t %f\t\t%d ",src, endindex, distend, src);
	printPath(endindex);
}

void Graph::printPath(int j)
{
	// Base Case : If j is source 
	if (parent[j] == -1)
		return;

	printPath(parent[j]);

	printf("%d ", j);
}



int main(int argc, char* argv[])
{
	int NoOfLines = 20;
	for (int k = 0; k < NoOfLines; k++) 
	{
		srand(time(NULL));
		int n = atoi(argv[1]), count = 0;
		//int n = 20, count = 0;
		float interval = atof(argv[2]);
		//float interval = 0.005;
	    double arr[SIZEE][SIZEE];
	    for (int i = 0; i < n; i++)
	    {
			for (int j = i+1; j < n; j++)
			{
				arr[i][j] = roundme(((double)rand() / (RAND_MAX)));
				if (arr[i][j] > 0.8 || arr[i][j]==0.0) 
				{
					arr[i][j] = INFINITE;
					count++;
				}
				arr[j][i]=arr[i][j];
			}
		}
		for (int i = 0; i < n; i++) 
			arr[i][i] = 0;
		float blockage = (float)count / (float)(n * n);
		Graph g(n);
		g.shortestPath(arr);
		double fin_p = g.distend;
		double maxpress=g.pressure[0];
		for (int i=1; i<n; i++)
			if (g.pressure[i]>maxpress)
				maxpress=g.pressure[i];
		cout<<"MAX PRESSURE="<<maxpress<<endl;
			//sort(pressure.begin(), pressure.end());
		//GRAPHSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS


		vector<float> px;
		vector<float> fracy;
		for(float i = 0; i < 0.1;i += interval)
		{
			int countt = 0;
			//cout<<i<<endl;
			px.push_back(i);
			for (int j=0; j<SIZEE; j++)
			{
				if ( (i-g.pressure[g.parent[j]]>=arr[j][g.parent[j]]))
					countt=countt+1;
			}
			fracy.push_back( (float) countt / (float)SIZEE);
		}
		ofstream X;
		X.open("result/X" + to_string(k) + ".txt");
		for (int i = 0; i < px.size(); i++)
			X << px[i] << " ";
		X << endl;
		X.close();
		ofstream Y;
		Y.open("result/Y" + to_string(k) + ".txt");
		for (int i = 0; i < fracy.size(); i++)
			Y << fracy[i] << " ";
		Y << endl;
		Y.close();
		system("python3 plot1.py");
	}

}
