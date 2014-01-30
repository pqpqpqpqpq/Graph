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
** Hexagon Item is the element of the hexagonal grid used for discretization
**
****************************************************************************/

#ifndef HEXAGONITEM_H
#define HEXAGONITEM_H

#include <QGraphicsPolygonItem>

class HexagonItem : public QGraphicsPolygonItem
{
public:
	HexagonItem(QGraphicsItem *parent = 0);
	HexagonItem(const QPolygonF &polygon, QGraphicsItem *parent = 0);
	~HexagonItem() { }

	enum { Type = UserType + 103 };	// Type of the QGraphicsItem
	int type() const { return Type; }

	void paint(QPainter *painter, 
		const QStyleOptionGraphicsItem *option, 
		QWidget *widget);

	// qreal getEdgeLength() { return HEXAGON_EDGE_ITEM; }
	void setIndex(quint32 index) { this->index = index; }
	quint32 getIndex() { return index; }

private:
	void initSettings();
	void createHexagon();

	quint16 edgeWidth;
	qreal HEXAGON_EDGE_ITEM;
	quint32 index;	//	The index of the hexagon item
};

#endif
