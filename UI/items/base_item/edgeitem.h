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
** This class is a base class of Line Items representing the vessel of the Micro Vascular Network
**
****************************************************************************/

#ifndef EDGEITEM_H
#define EDGEITEM_H

#include <QGraphicsItem>
#include <QLineF>

class NodeItem;
class EdgeAttr;

class EdgeItem : public QGraphicsItem
{
public:
	EdgeItem(NodeItem *sourceNode, NodeItem *destNode, EdgeAttr *edgeAttr);
	~EdgeItem() { }

	NodeItem *sourceNode() const { return source; }
	void setSourceNode(NodeItem *nodeItem) { source = nodeItem;	adjust(); }

	NodeItem *destNode() const { return dest; }
	void setDestNode(NodeItem *nodeItem) { dest = nodeItem; adjust(); }

	EdgeAttr *getEdgeAttr() const { return edgeAttr; }
	void setEdgeAttr(EdgeAttr *edgeAttr) { this->edgeAttr = edgeAttr; }

	// type of this QGraphicsItem
	// the type of base class starts from UserType+1
	enum { Type = UserType + 2 };
	int type() const { return Type; }

	void adjust();

protected:
	QPointF sourcePoint;		// position of the start point
	QPointF destPoint;			// position of the end point
	QLineF line;				// QLineF of the edgeItem

private:
	NodeItem *source, *dest;	// source and destination of the edgeItem
	EdgeAttr *edgeAttr;	// the attribute list of this edge
};

#endif
