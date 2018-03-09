/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

template<class T>
T max(T &a, T &b)
{
	if (a>b)
		return a;
	else
		return b;
}

template<class T>
T min(T &a, T &b)
{
	if (a<b)
		return a;
	else
		return b;
}

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}


static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;
	res.dmin = 0.0;

	if (vp.size() < 2)
		return res;

	res.dmin = vp[0].distance(vp[1]);

	for (int i = 0; i < vp.size(); i++)
	{
		for (int j = i+1; j < vp.size(); j++)
		{
			if (vp[i].distance(vp[j]) < res.dmin)
			{
				res.dmin = vp[i].distance(vp[j]);
				res.p1 = vp[i];
				res.p2 = vp[j];
			}
		}
	}

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	// TODO
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
	if (vp.size() < 2)
		return;

	for (int i = 0; i < vp.size(); i++)
	{
		for (int j = i+1; j < vp.size(); j++)
		{
			if (vp[i].distance(vp[j]) < res.dmin)
			{
				res.dmin = vp[i].distance(vp[j]);
				res.p1 = vp[i];
				res.p2 = vp[j];
			}
		}
	}
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	Result res;

	// Base case of two points
	if (right - left == 2)
	{
		res.dmin = vp[0].distance(vp[1]);
		return res;
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if (right - left < 2)
	{
		res.dmin = MAX_DOUBLE;
		return res;
	}

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	Result half1 = np_DC(vp, 0, (vp.size()-1)/2, numThreads);
	Result half2 = np_DC(vp, (vp.size()-1)/2 + 1, vp.size() - 1, numThreads);

	// Select the best solution from left and right
	Result min = min(half1, half2);

	// Determine the strip area around middle point
	double deltax = min.dmin;
	double midX = (v.front().x + v.back().x)/2;
	int beginMid;
	int endMid;

	for (int i = 0; i < v.size(); i++)
	{
		if (vp[i].x > midX - deltax)
		{
			beginMid = i;
			break;
		}
	}

	for (int i = v.size(); i >= 0; i--)
	{
		if (vp[i].x < midX + deltax)
		{
			endMid = i;
			break;
		}
	}

	// Order points in strip area by Y coordinate
	sortByY(vp, beginMid, endMid);

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp, beginMid, endMid, min);

	// Reorder points in strip area back by X coordinate
	sortByx(vp, 0, vp.size()-1);

	return min;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}

bool Result::operator<(const Result &r) const
{
	return (this->dmin < r.dmin);
}
