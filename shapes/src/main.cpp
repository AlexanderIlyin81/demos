#include <QApplication>
#include "MainWindow.h"


int main( int argc, char* argv[] )
{
	QApplication a( argc, argv );

	MainWindow mw;
	mw.show();

	a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
	return a.exec();
}
