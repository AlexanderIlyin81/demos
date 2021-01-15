#include "MainWindow.h"
#include <QPainter>
#include <QMessageBox>


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
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_btnAdd_clicked()
{
	Point c( 400.0 * rand() / RAND_MAX, 300.0 * rand() / RAND_MAX );
	unsigned vertices = 10 * rand() / RAND_MAX + 4;

	if( rbCircle->isChecked() )
		m_pScene->addCircle( c, 10.0 );
	else if( rbTriangle->isChecked() )
		m_pScene->addTriangle( c, 10.0 );
	else if( rbSquare->isChecked() )
		m_pScene->addSquare( c, 10.0 );
	else if( rbRectangle->isChecked() )
		m_pScene->addRectangle( c, 30.0, 20.0 );
	else if( rbPolygon->isChecked() )
		m_pScene->addPolygon( vertices, c, 30.0 );
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
