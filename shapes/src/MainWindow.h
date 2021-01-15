#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_MainWindow.h"
#include "model.h"

#include <memory>


class MainWindow: public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow( QWidget* parent = nullptr );
	virtual ~MainWindow();

protected:
	void paintEvent( QPaintEvent* pe ) override;
	void timerEvent( QTimerEvent* te ) override;

protected slots:
	void on_btnAdd_clicked();

private:
	std::unique_ptr<Scene> m_pScene;
};


#endif // MAINWINDOW_H
