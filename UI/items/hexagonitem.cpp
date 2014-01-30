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

#include "hexagonitem.h"

#include <QPainter>
#include <QPolygonF>
#include <QStyleOptionGraphicsItem>
#include <math.h>
#include "base_item/itemproperty.h"
#include "main/resmanager.h"

HexagonItem::HexagonItem(QGraphicsItem *parent)
	: QGraphicsPolygonItem(parent),
	  edgeWidth(1)
{
	initSettings();
	createHexagon();
	setZValue(ItemProperty::HexagonItem);
}

HexagonItem::HexagonItem(const QPolygonF &polygon, QGraphicsItem *parent)
	: QGraphicsPolygonItem(parent),
	  edgeWidth(1)
{
	setPolygon(polygon);
	createHexagon();
	setZValue(3);
}

/*!
	\brief Custom rendering of the item
*/
void HexagonItem::paint(QPainter *painter, 
		   const QStyleOptionGraphicsItem *option, 
		   QWidget *widget)
{
	painter->setClipRect(option->exposedRect);
	painter->setPen(QPen(Qt::white, edgeWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	// set the pen for drawing the outline of the item
	painter->drawPolygon(this->polygon());
}

/*!
	\brief Create the hexagon by setting a QPolygonF
*/
void HexagonItem::createHexagon()
{
	QPolygonF hexagonPolygon;
	hexagonPolygon << QPointF(-HEXAGON_EDGE_ITEM, 0.0) << QPointF(-HEXAGON_EDGE_ITEM/2, HEXAGON_EDGE_ITEM/2*sqrt(3.0))
					<< QPointF(HEXAGON_EDGE_ITEM/2, HEXAGON_EDGE_ITEM/2*sqrt(3.0)) << QPointF(HEXAGON_EDGE_ITEM, 0.0)
					<< QPointF(HEXAGON_EDGE_ITEM/2, -HEXAGON_EDGE_ITEM/2*sqrt(3.0)) << QPointF(-HEXAGON_EDGE_ITEM/2, -HEXAGON_EDGE_ITEM/2*sqrt(3.0));
	setPolygon(hexagonPolygon);
}

/*!
	\brief Initialization from QSettings
*/
void HexagonItem::initSettings()
{
	HEXAGON_EDGE_ITEM = ResManager::settings.value("SceneSize/element_edge_length").toDouble();
}
