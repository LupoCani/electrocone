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

float to_rad(float ang)
{
	return ang / 360.0 * M_2PI;
}

class Spr {
private:
	float x_a, x_b, y_a, y_b;

public:
	void ini(float ang_zx, float ang_yz)
	{
		x_a = cos(ang_zx);
		x_b = cos(ang_yz);
		y_a = sin(ang_zx);
		y_b = sin(ang_yz);
	}

	void plot_center(float x, float y, float z, int &x1, int &y1)
	{
		x1 = x * x_a - y * y_a;
		y1 = x * y_a * y_b + y * x_a * y_b + z * x_b;
		x1 = 320 + int(x1);
		y1 = 240 - int(y1);
	}

	void plot(float x, float y, float z, int xx, int yy, int &x1, int &y1)
	{
		float xx1, yy1;
		xx1 = x * x_a - y * y_a;
		yy1 = x * y_a * y_b + y * x_a * y_b + z * x_b;
		x1 = xx + int(xx1);
		y1 = yy + int(yy1);
	}

	void render_3d_center(float s, float t, float u, sf::Color cl)
	{
		int x1, y1;
		plot(s, t, u, 320, 240, x1, y1);

		putpixel(x1, y1, cl);
	}

	void render_3d(float x, float y, float z, int xx, int yy, sf::Color cl)
	{
		int x1, y1;
		plot(x, y, z, xx, yy, x1, y1);

		putpixel(x1, y1, cl);
	}
};

void count_ref(float &s, float &t, float &u, float ang_1, float ang_2, float r)
{
	ang_1 *= M_RF;
	ang_2 *= M_RF;

	s = r * cos(ang_2) * sin(ang_1);
	t = r * sin(ang_2) * sin(ang_1);
	u = r * cos(ang_1);
}

void main()
{
	srand(time(0));

	vector<Spr> planets(10);
	vector<Spr> orbits(10);

	vector<int> c(10);

	float df, s, t, u, d;
	vector<float> planet_day(10), planet_year(10), planet(10), radii(10);

	vector<int> x(20), y(20);

	for (int i = 0; i < 10; i++)
	{
		planet_day[i] = 0.0;
		planet_year[i] = 0.0;
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

	radii[1] = 100.0;
	radii[2] = 155.0;
	radii[3] = 210.0;
	radii[4] = 270.0;
	radii[5] = 250.0;
	radii[6] = 250.0;


	vector<sf::Color> colors =
	{
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color(100, 255, 100),
		sf::Color(255, 50, 255)
	};

	vector<sf::Color> pl_colors =
	{
		sf::Color::Green,
		sf::Color::Green,
		sf::Color::Magenta,
		sf::Color::White,
		sf::Color::Yellow
	};

	double ang_base = 40;

	bool ever = true;
	for (; ever;)
	{
		ang_base += 0.1;

		for (int i = 0; i < 7; i++)
			planets[i].ini(to_rad(planet_day[i]), to_rad(45 + ang_base));

		for (int i = 1; i < 7; i++)
			orbits[i].ini(to_rad(planet_year[i]), to_rad(40 + ang_base));

		for (int i = 1; i < 7; i++)
			orbits[i].plot_center(radii[i], 0, 0, x[i], y[i]);

		for (int i2 = 1; i2 < 5; i2++)
		{
			float i_max = 360.0 / 5.0;
			for (int i = 0; i < i_max; i++)
			{
				float ang = i / i_max * M_2PI;
				float x = radii[i2] * cos(ang);
				float y = radii[i2] * sin(ang);

				orbits[i2].render_3d_center(x, y, 0, colors[i2]);
			}
		}

		{
			float i_max = 360.0 / 15.0;
			float i2_max = 360.0 / 13.0;

			for (int i3 = 1; i3 < 5; i3++)
			{

				for (int i = 0.0; i < i_max; i++)
				{
					float ang = 360.0 * i / i_max;

					for (int i2 = 0; i2 < i2_max; i2++)
					{
						float ang2 = 360.0 * i2 / i2_max;

						count_ref(s, t, u, ang, ang2, planet[0]);
						planets[0].render_3d_center(s, t, u, sf::Color::Cyan);


						count_ref(s, t, u, ang, ang2, planet[i3]);
						planets[i3].render_3d(s, t, u, x[i3], y[i3], pl_colors[i3]);
					}
				}

			}

		}

		//delay(1);
		//cleardevice();

		vector<float> day_inc =
		{
			2.0f,
			0.8f,
			0.7f,
			0.8f,
			0.6f,
		};
		vector<float> year_inc =
		{
			0.0f,
			-0.1f,
			0.3f,
			-0.4f,
			0.5f,
		};

		for (int i = 0; i < 5; i++)
			planet_day[i] += day_inc[i];

		for (int i = 1; i < 5; i++)
			planet_year[i] += year_inc[i];

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