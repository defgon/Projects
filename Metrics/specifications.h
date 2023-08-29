#pragma once

#include <set>
#include <iostream>

template<typename T>
class Specification
{
public:
	virtual bool isSatisfied(const T& p) const = 0;

};

template<typename Cloud>
std::set<typename Cloud::Point>
filter(const Cloud& cloud, const Specification<typename Cloud::Point>& spec) 
{
	std::set<typename Cloud::Point> result;
	for (const auto& p : cloud) 
	{	
		if (spec.isSatisfied(p)) 
		{
			result.insert(p);
		}
	}
	return result;
}

/*
template <typename Cloud>
operator&&(const Specification<typename Cloud::Point>& spec1,
           const Specification<typename Cloud::Point>& spec2)
{
    return AndSpecification(spec1,spec2);
}
*/



template <typename Point>
class DistanceFromPointSpecification : public Specification<Point>
{
public:
	using Value = typename Point::value_type;
	using Metrika = std::function<Value(Point,Point)>;
	
	DistanceFromPointSpecification(Point c, Value r, Metrika dist) 
		:c(c), r(r), dist(dist)
	{}
	
	bool isSatisfied(const Point& p) const override
	{
		return dist(p, c) <= r;
	}

private:
	Point c;
	Value r;
	Metrika dist;
};

template <typename Point>
class SphericalShellSpecification : public Specification<Point>
{
public:
	using Value = typename Point::value_type;
	using Metrika = std::function<Value(Point, Point)>;

	SphericalShellSpecification(Point c, Value r,Value f, Metrika dist)
		:c(c), r(r), f(f) , dist(dist)
	{}

	bool isSatisfied(const Point& p) const override
	{
		return (r <= dist(p, c) && dist(p, c) <= f);
	}

private:
	Point c;
	Value r;
	Value f;
	Metrika dist;
	
};


template <typename Point>
class BoundingBoxSpecification : public Specification<Point>
{
public:
	using Value = typename Point::value_type;
	using Metrika = std::function<Value(Point, Point)>;

	BoundingBoxSpecification(Point c1, Point c2)
		:c1(c1), c2(c2)
    {        SetMin();
             SetMax();
    }

	void SetMin() 
	{
        for (int i = 0; i < 3; i++)
		{
            if (c1[i] > c2[i])
                min[i] = c2[i];
            else if(c1[i] < c2[i])
                min[i] = c1[i];
            else
                min[i] = c1[i];
		}
	}

	void SetMax()
	{
        for (int i = 0; i < 3; i++)
		{
			if (c1[i] < c2[i])
				max[i] = c2[i];
			else
				max[i] = c1[i];
		}
	}

	bool isSatisfied(const Point& p) const override
	{
        bool h = true;
        for (int i = 0; i < 3; i++)
		{
            if (min[i] > p[i] || max[i] < p[i])
            {
                h = false;
            }
		}
		return h;
	}

private:
	Point c1;
	Point c2;
    Point min;
	Point max;
	Metrika dist;
};


template <typename Point>
class AndSpecification : public Specification<Point>
{
	AndSpecification(const Specification<Point> operand1,
		const Specification<Point> operand2)
		: operand1(operand1), operand2(operand2)
	{}
	bool isSatisfied(const Point& p) const override
	{
        return operand1.isSatisfied(p) && operand2.isSatisfied(p);
    }
private:
	Specification<Point>& operand1, operand2;
};

template <typename Point>
class OrSpecification : public Specification<Point>
{
    OrSpecification(const Specification<Point> operand1,
        const Specification<Point> operand2)
        : operand1(operand1), operand2(operand2)
    {}
    bool isSatisfied(const Point& p) const override
    {
        return operand1.isSatisfied(p) || operand2.isSatisfied(p);
    }
private:
    Specification<Point>& operand1, operand2;
};

template <typename Point>
class ExSpecification : public Specification<Point>
{
    ExSpecification(const Specification<Point> operand)
        : operand(operand)
    {}
    bool isSatisfied(const Point& p) const override
    {
        return !(operand.isSatisfied(p));
    }
private:
    Specification<Point>& operand;
};



