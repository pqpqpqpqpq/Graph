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

#include "topographicscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QApplication>
#include <QMessageBox>
#include "ui/widgets/topographicsview.h"
#include "ui/items/base_item/edgeitem.h"
#include "ui/items/base_item/nodeitem.h"
#include "main/resmanager.h"
#include "ui/items/base_item/itemproperty.h"
#include "ui/items/mainnodeitem.h"
#include "main/itemcontainer.h"
#include "data/edgeattr.h"

TopoGraphicScene::TopoGraphicScene(QObject *parent)
:	QGraphicsScene(parent),
  nodeHash(ItemContainer::nodeHash)
{
	topoGraphicsView = NULL;
  startNode = NULL;
	// Determine the saved background
  setBackgroundBrush(ResManager::backColor);
}

TopoGraphicScene::~TopoGraphicScene()
{
	// Notice(panqing): the items should be deleted by the default deconstructor function
	// The implementation below is time-consuming because of the items() function (maybe)
	/*
	for (int i = 0; i < items().size(); i++)
		delete items().value(i);
	*/
}

/*!
	\brief Reimplementing the mousePressEvent to handle the display of HintItem
*/
void TopoGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
  if(startNode != NULL)
  {
    startNode->setStartIndicator(false);
    startNode->update();
  }
	// determine whether the mouse press event is happened on a QGraphicsItem
	QGraphicsItem *item = itemAt(mouseEvent->scenePos());
	// determine whether the mouse press is RightButton
	if (item != 0 && (mouseEvent->button() == Qt::RightButton))
	{
		// whether the type of the item is edgeItem
		if (EdgeItem *edgeItem = dynamic_cast<EdgeItem *>(item))
		{
      // Emit the edgeItem for showing its parameters
      emit rightClickOnSegment(edgeItem);
      // Indicate its start node
      startNode = qgraphicsitem_cast<MainNodeItem *>(nodeHash.value(edgeItem->getEdgeAttr()->getIntAttr(EdgeAttr::STARTNODE)));
      startNode->setStartIndicator(true);
      startNode->update();
		}
		else if (NodeItem *nodeItem = dynamic_cast<NodeItem *>(item))
		{
			// the action of MainNodeItem is implemented in MainNodeItem class
		}
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}
