#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>

//! @class InputDialog custom dialog window for right displaying on mobile devices
class InputDialog : public QWidget
{
	Q_OBJECT
public:
	explicit InputDialog(QWidget *parent = 0);

signals:
	void buttonPushed();

public slots:
	QString getInputText();

private:
	QLineEdit *mLineEdit;

private slots:
	void btnOkClicked();
};

