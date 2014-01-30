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
** This dialog contains loading *.dat and *.prn
** Only when the TWO files are successfully loaded,
** the information of the micro circulation is loaded
**
****************************************************************************/

#ifndef LOADFILEDLG_H
#define LOADFILEDLG_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QTextStream;
class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;
class QTabWidget;
class LoadAttrWidget;

class LoadFileDlg : public QDialog
{
	Q_OBJECT

public:
	LoadFileDlg(QWidget *parent = 0);
	~LoadFileDlg();

private slots:
	void loadData();

private:
	void createLoadFileBox();

	void loadAttributes();
	void loadTopology();

	QString datFileName;
	QString prnFileName;
	QString picFileName;
	QString topolFileName;
	QString optFileName;

	QTabWidget *dlgTabWidget;
	LoadAttrWidget *attrWidget;
	QGroupBox *buttonBox;
	QPushButton *okButton;
	QPushButton *cancelButton;
	QHBoxLayout *buttonLayout;
	QVBoxLayout *dlgLayout;
};

#endif
