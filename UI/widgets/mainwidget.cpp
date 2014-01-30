#include "mainwidget.h"
#include "topographicsview.h"
#include "ui/items/base_item/edgeitem.h"
#include "data/edgeattr.h"
#include "main/itemcontainer.h"
#include <QLayout>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QLineEdit>

MainWidget::MainWidget(QWidget *parent /* = 0 */)
: QWidget(parent)
{
  
}

MainWidget::~MainWidget()
{

}

void MainWidget::showSegmentInfo(EdgeItem *edgeItem)
{
  segNameEdit->setText(QString::number(edgeItem->getEdgeAttr()->getIntAttr(EdgeAttr::SEGNAME)));
  fromEdit->setText(QString::number(edgeItem->getEdgeAttr()->getIntAttr(EdgeAttr::STARTNODE)));
  toEdit->setText(QString::number(edgeItem->getEdgeAttr()->getIntAttr(EdgeAttr::ENDNODE)));
  lenEdit->setText(QString::number(edgeItem->getEdgeAttr()->getDoubleAttr(EdgeAttr::LENGTH)));
  diamEdit->setText(QString::number(edgeItem->getEdgeAttr()->getDoubleAttr(EdgeAttr::OLDDIAM)));
  viscEdit->setText(QString::number(edgeItem->getEdgeAttr()->getDoubleAttr(EdgeAttr::VISC)));
  pressEdit->setText(QString::number(edgeItem->getEdgeAttr()->getDoubleAttr(EdgeAttr::PR_MEAN)));
  flowEdit->setText(QString::number(edgeItem->getEdgeAttr()->getDoubleAttr(EdgeAttr::FLOW)));
  velEdit->setText(QString::number(edgeItem->getEdgeAttr()->getDoubleAttr(EdgeAttr::VEL)));

  // Find the SegID
  QList<EdgeAttr *> &edgeAttrList = ItemContainer::edgeAttrList;
  for (int i=0; i<edgeAttrList.size(); ++i)
  {
    if (edgeAttrList[i]->getIntAttr(EdgeAttr::SEGNAME)==edgeItem->getEdgeAttr()->getIntAttr(EdgeAttr::SEGNAME))
    {
      segIdEdit->setText(QString::number(i+1));
      break;
    }
  }
}

void MainWidget::createWidget()
{
  // Widgets
  graphicsView = new TopoGraphicsView(this);
  segNameLbl = new QLabel(tr("SegName"), this);
  segNameEdit = new QLineEdit(this);
  segNameEdit->setReadOnly(true);
  segIdLbl = new QLabel(tr("SegId"), this);
  segIdEdit = new QLineEdit(this);
  segIdEdit->setReadOnly(true);
  fromLbl = new QLabel(tr("From"), this);
  fromEdit = new QLineEdit(this);
  fromEdit->setReadOnly(true);
  toLbl = new QLabel(tr("To"), this);
  toEdit = new QLineEdit(this);
  toEdit->setReadOnly(true);
  diamLbl = new QLabel(tr("Diameter"), this);
  diamEdit = new QLineEdit(this);
  diamEdit->setReadOnly(true);
  lenLbl = new QLabel(tr("Length"), this);
  lenEdit = new QLineEdit(this);
  lenEdit->setReadOnly(true);
  viscLbl = new QLabel(tr("Visc"), this);
  viscEdit = new QLineEdit(this);
  viscEdit->setReadOnly(true);
  pressLbl = new QLabel(tr("Pressure"), this);
  pressEdit = new QLineEdit(this);
  pressEdit->setReadOnly(true);
  velLbl = new QLabel(tr("Velocity"), this);
  velEdit = new QLineEdit(this);
  velEdit->setReadOnly(true);
  flowLbl = new QLabel(tr("Flow Rate"), this);
  flowEdit = new QLineEdit(this);
  flowEdit->setReadOnly(true);

  // Palette & Font of QLabel
  QPalette pal;
  QFont ft;
  ft.setStyleHint(QFont::Helvetica);
  ft.setPointSize(12);
  ft.setBold(true);
  // ft.setCapitalization(QFont::AllUppercase);
  segNameLbl->setFont(ft);
  segIdLbl->setFont(ft);
  fromLbl->setFont(ft);
  toLbl->setFont(ft);
  diamLbl->setFont(ft);
  lenLbl->setFont(ft);
  viscLbl->setFont(ft);
  pressLbl->setFont(ft);
  velLbl->setFont(ft);
  flowLbl->setFont(ft);
  segNameEdit->setFont(ft);
  segIdEdit->setFont(ft);
  fromEdit->setFont(ft);
  toEdit->setFont(ft);
  diamEdit->setFont(ft);
  lenEdit->setFont(ft);
  viscEdit->setFont(ft);
  pressEdit->setFont(ft);
  velEdit->setFont(ft);
  flowEdit->setFont(ft);

  // Layout
  mainLayout = new QHBoxLayout(this);
  mainLayout->setContentsMargins(0,0,0,0);
  infoLayout = new QVBoxLayout;
  paraLayout = new QGridLayout;
  // paraLayout->setContentsMargins(5,0,0,0);
  paraLayout->addWidget(segNameLbl,0,0);
  paraLayout->addWidget(segNameEdit,1,0);
  paraLayout->addWidget(segIdLbl,0,1);
  paraLayout->addWidget(segIdEdit,1,1);
  paraLayout->addWidget(fromLbl,2,0);
  paraLayout->addWidget(fromEdit,3,0);
  paraLayout->addWidget(toLbl,2,1);
  paraLayout->addWidget(toEdit,3,1);
  paraLayout->addWidget(diamLbl,4,0);
  paraLayout->addWidget(diamEdit,5,0);
  paraLayout->addWidget(lenLbl,4,1);
  paraLayout->addWidget(lenEdit,5,1);
  paraLayout->addWidget(pressLbl,6,0);
  paraLayout->addWidget(pressEdit,7,0);
  paraLayout->addWidget(flowLbl,6,1);
  paraLayout->addWidget(flowEdit,7,1);
  paraLayout->addWidget(velLbl,8,0);
  paraLayout->addWidget(velEdit,9,0);
  paraLayout->addWidget(viscLbl,8,1);
  paraLayout->addWidget(viscEdit,9,1);
  mainLayout->addWidget(graphicsView,9);
  infoLayout->addLayout(paraLayout,6);
  infoLayout->addStretch(9);
  mainLayout->addLayout(infoLayout,2);

  graphicsView->addItems();
  connect(graphicsView, SIGNAL(rightClickOnSegment(EdgeItem *)), this, SLOT(showSegmentInfo(EdgeItem *)));
}
