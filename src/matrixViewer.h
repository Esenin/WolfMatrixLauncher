#pragma once

#include <QUrl>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDesktopServices>

class MatrixViewer : public QWidget
{
	Q_OBJECT
public:
	explicit MatrixViewer(QWidget *parent, QPoint const &matrixSize);
	~MatrixViewer();

protected:
	void createGUI();
	void fillZeros();
	void setupMatrix();
	QString makeUrlQuery();

protected slots:
	void startDeligation();

private:
	QVBoxLayout *mMainLayout;
	QGridLayout *mMatrixLayout;
	QPushButton *mStartButton;
	QPoint mMatrixSize;
	QList<QLineEdit *> mLinesList;
};

