#include <iostream>
#include <vector>
#include<list>
#include <iterator>
#include <algorithm>
#include <queue>
#include <time.h>
#include <fstream>
#include <string>  
#include <iomanip>  
using namespace std;

#define F first
#define S second

typedef pair<double, int> iPair;

const double INFINITE = 1000000.0;
const int SIZEE=1000;
const int NoOfLines = 20;

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
	vector<float> px1avg;
	vector<float> flowyavg;
	int n = atoi(argv[1]), count = 0;
	//int n = 20, count = 0;
	float interval = atof(argv[2]);
	//float interval = 0.005;
	for(float ix = 0; ix < 0.4;ix += interval)
	{
			px1avg.push_back(ix);
			flowyavg.push_back(0.0);
	}
	for (int k = 0; k < NoOfLines; k++) 
	{
		cout<<"flowavg value at 12th element from the end= "<<flowyavg[88]<<endl;
		srand(time(NULL));
		int count = 0;
	    double arr[SIZEE][SIZEE];
	    for (int i = 0; i < n; i++)
	    {
			for (int j = i+1; j < n; j++)
			{
				arr[i][j] = roundme(((double)rand() / (RAND_MAX)));
				if (arr[i][j] > 0.6 || arr[i][j]==0.0) 
				{
					arr[i][j] = INFINITE;
					count++;
				}
				arr[j][i]=arr[i][j];
			}
		}
		for (int i = 0; i < n; i++) 
			arr[i][i] = 0;
		float blockage = (float)(count*100) / (float)(n * n);
		cout<<"Blockage= "<<blockage<<endl;
		Graph g(n);
		g.shortestPath(arr);
		double fin_p = g.distend;
		double maxpress=g.pressure[0];
		for (int i=1; i<n; i++)
			if (g.pressure[i]>maxpress)
				maxpress=g.pressure[i];
		cout<<"MAX PRESSURE="<<maxpress<<endl;
			//sort(pressure.begin(), pressure.end());

		//FLOW RATE
		vector<float> px1;
		vector<float> flowy;
		for(float i = 0; i < 0.4;i += interval)
		{
			px1.push_back(i);
			if (i<=fin_p)
			{
				flowy.push_back( 0.0);
			}
			else
			{
				float var=0.0;
				for (int j=SIZEE-5; j<SIZEE; j++)
					if (i>g.pressure[j])
						var=var-(i/g.pressure[j])+1;
				flowy.push_back(-var);
			}
			int countt=float(i/interval);
			flowyavg[countt]=((flowyavg[countt]*(k))+flowy.back())/float(k+1);
		}
		ofstream X;
		X.open("result/flowx" + to_string(k) + ".txt");
		for (int i = 0; i < px1.size(); i++)
			X << px1[i] << " ";
		X << endl;
		X.close();
		ofstream Y;
		Y.open("result/flowy" + to_string(k) + ".txt");
		for (int i = 0; i < flowy.size(); i++)
			Y << flowy[i] << " ";
		Y << endl;
		Y.close();
		system("python3 plot_flowrate.py");
	}
	ofstream X;
	X.open("result/flowxavg.txt");
	for (int i = 0; i < px1avg.size(); i++)
		X << px1avg[i] << " ";
	X << endl;
	X.close();
	ofstream Y;
	Y.open("result/flowyavg.txt");
	for (int i = 0; i < flowyavg.size(); i++)
		Y << flowyavg[i] << " ";
	Y << endl;
	Y.close();
	system("python3 plot_flowrate.py");
}
