#pragma once

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>

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

