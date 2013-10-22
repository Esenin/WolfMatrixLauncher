#pragma once

#include <QMenu>
#include <QRegExp>
#include <QAction>
#include <QMenuBar>
#include <QMainWindow>

#include "clipboardObserver.h"
#include "matrixViewer.h"
#include "inputDialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void initMenuBar();
	MatrixViewer* createMatrixPage(QPoint const &matrixSize);
	QPoint newMatrixSize(QString const &input);
	bool isValidMatrixSize(QPoint const &size);

protected slots:
	void showInputDialog();
	void getAnswer();
	void setupFromClipboard();
};

