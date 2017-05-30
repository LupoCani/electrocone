#pragma once


struct vec_2;

double atan2(vec_2 in);
double vmag(double x, double y);
double vmag(vec_2 in);
double sqr(double in);

struct vec_2
{
	double x = 0;
	double y = 0;

	vec_2(double in_x = 0, double in_y = 0, double in_z = 0)
	{
		x = in_x;
		y = in_y;
	}

	double mag()
	{
		return vmag(*this);
	}

	double ang()
	{
		return atan2(*this);
	}

	operator sf::Vector2f() {
		return sf::Vector2f(x, y);
	}

	/*
	operator phys::vec_r() {
		phys::vec_r lhs;
		lhs.ang = phys::atan2(*this);
		lhs.mag = phys::vmag(*this);
		return lhs;
	}*/

	vec_2& operator +=(const vec_2& rhs)
	{
		(*this).x = (*this).x + rhs.x;
		(*this).y = (*this).y + rhs.y;
		return *this;
	}

	vec_2& operator-=(const vec_2& rhs)
	{
		(*this).x = (*this).x - rhs.x;
		(*this).y = (*this).y - rhs.y;
		return *this;
	}
	vec_2& operator*=(const vec_2& rhs)
	{
		(*this).x = (*this).x * rhs.x;
		(*this).y = (*this).y * rhs.y;
		return *this;
	}
	vec_2& operator*=(const double& rhs)
	{
		(*this).x = (*this).x * rhs;
		(*this).y = (*this).y * rhs;
		return *this;
	}
};

inline vec_2 operator+(vec_2 lhs, const vec_2& rhs)
{
	lhs += rhs;
	return lhs;
}

inline vec_2 operator-(vec_2 lhs, const vec_2& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline vec_2 operator*(vec_2 lhs, const vec_2& rhs)
{
	lhs *= rhs;
	return lhs;
}
inline vec_2 operator*(vec_2 lhs, const double& rhs)
{
	lhs *= rhs;
	return lhs;
}

double sqr(double in)	//Because writing pow(num, 2) all the time got annoying.
{
	return in*in;
}

double atan2(vec_2 pos)
{
	return std::atan2(pos.y, pos.x);
}

double vmag(double x, double y)
{
	return sqrt(sqr(x) + sqr(y));
}

double vmag(vec_2 in)
{
	return vmag(in.x, in.y);
}