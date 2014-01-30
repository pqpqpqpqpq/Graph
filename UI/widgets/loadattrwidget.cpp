/****************************************************************************
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** Author: panqing
** email: zjupanqing@gmail.com
**
****************************************************************************/

#include "loadattrwidget.h"

#include <QGroupBox>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QFileDialog>

LoadAttrWidget::LoadAttrWidget(QWidget *parent)
:	QWidget(parent)
{
	createWidget();
}

LoadAttrWidget::~LoadAttrWidget()
{
	delete datFileBox;
	delete prnFileBox;
	delete dlgLayout;
}

void LoadAttrWidget::createWidget()
{
	datFileBox = new QGroupBox(tr("Load *.dat File"), this);
	datLineEdit = new QLineEdit(datFileBox);
	datLineEdit->setReadOnly(true);	// set the lineedit READ_ONLY
	datFileButton = new QPushButton(tr("..."), datFileBox);
	datFileLayout = new QHBoxLayout(datFileBox);
	datFileLayout->addWidget(datLineEdit);
	datFileLayout->addWidget(datFileButton);
	connect(datFileButton, SIGNAL(clicked()), this, SLOT(openDatFile()));
	connect(datLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableOkButton()));

	prnFileBox = new QGroupBox(tr("Load *.prn File"), this);
	prnLineEdit = new QLineEdit(prnFileBox);
	prnLineEdit->setReadOnly(true);	// set the lineedit READ_ONLY
	prnFileButton = new QPushButton(tr("..."), prnFileBox);
	prnFileLayout = new QHBoxLayout(prnFileBox);
	prnFileLayout->addWidget(prnLineEdit);
	prnFileLayout->addWidget(prnFileButton);
	connect(prnFileButton, SIGNAL(clicked()), this, SLOT(openPrnFile()));
	connect(prnLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableOkButton()));

	topolFileBox = new QGroupBox(tr("Load topol File"), this);
	topolLineEdit = new QLineEdit(topolFileBox);
	topolLineEdit->setReadOnly(true);	// set the lineedit READ_ONLY
	topolButton = new QPushButton(tr("..."), topolFileBox);
	topolLayout = new QHBoxLayout(topolFileBox);
	topolLayout->addWidget(topolLineEdit);
	topolLayout->addWidget(topolButton);
	connect(topolButton, SIGNAL(clicked()), this, SLOT(openTopolFile()));
	connect(topolLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableOkButton()));

	optFileBox = new QGroupBox(tr("Load opt File"), this);
	optLineEdit = new QLineEdit(optFileBox);
	optLineEdit->setReadOnly(true);	// set the lineedit READ_ONLY
	optButton = new QPushButton(tr("..."), optFileBox);
	optLayout = new QHBoxLayout(optFileBox);
	optLayout->addWidget(optLineEdit);
	optLayout->addWidget(optButton);
	connect(optButton, SIGNAL(clicked()), this, SLOT(openOptFile()));
	connect(optLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableOkButton()));

	dlgLayout = new QVBoxLayout(this);
	dlgLayout->addWidget(datFileBox);
	dlgLayout->addWidget(prnFileBox);
	dlgLayout->addWidget(topolFileBox);
	dlgLayout->addWidget(optFileBox);
}

void LoadAttrWidget::openDatFile()
{
	datFileName = QFileDialog::getOpenFileName(this, tr("Open .dat File"), QDir::currentPath(), tr("*.dat"));
	datLineEdit->setText(datFileName);
}

void LoadAttrWidget::openPrnFile()
{
	prnFileName = QFileDialog::getOpenFileName(this, tr("Open .prn File"), QDir::currentPath(), tr("*.prn"));
	prnLineEdit->setText(prnFileName);
}

void LoadAttrWidget::openTopolFile()
{
	topolFileName = QFileDialog::getOpenFileName(this, tr("Open topol File"), QDir::currentPath(), tr("*.txt"));
	topolLineEdit->setText(topolFileName);
}

void LoadAttrWidget::openOptFile()
{
	optFileName = QFileDialog::getOpenFileName(this, tr("Open opt File"), QDir::currentPath(), tr("*.txt"));
	optLineEdit->setText(optFileName);
}

/*!
	If both datLineEdit and prnLineEdit is not empty,
	the OkButton is enabled.
*/
void LoadAttrWidget::enableOkButton()
{
	if (!datLineEdit->text().isEmpty()
		&& !prnLineEdit->text().isEmpty())
		emit buttonOK(false);
	else
		emit buttonOK(false);
		//emit buttonOK(true);
}