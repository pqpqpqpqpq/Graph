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

#include "subnodeitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "base_item/itemproperty.h"

SubNodeItem::SubNodeItem(TopoGraphicsView *topoGraphicsView, quint32 nodeIndex)
:	NodeItem(topoGraphicsView),
	nodeIndex(nodeIndex),
	radius(getRadius()),
	diameter(2*getRadius())
{
	radius = radius/2;
	diameter = 2*radius;
	setZValue(ItemProperty::SubNodeItem);
}

void SubNodeItem::paint(QPainter *painter, 
						const QStyleOptionGraphicsItem *option, 
						QWidget *)
{
	painter->setClipRect(option->exposedRect);
	painter->setPen(Qt::NoPen);

	if (this->isSelected())
		painter->setBrush(QBrush(Qt::transparent, Qt::Dense6Pattern));
	else
		painter->setBrush(Qt::transparent);

	painter->drawEllipse(-radius, -radius, diameter, diameter);
}
