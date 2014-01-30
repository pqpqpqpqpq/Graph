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
** This class provides a dialog for searching Nodes and Segments
** according to the number
**
****************************************************************************/

#ifndef SEARCHDLG_H
#define SEARCHDLG_H

#include <QDialog>

#include "main/itemcontainer.h"

class QGroupBox;
class QGridLayout;
class QVBoxLayout;
class QLineEdit;
class QPushButton;
class QLabel;

class SearchDlg : public QDialog
{
	Q_OBJECT

public:
	SearchDlg(QWidget *parent = 0);
	~SearchDlg();

private:
	void createSearchBox();

	QGroupBox *searchBox;
	QGridLayout *searchBoxLayout;
	QVBoxLayout *mainLayout;
  QLabel *segNoLbl;
  QLabel *nodeNoLbl;
	QLineEdit *segNoEdit;
	QLineEdit *nodeNoEdit;
	QPushButton *segSearchBtn;
	QPushButton *nodeSearchBtn;

private slots:
	void segSearch();
	void nodeSearch();
};

#endif
