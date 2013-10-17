#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, mTempLabel(NULL)
{
	setWindowTitle("Wolfram matrix launcher");

	initMenuBar();

	showInputDialog();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuBar()
{
	QAction *actionNew_matrix = new QAction("New matrix", this);
	QAction *actionEsenin = new QAction("Esenin", this);
	QAction *actionExit = new QAction("Exit", this);

	QMenu *menuFile = this->menuBar()->addMenu(tr("&File"));

	menuFile->addAction(actionNew_matrix);
	menuFile->addSeparator();
	menuFile->addAction(actionEsenin);
	menuFile->addSeparator();
	menuFile->addAction(actionExit);

	connect(actionNew_matrix, SIGNAL(triggered()), this, SLOT(showInputDialog()));
	connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MatrixViewer *MainWindow::createMatrixPage(QPoint const &matrixSize)
{
	MatrixViewer *matrixPage = new MatrixViewer(this, matrixSize);
	connect(matrixPage, SIGNAL(urlPrepared(QString)), this, SLOT(urlQueryDone(QString)));
	return matrixPage;
}

QPoint MainWindow::newMatrixSize(QString const &input)
{
	QRegExp regExp("(\\d+)");
	QList<int> numList;

	int pos = 0;
	while ((pos = regExp.indexIn(input, pos)) != -1)
	{
		numList << regExp.cap(1).toInt();
		pos += regExp.matchedLength();
	}

	if (numList.isEmpty()) {
		numList << 0;
	}

	return QPoint(numList.last(), numList.first());
}

bool MainWindow::isValidMatrixSize(QPoint const &size)
{
	return (size.x() > 0) && (size.y() > 0);
}

void MainWindow::showInputDialog()
{
	InputDialog *dialog = new InputDialog(this);
	setCentralWidget(dialog);  // this cause old root widget->deleteLater()
	connect(dialog, SIGNAL(buttonPushed()), this, SLOT(getAnswer()));
}

void MainWindow::getAnswer()
{
	InputDialog *dialog = dynamic_cast<InputDialog *>(QObject::sender());
	if (!dialog) {
		return;
	}

	QString text = dialog->getInputText();
	QPoint newSize = newMatrixSize(text);
	if (text.size() == 0 || !isValidMatrixSize(newSize)) {
		return;
	}

	setCentralWidget(createMatrixPage(newSize));
}

void MainWindow::urlQueryDone(QString url)
{
	QWebView *view = new QWebView(this);
	connect(view, SIGNAL(loadProgress(int)), this, SLOT(showProgress(int)));
	connect(view, SIGNAL(loadFinished(bool)), this, SLOT(showWebView()));
	view->load(QUrl(url));

	mTempLabel = new QLabel(this);
	setCentralWidget(mTempLabel);
}

void MainWindow::showProgress(int progress)
{
	if (mTempLabel) {
		mTempLabel->setText(QString::number(progress));
	}
}

void MainWindow::showWebView()
{
	QWidget *widget = dynamic_cast<QWidget *>(QObject::sender());
	if (widget) {
		setCentralWidget(widget);
	}
}
