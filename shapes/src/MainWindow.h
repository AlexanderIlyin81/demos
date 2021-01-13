#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_MainWindow.h"
#include "model.h"


class MainWindow: public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow( QWidget* parent = NULL );
	virtual ~MainWindow();

protected:
	void paintEvent( QPaintEvent* pe ) override;

protected slots:
	void on_btnAdd_clicked();

private:
	std::auto_ptr<Scene> m_pScene;
};


#endif // MAINWINDOW_H
