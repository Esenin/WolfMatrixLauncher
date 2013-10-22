#pragma once

#include <QApplication>
#include <QClipboard>
#include <QStringList>

class ClipboardObserver
{
public:
	void update();
	bool isValidMatrix() const;
	QPoint matrixSize() const;
	QStringList elements() const;

protected:
	QString clipboardData() const;
	QString cleanOutInput(QString text) const;
	bool isValidSequence(QString const line) const;

	QString mInput;

};
