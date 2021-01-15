#include "model.h"
#include <algorithm>
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
		double a1 = 2 * M_PI * i / num_vertices;
		double a2 = 2 * M_PI * ( i + 1 ) / num_vertices;

		if( num_vertices % 2 )
		{
			a1 -= M_PI_2;
			a2 -= M_PI_2;
		}
		else
		{
			a1 -= M_PI_4;
			a2 -= M_PI_4;
		}

		Point p1( center.x + radius * cos( a1 ), center.y + radius * sin( a1 ) );
		Point p2( center.x + radius * cos( a2 ), center.y + radius * sin( a2 ) );

		edges.push_back( new Edge( p1, p2 ) );
	}

	for_each( edges.begin(), edges.end(), d );
	for_each( edges.begin(), edges.end(), deleteShape );
}

Rectangle::Rectangle( const Point& c, double w, double h )
: Shape( c, sqrt( w * w + h * h ) ), width( w ), height( h )
{
}

void Rectangle::draw( Painter& p ) const
{
	std::vector<Edge*> edges;
	ShapeDrawer d( p );

	double left = center.x - width / 2;
	double right = center.x + width / 2;
	double top = center.y - height / 2;
	double bottom = center.y + height / 2;

	Point pts[] = {
		Point( left, top ),
		Point( right, top ),
		Point( right, bottom ),
		Point( left, bottom )
	};

	for( int i = 0; i < 4; ++i )
		edges.push_back( new Edge( pts[ i % 4 ], pts[ ( i + 1 ) % 4 ] ) );

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

void Scene::addRectangle( const Point& c, double w, double h )
{
	shapes.push_back( new Rectangle( c, w, h ) );
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
