#include "matrixViewer.h"

MatrixViewer::MatrixViewer(QWidget *parent, QPoint const &matrixSize)
	: QWidget(parent)
{
	createGUI();

	mMatrixSize = matrixSize;

	setupMatrix();
}

MatrixViewer::~MatrixViewer()
{
	delete mMatrixLayout;
}

void MatrixViewer::createGUI()
{
	mMainLayout = new QVBoxLayout(this);
	mMatrixLayout = new QGridLayout();
	mMainLayout->addLayout(mMatrixLayout);

	setLayout(mMainLayout);

	mStartButton = new QPushButton(tr("Launch"), this);
	mMainLayout->addWidget(mStartButton);
	connect(mStartButton, SIGNAL(clicked()), this, SLOT(startDeligation()));
	mStartButton->hide();
}

void MatrixViewer::setupMatrix()
{
	for (int y = 0; y < mMatrixSize.y(); y++)
		for (int x = 0; x < mMatrixSize.x(); x++) {
			QLineEdit *newLine = new QLineEdit(this);
			mLinesList << newLine;
			mMatrixLayout->addWidget(newLine, y, x);
		}

	for (int i = 0; i < mLinesList.size(); i++) {
		if (i < mLinesList.size() - 1) {
			connect(mLinesList.at(i), SIGNAL(returnPressed()), mLinesList.at(i + 1), SLOT(setFocus()));
		} else {
			connect(mLinesList.at(i), SIGNAL(returnPressed()), mStartButton, SLOT(click()));
		}
	}

	mStartButton->show();
	if (mMatrixSize.x() + mMatrixSize.y() == 0) {
		mStartButton->setEnabled(false);
	} else {
		mStartButton->setEnabled(true);
	}
}

void MatrixViewer::startDeligation()
{
	fillZeros();
	QString fullQuery = "http://m.wolframalpha.com/input/?i=" + makeUrlQuery();

	QDesktopServices::openUrl(QUrl(fullQuery));
}

QString MatrixViewer::makeUrlQuery()
{
	QString result;
	result += "{";
	for (int y = 0; y < mMatrixSize.y(); y++) {
		result += "{";
		for (int x = 0; x < mMatrixSize.x(); x++) {
			QString curWord = mLinesList.at(y * mMatrixSize.x() + x)->text();
			result += ((x == 0)? curWord : QString(", " + curWord));
		}
		result += "}";
		if (y < mMatrixSize.y() - 1) {
			result += ",";
		}
	}
	result += "}";

	return result;
}

void MatrixViewer::fillZeros()
{
	foreach (QLineEdit *edit, mLinesList) {
		if (edit->text().isEmpty()) {
			edit->setText("0");
		}
	}
}
