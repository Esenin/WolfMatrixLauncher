#pragma once

#include <QMenu>
#include <QRegExp>
#include <QAction>
#include <QMenuBar>
#include <QMainWindow>

#include "clipboardObserver.h"
#include "matrixViewer.h"
#include "inputDialog.h"

//! @class MainWindow root carrier for other windows, actions processing
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void initMenuBar();

	//! @returns new instance of matrix viewer widget
	//! @param size of new matrix x = columns, y = rows
	MatrixViewer* createMatrixPage(QPoint const &matrixSize);
	//! parses input from dialog
	QPoint newMatrixSize(QString const &input);

	bool isValidMatrixSize(QPoint const &size);

protected slots:
	void showInputDialog();
	void getAnswer();
	void setupFromClipboard();
};

