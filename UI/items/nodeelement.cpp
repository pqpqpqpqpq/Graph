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

#include "nodeelement.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "base_item/edgeitem.h"
#include "ui/scenes/topographicscene.h"
#include "base_item/itemproperty.h"

NodeElement::NodeElement(TopoGraphicsView *topoGraphicsView)
:	NodeItem(topoGraphicsView),
	radius(getRadius()),
	diameter(2*getRadius())
{
	radius = radius/2;
	diameter = 2*radius;
	setZValue(ItemProperty::NodeElement);
}

/*!
	\brief Custom rendering of the item
*/
void NodeElement::paint(QPainter *painter, 
						const QStyleOptionGraphicsItem *option, 
						QWidget *)
{
	painter->setClipRect(option->exposedRect);
	painter->setPen(Qt::NoPen);

	if (this->isSelected())
		painter->setBrush(QBrush(Qt::white, Qt::Dense6Pattern));
	else
		painter->setBrush(Qt::white);

	painter->drawEllipse(-radius, -radius, diameter, diameter);
}
