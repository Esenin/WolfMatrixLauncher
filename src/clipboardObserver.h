#pragma once

#include <QApplication>
#include <QClipboard>
#include <QStringList>

//! @class ClipboardObserver checks buffer for saved wf-styled matrix
class ClipboardObserver
{
public:
	//! checks buffer
	void update();
	//! always validate data before usage
	bool isValidMatrix() const;
	//! columns x rows
	QPoint matrixSize() const;
	//! all matrix elements in forward order
	QStringList elements() const;

protected:
	QString clipboardData() const;
	QString cleanOutInput(QString text) const;
	bool isValidSequence(QString const line) const;

	QString mInput;
};
