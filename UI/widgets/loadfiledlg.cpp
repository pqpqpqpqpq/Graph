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

#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTabWidget>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QPixmap>
#include <QDir>

#include "loadfiledlg.h"
#include "loadattrwidget.h"
#include "main/resmanager.h"
#include "data/edgeattr.h"
#include "data/dataio.h"

LoadFileDlg::LoadFileDlg(QWidget *parent)
	:QDialog(parent)
{
	const int dlgWidth = 480;	// width of the load file dialog
	const int dlgHeight = 240;	// height of the load file dialog
	setGeometry(parent->width()*0.5-dlgWidth/2, parent->height()*0.5-dlgHeight/2, dlgWidth, dlgHeight);
	createLoadFileBox();
}

// TODO(panqing): The child object will be deleted automatically when the parent object is deleted
LoadFileDlg::~LoadFileDlg()
{
	delete dlgTabWidget;
	delete buttonBox;
	delete dlgLayout;
}

/*!
	Construct the UI of the load file box
*/
void LoadFileDlg::createLoadFileBox()
{
	dlgTabWidget = new QTabWidget(this);
	attrWidget = new LoadAttrWidget(dlgTabWidget);
	dlgTabWidget->addTab(attrWidget, tr("Attributes"));

	buttonBox = new QGroupBox(this);
	okButton = new QPushButton(tr("OK"), buttonBox);
	okButton->setDisabled(true);
	cancelButton = new QPushButton(tr("Cancel"), buttonBox);
	buttonLayout = new QHBoxLayout(buttonBox);
	buttonLayout->addStretch(3);
	buttonLayout->addWidget(okButton,5);
	buttonLayout->addStretch(3);
	buttonLayout->addWidget(cancelButton,5);
	buttonLayout->addStretch(3);
	connect(attrWidget, SIGNAL(buttonOK(bool)), okButton, SLOT(setDisabled(bool)));
	connect(okButton, SIGNAL(clicked()), this, SLOT(loadData()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	dlgLayout = new QVBoxLayout(this);
	dlgLayout->addWidget(dlgTabWidget);
	dlgLayout->addWidget(buttonBox);
}

/*!
	Read data from files
	The type of loaded data depends on the currentIndex of the tabWidget
*/
void LoadFileDlg::loadData()
{
	switch(dlgTabWidget->currentIndex())
	{
	// The index starts with 0
	case 0:
		loadAttributes();
		break;
	default:
	    break;
	}
}

/*!
	Read data information from files
	The dat and prn files are necessary
	The opt and topol files are optional
	The header and the end of the file are neglected
	TODO(panqing):This function is too long
*/
void LoadFileDlg::loadAttributes()
{
	bool picEditEmpty;
	if (attrWidget != NULL)
	{
		datFileName = attrWidget->getDatFileName();
		prnFileName = attrWidget->getPrnFileName();
		topolFileName = attrWidget->getTopolFileName();
		optFileName = attrWidget->getOptFileName();
	}
	else
	{
		// TODO(panqing): error processing
		return;
	}

	// load .dat data
	QFile datFile(datFileName);
	if (!datFile.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(datFileName)
			.arg(datFile.errorString()));
		return;
	}

	QTextStream in(&datFile);
	if (DataIO::loadDatData(in) != 0)
	{
		QMessageBox::critical(this, tr("Error"), tr("Load .dat file failed!"));
		DataIO::unloadData();
		return;
	}

	// load .prn data
	if (!prnFileName.isEmpty())
	{
		QFile prnFile(prnFileName);
		if (!prnFile.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Application"),
				tr("Cannot read file %1:\n%2.")
				.arg(prnFileName)
				.arg(prnFile.errorString()));
			return;
		}

		in.flush();
		in.setDevice(&prnFile);
		int loadFlag = DataIO::loadPrnData(in);
		if (loadFlag == -1)
		{
			QMessageBox::critical(this, tr("Error"), tr("The .dat and .prn files are not matching! Please reload!"));
			DataIO::unloadData();
			return;
		}
		else if (loadFlag != 0)
		{
			QMessageBox::critical(this, tr("Error"), tr("Load .prn file failed!"));
			DataIO::unloadData();
			return;
		}
	}

	if (!topolFileName.isEmpty())
	{
		if (!topolFileName.contains(tr("topol")))
		{
			QMessageBox::critical(this, tr("Application"),
				tr("File Name error"));
			return;
		}

		// load topol data
		QFile topolFile(topolFileName);
		if (!topolFile.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Application"),
				tr("Cannot read file %1:\n%2.")
				.arg(topolFileName)
				.arg(topolFile.errorString()));
			return;
		}

		QTextStream in(&topolFile);
		if (DataIO::loadTopolData(in) != 0)
		{
			QMessageBox::critical(this, tr("Error"), tr("Load topol file failed!"));
			DataIO::unloadData();
			return;
		}
		accept();
	}
	else if (!optFileName.isEmpty())
	{
		if (!optFileName.contains(tr("opt")))
		{
			QMessageBox::critical(this, tr("Application"),
				tr("File Name error"));
			return;
		}

		// load opt data
		QFile optFile(optFileName);
		if (!optFile.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Application"),
				tr("Cannot read file %1:\n%2.")
				.arg(optFileName)
				.arg(optFile.errorString()));
			return;
		}

		QTextStream in(&optFile);
		if (DataIO::loadOptData(in) != 0)
		{
			QMessageBox::critical(this, tr("Error"), tr("Load opt file failed!"));
			DataIO::unloadData();
			return;
		}
	}
	accept();
}
