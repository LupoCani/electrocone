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


struct elct
{
	short n = 1;
	short l = 0;
	short ml = 0;
	short ms = 0;

	void increment()
	{
		if (n < 1)
		{
			(*this) = elct();
			return;
		}

		ml++;

		if (ml >= 2 * l + 1)
		{
			ml = 0;
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
		if (n < 1)
			return;

		ml--;

		if (ml < 0)
		{
			l--;
			ml = 2 * l;
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

	elct operator++(int)
	{
		(*this).increment();
		return *this;
	}
	elct operator--(int)
	{
		(*this).decrement();
		return *this;
	}

};


inline bool operator==(elct &lhs, elct &rhs)
{
	if (lhs.n != rhs.n)
		return false;

	if (lhs.l != rhs.l)
		return false;

	if (lhs.ml != rhs.ml)
		return false;

	if (lhs.ms != rhs.ms)
		return false;

	return true;
}
inline bool operator!=(elct &lhs, elct &rhs)
{
	return !(lhs == rhs);
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

elct get_electron(int number)
{
	elct electron;

	for (int i = 0; i < number; i++)
		electron++;
}

int get_number(elct electron)
{
	elct comp;
	int i = 0;
	while (electron != comp)
	{
		i++;
		comp++;
	}
	return i;
}

vector<int> get_bounds(elct el)
{
	int num = get_number(el);

	elct el_up = el;
	int bound_up = 0;

	while (el_up.n == el.n)
	{
		el_up++;
		bound_up++;
	}

	elct el_down = el;
	int bound_down = 0;

	while (el_down.n == el.n)
	{
		el_down--;
		bound_down++;
	}
	bound_down--;

	int shell_size = bound_up + bound_down;
	int shell_pos = bound_down;

	return { shell_pos, shell_size };

}

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

void print_elec(elct in)
{
	int n = in.n;
	int l = in.l;
	int ml = in.ml;
	float ms = in.ms;

	if (ml % 2)
		ml = -ml / 2.0 + 0.5;
	else
		ml = ml / 2;

	ms -= 0.5;

	cout << "-----------------\n";

	cout << "n = " << n << endl;
	cout << "l = " << l << endl;
	cout << "n = " << ml << endl;
	cout << "n = " << ms << endl;

	cout << "-----------------\n";
}

void main_old()
{
	srand(time(0));

	double ang_base = 40;
	int select = 1;

	bool ever = true;

	int pl_count = 30;
	for (; ever;)
	{

		int orb_count = pl_count;

		vector<Spr> planets(pl_count);
		vector<Spr> orbits(orb_count);

		vector<int> c(10);

		float df, s, t, u, d;
		vector<float> planet_day(pl_count), planet_year(pl_count), planet(pl_count), radii(orb_count);

		vector<int> x_vec(pl_count), y_vec(pl_count);

		vector<sf::Color> colors(pl_count);
		vector<sf::Color> pl_colors(pl_count);

		s = 90.0;
		d = 1.0;
		planet[0] = 20.0;
		pl_colors[0] = sf::Color::White;


		ang_base += 0.002;


		vector<elct> elects;
		{
			elct elec_base;

			for (int i = 0; i < pl_count; i++)
			{
				vector<int> data = get_bounds(elec_base);

				planet_year[i] = 360.0 * (ang_base + data[0] / float(data[1]));
				planet_day[i] = planet_year[i] * 10;
				radii[i] = 75 * elec_base.n;
				planet[i] = 20;

				if (elec_base.ms)
					pl_colors[i] = sf::Color::Red;
				else
					pl_colors[i] = sf::Color::Blue;

				if (i == select)
					pl_colors[i] = sf::Color::Green;

				colors[i] = sf::Color::White;
				elects.push_back(elec_base);
				elec_base++;
			}
		}


		for (int i = 0; i < pl_count; i++)
			planets[i].ini(to_rad(planet_day[i]), to_rad(40));

		for (int i = 0; i < orb_count; i++)
			orbits[i].ini(to_rad(planet_year[i]), to_rad(40));

		for (int i = 0; i < orb_count; i++)
			orbits[i].plot_center(radii[i], 0, 0, x_vec[i], y_vec[i]);

		for (int i2 = 1; i2 < orb_count; i2++)
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
			float i2_max = 360.0 / 15.0;
			float i3_max = 360.0 / 13.0;

			for (int i = 0; i < pl_count; i++)
			{
				for (int i2 = 0.0; i2 < i2_max; i2++)
				{
					float ang = 360.0 * i2 / i2_max;

					for (int i3 = 0; i3 < i3_max; i3++)
					{
						float ang2 = 360.0 * i3 / i3_max;

						count_ref(s, t, u, ang, ang2, planet[i]);
						if (i == 0 && 0)
							planets[0].render_3d_center(s, t, u, pl_colors[i]);
						else
							planets[i].render_3d(s, t, u, x_vec[i], y_vec[i], pl_colors[i]);
					}
				}
			}
		}

		//delay(1);
		//cleardevice();

		window.display();
		_sleep(10);
		window.clear();

		if (kbhit())
		{
			//closegraph();
			exit(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				void;
			pl_count++;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				void;
			pl_count--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				void;

			select--;
			print_elec(elects[select]);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				void;

			select++;
			print_elec(elects[select]);
		}

		if (select < 0)
			select = 0;

		if (select >= pl_count)
			select = pl_count - 1;

		if (pl_count < 2)
			pl_count = 2;
	}
}

void main()
{
	main_old();
}