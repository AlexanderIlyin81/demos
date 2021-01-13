#include "model.h"
#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>


class ShapeDrawer
{
public:
	ShapeDrawer( Painter& p )
		: m_Painter( p )
	{}

	void operator() ( const Shape* shape )
	{
		shape->draw( m_Painter );
	}

private:
	Painter& m_Painter;
};

void deleteShape( Shape* s )
{
	delete s;
}

Shape::Shape( const Point& c, double r )
: center( c ), radius( r )
{
}

Edge::Edge( const Point& _begin, const Point& _end )
: Shape( Point( ( _begin.x + _end.x ) / 2, ( _begin.y + _end.y ) / 2  ),
		sqrt( pow( _begin.x - _end.x, 2 ) + pow( _begin.y - _end.y, 2 ) ) ),
	begin( _begin ), end( _end )
{
}

void Edge::draw( Painter& p ) const
{
	p.drawLine( begin, end );
}


Circle::Circle( const Point& c, double r )
: Shape( c, r )
{
}

void Circle::draw( Painter& p ) const
{
	p.drawCircle( center, radius );
}

Polygon::Polygon( unsigned vertices, const Point& c, double r )
: Shape( c, r ), num_vertices( vertices )
{
}

void Polygon::draw( Painter& p ) const
{
	std::vector<Edge*> edges;
	ShapeDrawer d( p );

	for( unsigned i = 0; i < num_vertices; ++i )
	{
		double a1 = 2 * M_PI * i / num_vertices - M_PI_2;
		double a2 = 2 * M_PI * ( i + 1 ) / num_vertices - M_PI_2;

		Point p1( center.x + radius * cos( a1 ), center.y + radius * sin( a1 ) );
		Point p2( center.x + radius * cos( a2 ), center.y + radius * sin( a2 ) );

		edges.push_back( new Edge( p1, p2 ) );
	}

	for_each( edges.begin(), edges.end(), d );
	for_each( edges.begin(), edges.end(), deleteShape );
}

Scene::~Scene()
{
	for_each( shapes.begin(), shapes.end(), deleteShape );
}

void Scene::addCircle( const Point& c, double r )
{
	shapes.push_back( new Circle( c, r ) );
}

void Scene::addTriangle( const Point& c, double r )
{
	shapes.push_back( new Polygon( 3, c, r ) );
}

void Scene::addSquare( const Point& c, double r )
{
	shapes.push_back( new Polygon( 4, c, r ) );
}

void Scene::addRectangle( const Point& c, double r )
{
	shapes.push_back( new Polygon( 6, c, r ) );
}

void Scene::addPolygon( unsigned vertices, const Point& c, double r )
{
	shapes.push_back( new Polygon( 5, c, r ) );
}

void Scene::draw( Painter& p ) const
{
	ShapeDrawer d( p );

	for_each( shapes.begin(), shapes.end(), d );
}
