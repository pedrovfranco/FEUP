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
T max(const T &a, const T &b)
{
	if (a<b)
		return b;
	else
		return a;
}

Result min(const Result &a, const Result &b)
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

	for (int i = left; i <= right; i++)
	{
		for (int j = i+1; j <= right; j++)
		{
			if (vp[j].y - vp[i].y > res.dmin)
				break;

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
 * using at most hreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	Result res;

	// Base case of two points
	if (right - left == 1)
	{
		return Result(vp[left].distance(vp[right]), vp[left], vp[right]);
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if (left >= right)
	{
		return res; // returns MAX_DOUBLE
	}

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	Result half1, half2;
	if (numThreads > 1) {
		std::thread t( [&] () {half1 = np_DC(vp, left, (right + left)/2, numThreads/2);});
		half2 = np_DC(vp, (right + left)/2 + 1, right, numThreads/2);
		t.join();
	}
	else {
		 half1 = np_DC(vp, left, (right + left)/2, numThreads);
		 half2 = np_DC(vp, (right + left)/2 + 1, right, numThreads);

	}

	// Select the best solution from left and right
	Result minimum = min(half1, half2);

	// Determine the strip area around middle point
	double deltax = minimum.dmin;
	double midX = vp[(right + left)/2].x;
	int beginMid = left;
	int endMid = right;

	for (int i = left; i <= right; i++) // Finds mid limit at right
	{
		if (vp[i].x > (midX - deltax))
		{
			beginMid = i;
			break;
		}
	}

	for (int i = right; i >= left; i--) // Finds mid limit at left
	{
		if (vp[i].x < (midX + deltax))
		{
			endMid = i;
			break;
		}
	}

  if (beginMid >= endMid)
  	return minimum;

	// Order points in strip area by Y coordinate
	sortByY(vp, beginMid, endMid);

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp, beginMid, endMid, minimum);

	// Reorder points in strip area back by X coordinate
	sortByX(vp, beginMid, endMid);

	return minimum;
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
