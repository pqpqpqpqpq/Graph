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
#include <QDebug>
#include <QLabel>

#include "searchdlg.h"
#include "data/edgeattr.h"
#include "UI/items/base_item/nodeitem.h"
#include "data/itemfactory.h"
#include "topographicsview.h"
#include "ui/items/base_item/edgeitem.h"
#include "ui/items/subedgeitem.h"
#include "ui/items/mainnodeitem.h"

SearchDlg::SearchDlg(QWidget *parent)
: QDialog(parent)
{
	const int dlgWidth = 120;	// width of the load file dialog
	const int dlgHeight = 90;	// height of the load file dialog
	setGeometry(parent->width()*0.5-dlgWidth/2, parent->height()*0.5-dlgHeight/2, dlgWidth, dlgHeight);
	setSizeGripEnabled(true);

	createSearchBox();
}

SearchDlg::~SearchDlg()
{

}

void SearchDlg::createSearchBox()
{
	searchBox = new QGroupBox(this);
  segNoLbl = new QLabel(tr("Segment Number"),searchBox);
	segNoEdit = new QLineEdit(searchBox);
	segNoEdit->setFixedWidth(80);
  nodeNoLbl = new QLabel(tr("Node Number"),searchBox);
	nodeNoEdit = new QLineEdit(searchBox);
	nodeNoEdit->setFixedWidth(80);
	searchBoxLayout = new QGridLayout(searchBox);
	segSearchBtn = new QPushButton(tr("Search"), searchBox);
	nodeSearchBtn = new QPushButton(tr("Search"), searchBox);
	connect(segSearchBtn, SIGNAL(clicked()), this, SLOT(segSearch()));
	connect(nodeSearchBtn, SIGNAL(clicked()), this, SLOT(nodeSearch()));

  searchBoxLayout->addWidget(segNoLbl, 0, 0);
	searchBoxLayout->addWidget(segNoEdit, 0, 1);
	searchBoxLayout->addWidget(segSearchBtn, 0, 4);
  searchBoxLayout->addWidget(nodeNoLbl, 1, 0);
	searchBoxLayout->addWidget(nodeNoEdit, 1, 1);
	searchBoxLayout->addWidget(nodeSearchBtn, 1, 4);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(searchBox);
}

void SearchDlg::segSearch()
{
  QList<EdgeItem *> &edgeItemList = ItemContainer::edgeItemList;
  QList<EdgeItem *>::const_iterator edgeItemListIt;

  for (edgeItemListIt = edgeItemList.constBegin();
    edgeItemListIt != edgeItemList.constEnd();
    ++ edgeItemListIt)
  {
    SubEdgeItem *subEdgeItem = qgraphicsitem_cast<SubEdgeItem *>(*edgeItemListIt);
    subEdgeItem->setFindedSegIndicator(false);
    EdgeAttr *edgeAttr = (*edgeItemListIt)->getEdgeAttr();
    if (segNoEdit->text().toInt()==edgeAttr->getIntAttr(EdgeAttr::SEGNAME))
      subEdgeItem->setFindedSegIndicator(true);
  }

	segNoEdit->clear();
	accept();
}

void SearchDlg::nodeSearch()
{
  QHash<quint32, NodeItem *> &nodeHash = ItemContainer::nodeHash;
  QHash<quint32, NodeItem *>::const_iterator nodeHashIt = nodeHash.constBegin();
  // First, clear the last search results
  while (nodeHashIt != nodeHash.constEnd())
  {
    NodeItem *tmpNodeItem = nodeHashIt.value();
    if (MainNodeItem *mainNodeItem = qgraphicsitem_cast<MainNodeItem *>(tmpNodeItem))
      mainNodeItem->setFindedNodeIndicator(false);
    ++nodeHashIt;
  }
  NodeItem *findedNodeItem = nodeHash.value(nodeNoEdit->text().toInt());
  if (MainNodeItem *mainNodeItem = qgraphicsitem_cast<MainNodeItem *>(findedNodeItem))
    mainNodeItem->setFindedNodeIndicator(true);

  segNoEdit->clear();
  accept();
}
