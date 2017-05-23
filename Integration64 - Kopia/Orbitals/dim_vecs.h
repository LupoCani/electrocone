#pragma once


struct vec_3;

double atan2(vec_3 in);
double vmag(double x, double y, double z);
double vmag(vec_3 in);
double sqr(double in);

struct ang_2
{
	double xz = 0;
	double xy = 0;
};

struct vec_3
{
	double x = 0;
	double y = 0;
	double z = 0;

	vec_3(double in_x = 0, double in_y = 0, double in_z = 0)
	{
		x = in_x;
		y = in_y;
		z = in_z;
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

	vec_3& operator +=(const vec_3& rhs)
	{
		(*this).x = (*this).x + rhs.x;
		(*this).y = (*this).y + rhs.y;
		return *this;
	}

	vec_3& operator-=(const vec_3& rhs)
	{
		(*this).x = (*this).x - rhs.x;
		(*this).y = (*this).y - rhs.y;
		return *this;
	}
	vec_3& operator*=(const vec_3& rhs)
	{
		(*this).x = (*this).x * rhs.x;
		(*this).y = (*this).y * rhs.y;
		return *this;
	}
	vec_3& operator*=(const double& rhs)
	{
		(*this).x = (*this).x * rhs;
		(*this).y = (*this).y * rhs;
		return *this;
	}
};

inline vec_3 operator+(vec_3 lhs, const vec_3& rhs)
{
	lhs += rhs;
	return lhs;
}

inline vec_3 operator-(vec_3 lhs, const vec_3& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline vec_3 operator*(vec_3 lhs, const vec_3& rhs)
{
	lhs *= rhs;
	return lhs;
}
inline vec_3 operator*(vec_3 lhs, const double& rhs)
{
	lhs *= rhs;
	return lhs;
}

double sqr(double in)	//Because writing pow(num, 2) all the time got annoying.
{
	return in*in;
}

double atan2(vec_3 pos)
{
	return std::atan2(pos.y, pos.x);
}

double vmag(double x, double y, double z)
{
	return sqrt(sqr(x) + sqr(y) + sqr(z));
}

double vmag(vec_3 in)
{
	return vmag(in.x, in.y, in.z);
}