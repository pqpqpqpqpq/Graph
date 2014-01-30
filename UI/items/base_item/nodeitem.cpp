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

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

#include "nodeitem.h"
#include "edgeitem.h"
#include "itemproperty.h"
#include "ui/items/nodeelement.h"
#include "ui/items/subnodeitem.h"
#include "ui/widgets/topographicsview.h"
#include "data/edgeattr.h"

NodeItem::NodeItem(TopoGraphicsView *topoGraphicsView)
:	graph(topoGraphicsView)
{
  // setFlag(ItemIsMovable);
  setFlag(ItemIsSelectable);
  // NOTICE(panqing): In the function itemChange(), GraphicsItemChange has many types
  // The types ItemPositionChange and ItemPositionHasChanged are enabled when this flag is set enabled
  // The flag is introduced in Qt4.6!! By default, ItemPositionChange is not accepted by Qt
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
  setZValue(ItemProperty::NodeItem);
}

/*!
\brief Add an EdgeItem to the NodeItem
The edgeList holds the edgeItems which connected to the nodeItem
*/
void NodeItem::addEdge(EdgeItem *edgeItem)
{
  edgeList << edgeItem;
  edgeItem->adjust();

  // Update the diameter info
  diameter=0;
  for (int i=0; i<edgeList.size(); ++i)
    diameter = diameter + edgeList[i]->getEdgeAttr()->getDoubleAttr(EdgeAttr::OLDDIAM);

  diameter = diameter/edgeList.size();
  radius = diameter/2;
}

QList<EdgeItem *> NodeItem::edges()
{
  return edgeList;
}

bool NodeItem::posAdvance()
{
  if (newPos == pos())
    return false;

  setPos(newPos);
  return true;
}

QRectF NodeItem::boundingRect() const
{
  // qreal adjust = 2;
  qreal adjust = 0;
  return QRect(-radius - adjust, -radius - adjust,
    diameter + adjust, diameter + adjust);
}

/*!
  The boundingRect is always rectangular but the shape is round here 
*/
QPainterPath NodeItem::shape() const
{
  QPainterPath path;
  path.addEllipse(-radius, -radius, diameter, diameter);
  return path;
}

/*!
\brief This virtual function is called by QGraphicsItem to notify custom items that some part of the item's state changes. 
By reimplementing this function, your can react to a change, and in some cases, (depending on change,) adjustments can be made.
*/
QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  switch (change)
  {
    // To accept ItemPositionChange, the flag QGraphicsItem::ItemSendsGeometryChanges HAS TO BE ENABLED
    // This attribute is introduced since Qt4.6
    case ItemPositionHasChanged:
    case ItemPositionChange:
      // Adjust the connected edges
      foreach (EdgeItem *edgeItem, edgeList)
      {
        edgeItem->adjust();
      }
      break;
    default:
      break;
  }

  return QGraphicsItem::itemChange(change, value);
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  update();
  QGraphicsItem::mousePressEvent(event);
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}
