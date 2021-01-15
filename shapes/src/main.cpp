#include <QApplication>
#include "MainWindow.h"

#include <windows.h>


int main( int argc, char* argv[] )
{
	QApplication a( argc, argv );

	srand( GetTickCount() );

	MainWindow mw;
	mw.show();

	a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
	return a.exec();
}
