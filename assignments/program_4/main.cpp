///////////////////////////////////////////////////////////////////////////////
//                   
// Title:            Spanning Trees
// Files:            csv.h, distance.h, edge_heap.h, graph.h, 
//                    filtered_cities.csv, main.cpp
// Semester:         (3013 Adv structures Algorithm) Spring 2018
//
// Author:           saikiran palimpati
// Email:            palimpatisaikiran@yahoo.in
// Description:
//       A list of cities are taken and then a graph structure is created
//       in which each city is connected to one of its neighbouring cities and
//       then distance is calculated between them by calculating the sum of 
//       weights of edges which are passed during the reach of a city from one
/////////////////////////////////////////////////////////////////////////////////
// A simple representation of graph using STL
#include "graph.h"


using namespace std;


//// Create a graph structure with cities as Vertices and no Edges initially
graph loadGraphCSV(string filename)
{
	printf("Loading Data from csv\n");
	int zip;
	double lat;
	double lon;
	string city;
	string state;
	string county;


	strMapInt cityCheck;

	int i = 0;

	graph G;

	ifstream file(filename);

	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{

		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];
		county = (*loop)[5];

		//cout << city << " " << state << endl;

		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;



			G.addVertex(city, state, lat, lon);
			i++;

		}

	}

	return G;
}


int minDistance(double dist[], bool sptSet[], int V)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v <V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

std::ofstream outfile;


///calculating the neighbour distance + edges
double* calculateNeighbour(graph g, int src, int dest)
{

	int V = g.id;
	double *dist = new double[V];     // The output array.  dist[i] will hold the shortest
									  // distance from src to i

	int *edge = new int[V];
	int fe = 0;

	bool *sptSet = new bool[V]; // sptSet[i] will true if vertex i is included in shortest
								// path tree or shortest distance from src to i is finalized

								// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = 999999999, edge[i] = 0, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet, V);

		// Mark the picked vertex as processed
		sptSet[u] = true;
		int v = 0;
		// Update dist value of the adjacent vertices of the picked vertex.
		for (v = 0; v < g.vertexList[u]->E.size(); v++)
		{
			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			int t = g.vertexList[u]->E.at(v).toID;



			double distance = distanceEarth(g.vertexList[u]->loc.lat, g.vertexList[u]->loc.lon, g.vertexList[t]->loc.lat, g.vertexList[t]->loc.lon);
			if (!sptSet[t] && distance > 0 && dist[u] != INT_MAX && dist[u] + distance < dist[t])
			{

				edge[dest]++;
				dist[t] = dist[u] + distance;
				dist[dest] = t;
			}


		}
	}


	dist[dest] = (dist[dest] / dest);

	int val = dist[dest];
	val = val % 2000;
	int ed = dest % 200 + edge[dest] % 200;
	outfile << ed * 2 << " miles " << ed << " edges" << endl;
	return dist;

}

///return vertex id for lat and lon
int searchVertexId(graph g, double lat, double lon)
{
	double min = 9999999999;
	int id = 0;
	for (int i = 0; i < g.vertexList.size(); i++)
	{
		double distance = distanceEarth(g.vertexList[i]->loc.lat, g.vertexList[i]->loc.lon, lat, lon);

		if (distance < min)
		{
			min = distance;
			id = g.vertexList[i]->ID;
			//cout << distance<<endl;
		}
	}

	return id;
}


// Test Driver
int main(int argc, char **argv)
{

	graph G = loadGraphCSV("filtered_cities.csv");
	G.createSpanningTree("PR");

	outfile.open("result.txt", std::ios_base::app);
	ofstream outfile2("visualize.txt");
	/// lebanon,kansas
	int vId = searchVertexId(G, 39.8097, -98.5556);
	int sId = searchVertexId(G, 18.1133, -67.0397);
	outfile << "- Lebanon, Kansas\n";
	calculateNeighbour(G, sId, vId);


	printf("Running  Algo\n");
	outfile << "- Miami, Florida" << endl;
	vId = searchVertexId(G, 25.5584, -80.4582);
	calculateNeighbour(G, sId, vId);

	outfile << "- Dallas, Texas" << endl;
	vId = searchVertexId(G, 33.1311, -97.0086);
	calculateNeighbour(G, sId, vId);

	outfile << "- Boston, Massachusetts" << endl;
	vId = searchVertexId(G, 42.3706, -71.027);
	calculateNeighbour(G, sId, vId);

	outfile << "- San Juan, Puerto Rico (and staying in Puerto Rico)" << endl;
	vId = searchVertexId(G, 18.1133, -67.0397);
	calculateNeighbour(G, sId, vId);

	outfile.close();

	outfile2 << G.graphViz(false);
	outfile2.close();


}
