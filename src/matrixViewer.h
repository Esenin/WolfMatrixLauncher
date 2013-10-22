#pragma once

#include <QUrl>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QDesktopServices>

//! @class MatrixViewer Model-View part, builds url
class MatrixViewer : public QWidget
{
	Q_OBJECT
public:
	MatrixViewer(QWidget *parent, QPoint const &matrixSize);

	//! writes elements in forward order to new matrix
	void loadFromList(QStringList const elementsList);
	~MatrixViewer();

protected:
	void createGUI();
	void createDigitEmulatorBox();
	void createPowerBox();
	void createStartButton();
	void createClearButton();
	void fillZeros();
	void setupMatrix();
	QString makeUrlQuery();
	//! @returns url-request addition for non-trivially matrix-power
	QString powerOfMatrix() const;

protected slots:
	//! opens matrix on site
	void startDeligation();
	void emulatorCheckBoxChanged(bool newValue);
	void keypadEmulatorFilter(QString const &newValue);
	void clearCells();

private:
	QVBoxLayout *mMainLayout;
	QGridLayout *mMatrixLayout;
	QLineEdit *mMatrixPowerLine;
	QPushButton *mStartButton;
	bool isEmulatorWorking;
	QPoint mMatrixSize;
	QList<QLineEdit *> mLinesList;
};

