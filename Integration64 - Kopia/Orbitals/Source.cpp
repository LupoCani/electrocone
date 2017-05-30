#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>
#include <math.h>
#include <cmath>
#include <vector>
#include <string>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iso646.h>
#include "dim_vecs.h"

#define skip if (false)

using namespace std;

const double M_PI   = acos(-1.0);
const double M_2PI  = 2 * M_PI;
const double M_PI2  = M_PI * 0.5;
const double M_3PI2 = M_PI * 0.75;
const double M_RF = M_PI / 180.0;

sf::RenderWindow window(sf::VideoMode(1000, 1000), "Lorem Ipsum");




void putpixel(double x, double y, sf::Color cl)
{
	sf::Vertex point;

	point.position = sf::Vector2f(x, y);
	point.color = cl;

	window.draw(&point, 1, sf::Points);
}



struct elct
{
	short n = 0;
	short l = 0;
	short m = 0;
	short ms = 0;

	void increment()
	{
		m++;

		if (m >= 2 * l + 1)
		{
			m = 0;
			l++;
		}
		if (l >= n)
		{
			l = 0;
			ms++;
		}
		if (ms >= 2)
		{
			n++;
			ms = 0;
		}
	}
	void decrement()
	{
		m--;

		if (m < 0)
		{
			l--;
			m = 2 * l;
		}
		if (l < 0)
		{
			l = n - 1;
			ms--;
		}
		if (ms < 0)
		{
			ms = 1;
			n--;
		}

	}
};


inline bool operator==(elct &lhs, elct &rhs)
{
	if (lhs.n != rhs.n)
		return false;

	if (lhs.l != rhs.l)
		return false;

	if (lhs.m != rhs.m)
		return false;

	if (lhs.ms != rhs.ms)
		return false;

	return true;
}

template<class vec_cont>
void push_any(vector<vec_cont> &in, int ind, vec_cont element)
{
	vector<vec_cont>::iterator ref = in.begin();
	if (ind < 0)
		ref = in.end();

	in.insert(ref + ind, element);
}

template<class vec_cont>
void pop_any(vector<vec_cont> &in, int ind)
{
	vector<vec_cont>::iterator ref = in.begin();
	if (ind < 0)
		ref = in.end();

	in.erase(ref + ind);
}

template<class vec_cont>
int find_in(vector<vec_cont> &in, vec_cont element)
{
	for (int i = 0; i < in.size(); i++)
		if (in[i] == element)
			return i;

	return -1;
}

void main()
{
	srand(time(0));

	vector<elct> shells(3);
	short protons = 0;

	elct el1;
	elct el2;

	el1.l = 2;
	el2.l = 3;

	shells[0] = el1;
	shells[1] = el1;
	shells[2] = el2;

	cout << find_in(shells, el2) << endl;

	vec_2 vec;

	system("pause");



}