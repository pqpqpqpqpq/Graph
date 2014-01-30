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

#ifndef LOADATTRWIDGET_H
#define LOADATTRWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;

class LoadAttrWidget : public QWidget
{
	Q_OBJECT

public:
	LoadAttrWidget(QWidget *parent = 0);
	~LoadAttrWidget();

	QString getDatFileName() { return datFileName; }
	QString getPrnFileName() { return prnFileName; }
	QString getTopolFileName() { return topolFileName; }
	QString getOptFileName() { return optFileName; }

private slots:
	void openDatFile();
	void openPrnFile();
	void openTopolFile();
	void openOptFile();

	void enableOkButton();

private:
	void createWidget();

	QString datFileName;
	QString prnFileName;
	QString topolFileName;
	QString optFileName;

	QGroupBox *datFileBox;
	QGroupBox *prnFileBox;
	QGroupBox *topolFileBox;
	QGroupBox *optFileBox;
	QLineEdit *datLineEdit;
	QLineEdit *prnLineEdit;
	QLineEdit *topolLineEdit;
	QLineEdit *optLineEdit;
	QPushButton *datFileButton;
	QPushButton *prnFileButton;
	QPushButton *topolButton;
	QPushButton *optButton;
	QHBoxLayout *datFileLayout;
	QHBoxLayout *prnFileLayout;
	QHBoxLayout *topolLayout;
	QHBoxLayout *optLayout;
	QVBoxLayout *dlgLayout;

signals:
	void buttonOK(bool);
};
#endif
