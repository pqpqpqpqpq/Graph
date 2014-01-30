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

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QColorDialog>
#include <QGroupBox>
#include <QCheckBox>
#include <QButtonGroup>

#include "colorsetdlg.h"
#include "main/resmanager.h"

ColorSetDlg::ColorSetDlg(QWidget *parent)
: QDialog(parent)
{
  createColorSetDlg();

}

ColorSetDlg::~ColorSetDlg()
{

}

void ColorSetDlg::okClicked()
{
  ResManager::vesColorMode = btnGroup->checkedId();
  ResManager::settings.setValue("Color/Vessel Color Mode",ResManager::vesColorMode);
  accept();
}

/*!
  \brief Set the background color
*/
void ColorSetDlg::setBackColor(const QColor &color)
{
  ResManager::backColor = color;
  QPalette pa;
  pa.setColor(QPalette::Button, color);
  backColorBtn->setPalette(pa);
  ResManager::settings.setValue("Color/Background Color", color);
}

/*!
  \brief Init the widget
*/
void ColorSetDlg::createColorSetDlg()
{
  QGroupBox *groupBox1 = new QGroupBox(tr("Background Color"), this);
  QLabel *backColorLbl = new QLabel(tr("Background Color"), groupBox1);
  backColorBtn = new QPushButton(groupBox1);
  backColorBtn->setFlat(true);
  backColorBtn->setAutoFillBackground(true);
  QPalette pa;
  pa.setColor(QPalette::Button, ResManager::backColor);
  backColorBtn->setPalette(pa);
  
  QGroupBox *groupBox2 = new QGroupBox(tr("Vessel Color Mode"), this);
  btnGroup = new QButtonGroup(this);
  btnGroup->setExclusive(true);
  QCheckBox *chkBox1 = new QCheckBox(tr("Vessel Type"), groupBox2);
  QCheckBox *chkBox2 = new QCheckBox(tr("Monochrome"), groupBox2);
  QCheckBox *chkBox3 = new QCheckBox(tr("Highlight Typical Pathway"), groupBox2);
  QCheckBox *chkBox4 = new QCheckBox(tr("Parameter Distribution"), groupBox2);
  btnGroup->addButton(chkBox1, 0);
  btnGroup->addButton(chkBox2, 1);
  btnGroup->addButton(chkBox3, 2);
  btnGroup->addButton(chkBox4, 3);
  btnGroup->button(ResManager::vesColorMode)->setChecked(true);

  colorDlg = new QColorDialog(this);
  connect(backColorBtn, SIGNAL(clicked()), colorDlg, SLOT(exec()));
  connect(colorDlg, SIGNAL(colorSelected(const QColor &)), this, SLOT(setBackColor(const QColor &)));
  
  okButton = new QPushButton(tr("OK"), this);
  cancelButton = new QPushButton(tr("Cancel"), this);
  connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

  QHBoxLayout *grp1Layout = new QHBoxLayout(groupBox1);
  grp1Layout->addWidget(backColorLbl);
  grp1Layout->addWidget(backColorBtn);
  QVBoxLayout *grp2Layout = new QVBoxLayout(groupBox2);
  grp2Layout->addWidget(chkBox1);
  grp2Layout->addWidget(chkBox2);
  grp2Layout->addWidget(chkBox3);
  grp2Layout->addWidget(chkBox4);
  QGridLayout *mainLayout = new QGridLayout(this);
  mainLayout->addWidget(groupBox1,0,0,2,2);
  mainLayout->addWidget(groupBox2,2,0,4,2);
  mainLayout->addWidget(okButton,6,0,1,1);
  mainLayout->addWidget(cancelButton,6,1,1,1);
}
