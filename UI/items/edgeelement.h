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
** Edge Element is used as the edge in the discretized vascular network
**
****************************************************************************/

#ifndef EDGEELEMENT_H
#define EDGEELEMENT_H

#include "base_item/edgeitem.h"

class NodeItem;

class EdgeElement : public EdgeItem
{
public:
	EdgeElement(NodeItem *sourceNode, NodeItem *destNode);
	~EdgeElement() { }

	enum { Type = UserType + 107 };	// Type of the QGraphicsItem
	int type() const { return Type; }

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, 
		const QStyleOptionGraphicsItem *option, 
		QWidget *widget);
	QPainterPath shape() const;

private:
	NodeItem *source, *dest;
};
#endif
