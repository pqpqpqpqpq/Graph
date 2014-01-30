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

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#include "edgeitem.h"
#include "nodeitem.h"
#include "itemproperty.h"
#include "data/edgeattr.h"

EdgeItem::EdgeItem(NodeItem *sourceNode, NodeItem *destNode, EdgeAttr *edgeAttr)
:	source(sourceNode),
	dest(destNode),
  edgeAttr(edgeAttr)
{
  setAcceptedMouseButtons(Qt::RightButton);	// the edgeItem only accept RIGHT mouse button click
  source->addEdge(this);
  dest->addEdge(this);
  setZValue(ItemProperty::EdgeItem);
  adjust();
}

// TODO(panqing): edgeOffsetRatio should be changed according to the type of the node
void EdgeItem::adjust()
{
	if (!source || !dest)
		return;

	line = QLineF(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
	qreal length = line.length();
	quint8 edgeOffsetRatio = 0;
	QPointF edgeOffset = QPointF((line.dx() * edgeOffsetRatio) / length, (line.dy() * edgeOffsetRatio) / length);

	// Prepares the item for a geometry change. 
	// Call this function before changing the bounding rect of an item to keep QGraphicsScene's index up to date.
	prepareGeometryChange();
	sourcePoint = line.p1() + edgeOffset;
	//sourcePoint = line.p1();
	//destPoint = line.p2();
	destPoint = line.p2() - edgeOffset;
}
