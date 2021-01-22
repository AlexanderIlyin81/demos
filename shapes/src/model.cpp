#include "model.h"
#include <algorithm>
#include <cmath>


#if _MSC_VER == 1500

class ShapeDrawer
{
public:
	ShapeDrawer( Painter& p )
		: m_Painter( p )
	{}

	void operator() ( const Shape_t& shape )
	{
		shape->draw( m_Painter );
	}

private:
	Painter& m_Painter;
};

class ShapeMover
{
public:
	ShapeMover( Time t )
		: m_Time( t )
	{}

	void operator() ( Shape_t& shape )
	{
		shape->move( m_Time );
	}

private:
	Time m_Time;
};

#endif // _MSC_VER == 1500

Shape::Shape( const Point& c, double r, const Velocity& v  )
: center( c ), radius( r ), velocity( v )
{
}

void Shape::move( Time t )
{
	center += velocity * t;
}

Edge::Edge( const Point& _begin, const Point& _end )
: Shape( Point( ( _begin.x + _end.x ) / 2, ( _begin.y + _end.y ) / 2  ),
		sqrt( pow( _begin.x - _end.x, 2 ) + pow( _begin.y - _end.y, 2 ) ), Velocity( 0, 0 ) ),
	begin( _begin ), end( _end )
{
}

void Edge::draw( Painter& p ) const
{
	p.drawLine( begin, end );
}


Circle::Circle( const Point& c, double r, const Velocity& v )
: Shape( c, r, v )
{
}

void Circle::draw( Painter& p ) const
{
	p.drawCircle( center, radius );
}

Polygon::Polygon( unsigned vertices, const Point& c, double r, const Velocity& v )
: Shape( c, r, v ), num_vertices( vertices )
{
}

void Polygon::draw( Painter& p ) const
{
	ShapeList_t edges;

#if _MSC_VER == 1500
	ShapeDrawer d( p );
#endif // _MSC_VER == 1500

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

		edges.push_back( Shape_t( new Edge( p1, p2 ) ) );
	}

#if _MSC_VER == 1500
	for_each( edges.begin(), edges.end(), d );
#else
	for_each( edges.begin(), edges.end(), [ &p ]( const auto& e ) { e->draw( p ); } );
#endif // _MSC_VER == 1500
}

Rectangle::Rectangle( const Point& c, double w, double h, const Velocity& v )
: Shape( c, sqrt( w * w + h * h ), v ), width( w ), height( h )
{
}

void Rectangle::draw( Painter& p ) const
{
	ShapeList_t edges;

#if _MSC_VER == 1500
	ShapeDrawer d( p );
#endif // _MSC_VER == 1500

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
		edges.push_back( Shape_t( new Edge( pts[ i % 4 ], pts[ ( i + 1 ) % 4 ] ) ) );

#if _MSC_VER == 1500
	for_each( edges.begin(), edges.end(), d );
#else
	for_each( edges.begin(), edges.end(), [ &p ]( const auto& e ) { e->draw( p ); } );
#endif // _MSC_VER == 1500
}

Scene::~Scene()
{
}

void Scene::addCircle( const Point& c, double r, const Velocity& v )
{
	shapes.push_back( Shape_t( new Circle( c, r, v ) ) );
}

void Scene::addTriangle( const Point& c, double r, const Velocity& v )
{
	shapes.push_back( Shape_t( new Polygon( 3, c, r, v ) ) );
}

void Scene::addSquare( const Point& c, double r, const Velocity& v )
{
	shapes.push_back( Shape_t( new Polygon( 4, c, r, v ) ) );
}

void Scene::addRectangle( const Point& c, double w, double h, const Velocity& v )
{
	shapes.push_back( Shape_t( new Rectangle( c, w, h, v ) ) );
}

void Scene::addPolygon( unsigned vertices, const Point& c, double r, const Velocity& v )
{
	shapes.push_back( Shape_t( new Polygon( vertices, c, r, v ) ) );
}

void Scene::draw( Painter& p ) const
{
#if _MSC_VER == 1500
	ShapeDrawer d( p );
	for_each( shapes.begin(), shapes.end(), d );
#else
	for_each( shapes.begin(), shapes.end(), [ &p ]( const auto& s ) { s->draw( p ); } );
#endif // _MSC_VER == 1500
}

void Scene::move( Time t )
{
#if _MSC_VER == 1500
	ShapeMover m( t );
	for_each( shapes.begin(), shapes.end(), m );
#else
	for_each( shapes.begin(), shapes.end(), [ t ]( const auto& s ) { s->move( t ); } );
#endif // _MSC_VER == 1500
}
