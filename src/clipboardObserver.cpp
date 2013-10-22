#include "clipboardObserver.h"

void ClipboardObserver::update()
{
	mInput = cleanOutInput(clipboardData());
}

bool ClipboardObserver::isValidMatrix() const
{
	return isValidSequence(mInput);
}

QPoint ClipboardObserver::matrixSize() const
{
	int const firstOpen = mInput.indexOf("{");
	int const firstClose = mInput.indexOf("}");

	QPoint result(0,0);
	result.setX(mInput.mid(firstOpen, firstClose - firstOpen + 1).count(",") + 1);
	result.setY(mInput.count(",") / result.x() + 1);
	return result;
}

QStringList ClipboardObserver::elements() const
{
	QString text = mInput;
	text.replace("{", "");
	text.replace("}", "");
	QStringList result = text.split(",", QString::SkipEmptyParts);
	return result;
}

QString ClipboardObserver::clipboardData() const
{
	return QApplication::clipboard()->text();
}

QString ClipboardObserver::cleanOutInput(QString text) const
{
	text = text.simplified();
	text.replace(" ", "");

	int first = text.indexOf('{');
	int last = text.lastIndexOf('}');
	return text.mid(first, last - first + 1);
}

bool ClipboardObserver::isValidSequence(QString const line) const
{
	bool hasBrackets = false;
	int openBracketsCount = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) == '{') {
			openBracketsCount++;
			hasBrackets = true;
		} else if (line.at(i) == '}') {
			openBracketsCount--;
		}

		if (openBracketsCount < 0) {
			return false;
		}
	}

	return hasBrackets && openBracketsCount == 0;
}
