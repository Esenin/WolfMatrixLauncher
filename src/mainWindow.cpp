#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("Wolfram matrix launcher");

	QBrush brush(Qt::VerPattern);
	brush.setTextureImage(QImage("://background.jpg"));
	QPalette curPalette = palette();
	curPalette.setBrush(QPalette::Background, brush);
	setPalette(curPalette);

	initMenuBar();

	showInputDialog();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuBar()
{
	QAction *actionNew_matrix = new QAction("New matrix", this);
	QAction *actionCapClipboard = new QAction("From clipboard", this);
	QAction *actionExit = new QAction("Exit", this);

	QMenu *menuFile = this->menuBar()->addMenu(tr("&File"));

	menuFile->addAction(actionNew_matrix);
	menuFile->addAction(actionCapClipboard);
	menuFile->addSeparator();
	menuFile->addAction(actionExit);

	connect(actionNew_matrix, SIGNAL(triggered()), this, SLOT(showInputDialog()));
	connect(actionCapClipboard, SIGNAL(triggered()), this, SLOT(setupFromClipboard()));
	connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MatrixViewer *MainWindow::createMatrixPage(QPoint const &matrixSize)
{
	MatrixViewer *matrixPage = new MatrixViewer(this, matrixSize);
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
	if (dynamic_cast<InputDialog *>(centralWidget()) != NULL) {
		return;
	}
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

void MainWindow::setupFromClipboard()
{
	ClipboardObserver observer;
	observer.update();
	if (!observer.isValidMatrix()) {
		return;
	}

	MatrixViewer *viewer = createMatrixPage(observer.matrixSize());
	viewer->loadFromList(observer.elements());

	setCentralWidget(viewer);
}


