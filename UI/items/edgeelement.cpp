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

#include "edgeelement.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <math.h>
#include "base_item/nodeitem.h"
#include "base_item/itemproperty.h"

EdgeElement::EdgeElement(NodeItem *sourceNode, NodeItem *destNode)
:	EdgeItem(sourceNode, destNode, NULL),
	source(sourceNode),
	dest(destNode)
{
	setZValue(ItemProperty::EdgeElement);
}

QRectF EdgeElement::boundingRect() const
{
	if (!source || !dest)
		return QRectF();

	qreal penWidth = 1;

	return QRectF(sourcePoint, QSize(destPoint.x() - sourcePoint.x(),
		destPoint.y() - sourcePoint.y()))
		.normalized();
}

/*!
	Custom rendering of the item
	Each subclass of EdgeItem has its own implementation 
*/
void EdgeElement::paint(QPainter *painter, 
						 const QStyleOptionGraphicsItem *option, 
						 QWidget *)
{
	// painter->setClipRect(option->exposedRect);

	if (!source || !dest)
		return;

	QLineF line(sourcePoint, destPoint);

	// show the width of the edgeItem with respect to the OLDDIAM
	qreal showDiameter = 1;

	painter->setPen(QPen(Qt::black, showDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawLine(line);
}

/*!
	\brief	The shape is IMPORTANT!

	If the shape is not reimplemented, the default shape 
	is the same as the boundingRect. 
	This could lead problems in collision detection and
	behavior of some functions such as itemAt(QPointF &point)
*/
QPainterPath EdgeElement::shape() const
{
	QPainterPath path;
	QPolygonF polygon;
	qreal shapeWidth;
	qreal shapeHeight;
	qreal x1 = source->scenePos().x();
	qreal x2 = dest->scenePos().x();
	qreal y1 = source->scenePos().y();
	qreal y2 = dest->scenePos().y();

	// deal with different directions of the line
	// TODO(panqing): it should be better but I don't know how to
	if ((y1-y2)*(x1-x2) <= 0)
	{
		shapeWidth = 6;
		shapeHeight = 6;
	}
	else
	{
		shapeWidth = -6;
		shapeHeight = 6;
	}

	QPointF point1(line.p1() - QPointF(shapeWidth,shapeHeight));
	QPointF point2(line.p1() + QPointF(shapeWidth,shapeHeight));
	QPointF point3(line.p2() + QPointF(shapeWidth,shapeHeight));
	QPointF point4(line.p2() - QPointF(shapeWidth,shapeHeight));

	polygon << point1 << point2 << point3 << point4; 
	path.addPolygon(polygon);
	return path;
}
