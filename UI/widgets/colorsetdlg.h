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

#ifndef COLORSETDLG_H
#define COLORSETDLG_H

#include <QDialog>

class QPushButton;
class QColorDialog;
class QButtonGroup;

class ColorSetDlg : public QDialog
{
  Q_OBJECT

public:
  ColorSetDlg(QWidget *parent = 0);
  ~ColorSetDlg();

private slots:
  void okClicked();
  void setBackColor(const QColor &color);

private:
  void createColorSetDlg();

  QButtonGroup *btnGroup;
  QPushButton *backColorBtn;
  QPushButton *okButton;
  QPushButton *cancelButton;
  QColorDialog *colorDlg;
};

#endif
