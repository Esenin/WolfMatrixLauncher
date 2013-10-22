#pragma once

#include <QUrl>
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QDesktopServices>

#include <QDebug>

class MatrixViewer : public QWidget
{
	Q_OBJECT
public:
	explicit MatrixViewer(QWidget *parent, QPoint const &matrixSize);
	void loadFromList(QStringList const elementsList);
	~MatrixViewer();

protected:
	void createGUI();
	void createDigitEmulatorBox();
	void createPowerBox();
	void createStartButton();
	void fillZeros();
	void setupMatrix();
	QString makeUrlQuery();
	QString powerOfMatrix() const;

protected slots:
	void startDeligation();
	void emulatorCheckBoxChanged(bool newValue);
	void keypadEmulatorFilter(QString const &newValue);

private:
	QVBoxLayout *mMainLayout;
	QGridLayout *mMatrixLayout;
	QLineEdit *mMatrixPowerLine;
	QPushButton *mStartButton;
	bool isEmulatorWorking;
	QPoint mMatrixSize;
	QList<QLineEdit *> mLinesList;
};

