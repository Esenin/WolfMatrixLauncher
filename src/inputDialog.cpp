#include "inputDialog.h"

InputDialog::InputDialog(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	setLayout(mainLayout);

	QLabel *label = new QLabel("Input matrix dim: \n(e.g. \"2*3\" or just \"3\" for 3*3 matrix)", this);
	mainLayout->addWidget(label);

	mLineEdit = new QLineEdit(this);
	mainLayout->addWidget(mLineEdit);
	connect(mLineEdit, SIGNAL(returnPressed()), this, SLOT(btnOkClicked()));

	QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Expanding);
	mainLayout->addSpacerItem(spacer);

	QPushButton *okButton = new QPushButton("Ok!", this);
	mainLayout->addWidget(okButton);
	connect(okButton, SIGNAL(clicked()), this, SLOT(btnOkClicked()));
}

QString InputDialog::getInputText()
{
	return mLineEdit->text();
}

void InputDialog::btnOkClicked()
{
	emit buttonPushed();
}


