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

#include "mainnodeitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "base_item/edgeitem.h"
#include "data/edgeattr.h"
#include "ui/scenes/topographicscene.h"
#include "base_item/itemproperty.h"

MainNodeItem::MainNodeItem(TopoGraphicsView *topoGraphicsView, quint32 nodeIndex)
:	NodeItem(topoGraphicsView),
	nodeIndex(nodeIndex),
  startIndicator(false),
  findedNodeIndicator(false)
{
	setZValue(ItemProperty::MainNodeItem);
}

void MainNodeItem::paint(QPainter *painter, 
						 const QStyleOptionGraphicsItem *option, 
						 QWidget *)
{
	// painter->setClipRect(option->exposedRect);
  
  if(startIndicator)
  {
    painter->setPen(Qt::gray);
    painter->setBrush(QBrush(Qt::gray));
  }
  else
  {
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::transparent);
  }

  if(findedNodeIndicator)
  {
    painter->setPen(Qt::green);
    painter->setBrush(QBrush(Qt::green));
  }

	painter->drawEllipse(-radius, -radius, diameter, diameter);
}