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
** This class is the base class of Node Items representing the bifurcations in the micro vascular network
**
****************************************************************************/

#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsItem>
#include <QList>

class EdgeItem;
class TopoGraphicsView;
class QGraphicsSceneMouseEvent;

class NodeItem : public QGraphicsItem
{
public:
	NodeItem(TopoGraphicsView *topoGraphicsView);
	~NodeItem() { }

	// manage the edges connected to the nodeItem
	void addEdge(EdgeItem *edgeItem);
	QList<EdgeItem *> edges();

	// type of this QGraphicsItem
	enum { Type = UserType + 1 };
	int type() const { return Type; }

	// set the get the radius of the nodeItem
	void setRadius(qreal radius) { this->radius = radius; }
	qreal getRadius() { return radius; }

	void setTopoGraphicsView(TopoGraphicsView *topoGraphicsView) { this->graph = topoGraphicsView; }
	bool posAdvance();
   
protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	// void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	QPointF newPos;	// temp
  qreal radius, diameter;			// radius of the nodeItem, sometimes it changes with the size of its scene

private:
	QList<EdgeItem *> edgeList;		// the edgeItem connected to this nodeItem
	TopoGraphicsView *graph;		// pointer to its QGraphicsView
};

#endif
