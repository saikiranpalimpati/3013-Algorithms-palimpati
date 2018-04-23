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
#include <math.h>
#include <cmath> 
#define earthRadiusKm 6371.0
#define earthRadiusMi 3959.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * 3.1416 / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
	return (rad * 180 / 3.1416);
}

/**
* Returns the distance between two points on the Earth.
* Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
* @param lat1d Latitude of the first point in degrees
* @param lon1d Longitude of the first point in degrees
* @param lat2d Latitude of the second point in degrees
* @param lon2d Longitude of the second point in degrees
* @return The distance between the two points in kilometers
*/
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusMi * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}