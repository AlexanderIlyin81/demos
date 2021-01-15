#include "MainWindow.h"
#include <QPainter>
#include <QMessageBox>


static int g_nInterval = 1;

class MyPainter: public Painter
{
public:
	MyPainter( QWidget* widget )
		: m_Painter( widget )
	{}

	void drawCircle( const Point& center, double radius )
	{
		m_Painter.drawEllipse( QPointF( center.x, center.y ), radius, radius );
	}

	void drawLine( const Point& p1, const Point& p2 )
	{
		m_Painter.drawLine( QPointF( p1.x, p1.y ), QPointF( p2.x, p2.y ) );
	}

private:
	QPainter m_Painter;
};

MainWindow::MainWindow( QWidget* parent )
: QMainWindow( parent ), m_pScene( new Scene )
{
	setupUi( this );

	startTimer( g_nInterval * 1000 );
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_btnAdd_clicked()
{
	Point c( 400.0 * rand() / RAND_MAX, 300.0 * rand() / RAND_MAX );
	unsigned vertices = 10 * rand() / RAND_MAX + 4;
	Velocity v( 5 * rand() / RAND_MAX - 2.5, 5 * rand() / RAND_MAX - 2.5 );

	if( rbCircle->isChecked() )
		m_pScene->addCircle( c, 10.0, v );
	else if( rbTriangle->isChecked() )
		m_pScene->addTriangle( c, 10.0, v );
	else if( rbSquare->isChecked() )
		m_pScene->addSquare( c, 10.0, v );
	else if( rbRectangle->isChecked() )
		m_pScene->addRectangle( c, 30.0, 20.0, v );
	else if( rbPolygon->isChecked() )
		m_pScene->addPolygon( vertices, c, 30.0, v );
	else
	{
		QMessageBox::critical( this, tr( "Error" ), tr( "No shape selected!" ) );
		return;
	}

	repaint();
}

void MainWindow::paintEvent( QPaintEvent* pe )
{
	MyPainter p( this );

	m_pScene->draw( p );
}

void MainWindow::timerEvent( QTimerEvent* te )
{
	m_pScene->move( g_nInterval );
	repaint();
}
