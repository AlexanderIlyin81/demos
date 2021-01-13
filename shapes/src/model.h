#ifndef MODEL_H
#define MODEL_H


#include <vector>


struct Point
{
	Point( double _x, double _y )
		: x( _x ), y( _y )
	{}

	double x;
	double y;
};

class Painter
{
public:

	virtual void drawCircle( const Point& center, double radius ) = 0;
	virtual void drawLine( const Point& p1, const Point& p2 ) = 0;
};

class Shape
{
public:
	Shape( const Point& c, double r );

	virtual void draw( Painter& p ) const = 0;

protected:
	Point center;
	double radius;
};

class Edge: public Shape
{
public:

	Edge( const Point& _begin, const Point& _end );

	virtual void draw( Painter& p ) const override;

private:
	Point begin;
	Point end;
};

class Circle: public Shape
{
public:

	Circle( const Point& c, double r );

	virtual void draw( Painter& p ) const override;
};

class Polygon: public Shape
{
public:

	Polygon( unsigned vertices, const Point& c, double r );

	virtual void draw( Painter& p ) const override;

private:
	unsigned num_vertices;
};

class Scene
{
public:
	~Scene();

	void addCircle( const Point& c, double r );
	void addTriangle( const Point& c, double r );
	void addSquare( const Point& c, double r );
	void addRectangle( const Point& c, double r );
	void addPolygon( unsigned vertices, const Point& c, double r );

	void draw( Painter& p ) const;

private:
	std::vector<Shape*> shapes;
};


#endif // MODEL_H
