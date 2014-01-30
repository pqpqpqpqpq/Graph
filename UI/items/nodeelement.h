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
** Node Element is used as the node in the discretized vascular network
**
****************************************************************************/

#ifndef NODEELEMENT_H
#define NODEELEMENT_H

#include "base_item/nodeitem.h"

class NodeElement : public NodeItem
{
public:
	NodeElement(TopoGraphicsView *topoGraphicsView = 0);
	~NodeElement() { }

	enum { Type = UserType + 106 };	// Type of the QGraphicsItem
	int type() const { return Type; }

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	qreal radius, diameter;			// radius of the nodeItem, sometimes it changes with the size of its scene
};
#endif
