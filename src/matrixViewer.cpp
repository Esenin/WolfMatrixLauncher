#include "matrixViewer.h"

MatrixViewer::MatrixViewer(QWidget *parent, QPoint const &matrixSize)
	: QWidget(parent)
	, isEmulatorWorking(true)
{
	createGUI();

	mMatrixSize = matrixSize;

	setupMatrix();
}

void MatrixViewer::loadFromList(QStringList const elementsList)
{
	for (int i = 0; i < mLinesList.size(); i++) {
		mLinesList.at(i)->setText(elementsList.at(i));
	}
}

MatrixViewer::~MatrixViewer()
{
	delete mMatrixLayout;
}

void MatrixViewer::createPowerBox()
{
	QIntValidator *degreeValidator = new QIntValidator(this);
	mMatrixPowerLine = new QLineEdit(tr("1"), this);
	mMatrixPowerLine->setValidator(degreeValidator);
	connect(mMatrixPowerLine, SIGNAL(returnPressed()), this, SLOT(startDeligation()));

	QGroupBox *powerBox = new QGroupBox(tr("Matrix power:"), this);
	powerBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QVBoxLayout *boxLayout = new QVBoxLayout(powerBox);
	boxLayout->addWidget(mMatrixPowerLine);

	mMainLayout->addWidget(powerBox);
}

void MatrixViewer::createStartButton()
{
	mStartButton = new QPushButton(tr("Launch"), this);
	mMainLayout->addWidget(mStartButton);
	connect(mStartButton, SIGNAL(clicked()), this, SLOT(startDeligation()));
	mStartButton->hide();
}

void MatrixViewer::createGUI()
{
	mMainLayout = new QVBoxLayout(this);

	createDigitEmulatorBox();

	mMatrixLayout = new QGridLayout();
	mMainLayout->addLayout(mMatrixLayout);

	setLayout(mMainLayout);

	createPowerBox();
	createStartButton();
}

void MatrixViewer::createDigitEmulatorBox()
{
	QCheckBox *emulatorTumbler = new QCheckBox("Use emulator ('A' -> 2, 'D' -> 3 ... 'W' -> 9)", this);
	emulatorTumbler->setChecked(true);
	connect(emulatorTumbler, SIGNAL(toggled(bool)), this, SLOT(emulatorCheckBoxChanged(bool)));

	QGroupBox *emulatorBox = new QGroupBox(tr("Digit keypad emulator"), this);
	emulatorBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QVBoxLayout *boxLayout = new QVBoxLayout(emulatorBox);
	boxLayout->addWidget(emulatorTumbler);

	mMainLayout->addWidget(emulatorBox);
}

void MatrixViewer::setupMatrix()
{
	for (int y = 0; y < mMatrixSize.y(); y++)
		for (int x = 0; x < mMatrixSize.x(); x++) {
			QLineEdit *newLine = new QLineEdit(this);
			connect(newLine, SIGNAL(textEdited(QString)), this, SLOT(keypadEmulatorFilter(QString)));
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

void MatrixViewer::emulatorCheckBoxChanged(bool newValue)
{
	isEmulatorWorking = newValue;
}

void MatrixViewer::keypadEmulatorFilter(QString const &newValue)
{
	if (!isEmulatorWorking || newValue.isEmpty()) {
		return;
	}
	int const alphabeticShift = 2;


	QString sample("adgjmptw");
	QString input = newValue.toLower();
	if (sample.contains(input.at(input.size() - 1))) {
		input.append(QString::number(sample.indexOf(input.at(input.size() - 1)) + alphabeticShift));
		input.remove(input.size() - 2, 1);

		QLineEdit *curLine = dynamic_cast<QLineEdit *>(sender());
		curLine->setText(input);
	}
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

	result += powerOfMatrix();

	return result;
}

QString MatrixViewer::powerOfMatrix() const
{
	QString const line = mMatrixPowerLine->text().simplified();
	bool const empty = line.isEmpty() || line == "1";
	return (empty)? QString() : QString("^(" + line + ")");
}

void MatrixViewer::fillZeros()
{
	foreach (QLineEdit *edit, mLinesList) {
		if (edit->text().isEmpty()) {
			edit->setText("0");
		}
	}
}
