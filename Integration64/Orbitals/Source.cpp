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
#define RIGHT 77
#define LEFT 75
#define mx getmaxx()/2
#define my getmaxy()/2-30
#define skip if (false)

#pragma warning (disable: 4996)

using namespace std;

const double M_PI = acos(-1.0);

sf::RenderWindow window(sf::VideoMode(1000, 1000), "Lorem Ipsum");

void putpixel(double x, double y, sf::Color cl)
{
	sf::Vertex point;

	point.position = sf::Vector2f(x, y);
	point.color = cl;

	window.draw(&point, 1, sf::Points);
}


class Spr {
private:
	float cosa, cosb, sina, sinb;

public:
	void ini(float cos1, float cos2)
	{
		cosa = cos(cos1 * M_PI / 180);
		cosb = cos((cos2)* M_PI / 180);
		sina = sin(cos1 * M_PI / 180);
		sinb = sin((cos2)* M_PI / 180);
	}

	void plot(float x, float y, float z, int &x1, int &y1)
	{
		x1 = x * cosa - y * sina;
		y1 = x * sina * sinb + y * cosa * sinb + z * cosb;
		x1 = 320 + int(x1);
		y1 = 240 - int(y1);
	}

	void plot1(float x, float y, float z, int xx, int yy, int &x1, int &y1)
	{
		float xx1, yy1;
		xx1 = x * cosa - y * sina;
		yy1 = x * sina * sinb + y * cosa * sinb + z * cosb;
		x1 = xx + int(xx1);
		y1 = yy + int(yy1);
	}

	void plot3d1(float x, float y, float z, int xx, int yy, sf::Color cl)
	{
		float xx1, yy1;
		int x1, y1;
		xx1 = x * cosa - y * sina;
		yy1 = x * sina * sinb + y * cosa * sinb + z * cosb;
		x1 = xx + int(xx1);
		y1 = yy + int(yy1);
		putpixel(x1, y1, cl);
	}

	void plot3d(float s, float t, float u, sf::Color cl)
	{
		int x1, y1;
		plot(s, t, u, x1, y1);
		putpixel(x1, y1, cl);
	}
};

void count_ref(float &s, float &t, float &u, float j, float i, float r)
{
	s = (r)*cos(i*M_PI / 180.0)*sin(j*M_PI / 180.0);
	t = (r)*sin(i*M_PI / 180.0)*sin(j*M_PI / 180.0);
	u = (r)*cos(j*M_PI / 180.0);
}

void main()
{
	srand(time(0));

	vector<Spr> a(10);
	vector<Spr> b(10);

	vector<int> c(10);

	float df, s, t, u, d;
	vector<float> p(10), p1(10), planet(10), r1(10);

	vector<int> x(20), y(20);

	for (int i = 0; i<10; i++)
	{
		p[i] = 0.0;
		p1[i] = 0.0;
	}
	s = 90.0;
	d = 1.0;
	planet[0] = 55.0;
	planet[1] = 18.0;
	planet[2] = 23.0;
	planet[3] = 22.0;
	planet[4] = 24.0;
	planet[5] = 40.0;
	planet[6] = 40.0;

	r1[1] = 100.0;
	r1[2] = 155.0;
	r1[3] = 210.0;
	r1[4] = 270.0;
	r1[5] = 250.0;
	r1[6] = 250.0;


	vector<sf::Color> colors =
	{
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color(100, 255, 100),
		sf::Color(255, 50, 255)
	};

	bool ever = true;
	for (;ever;)
	{
		for (int i = 0; i < 7; i++)
			a[i].ini(p[i], 45 + 90);

		for (int i = 1; i < 7; i++)
			b[i].ini(p1[i], 40 + 90);

		for (int i = 1; i < 7; i++)
			b[i].plot(r1[i], 0, 0, x[i], y[i]);

		for (float i = 0.0; i < 360.0; i += 5.0)
		{
			for (int i2 = 1; i2 < 5; i2++)
				b[i2].plot3d(r1[i2] * cos(i * M_PI / 180.0), r1[i2] * sin(i * M_PI / 180.0), 0, colors[i2]);
		}

		int i_max = 24;
		for (int i = 0.0; i < i_max; i += 1)
		{
			float ang = i * 360.0 / i_max;

			for (float i2 = 0.0; i2 < 360.0; i2 += 13.0)
			{
				count_ref(s, t, u, ang, i2, planet[0]);
				a[0].plot3d(s, t, u, sf::Color::Cyan);

				count_ref(s, t, u, ang, i2, planet[1]);
				a[1].plot3d1(s, t, u, x[1], y[1], sf::Color::Green);

				count_ref(s, t, u, ang, i2, planet[2]);
				a[2].plot3d1(s, t, u, x[2], y[2], sf::Color::Magenta);

				count_ref(s, t, u, ang, i2, planet[3]);
				a[3].plot3d1(s, t, u, x[3], y[3], sf::Color::White);

				count_ref(s, t, u, ang, i2, planet[4]);
				a[4].plot3d1(s, t, u, x[4], y[4], sf::Color::Yellow);
			}
		}
		//delay(1);
		//cleardevice();

		vector<float> p_inc = 
		{
			2.0f,
			0.8f,
			0.7f,
			0.8f,
			0.6f,
			0.5f,
			0.2f
		};
		vector<float> p1_inc =
		{
			0.2f,
			-0.1f,
			0.3f,
			-0.4f,
			0.5f,
			0.5f
		};

		for (int i = 0; i < 7; i++)
			p[i] += p_inc[i];

		for (int i = 0; i < 7; i++)
			p1[i] += p1_inc[i];

		window.display();
		_sleep(10);
		window.clear();

		if (kbhit())
		{
			//closegraph();
			exit(1);
		}
	}
}