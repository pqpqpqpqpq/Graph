/****************************************************************************
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

** The SubNodeItem is used (accompanied with SubEdgeItem) to plot a more accurate topology of micro vascular network.
**
** Author: panqing
** email: zjupanqing@gmail.com
**
****************************************************************************/

#ifndef SUBNODEITEM_H
#define SUBNODEITEM_H

#include "base_item/nodeitem.h"
#include <QList>

class SubEdgeItem;

class SubNodeItem : public NodeItem
{
public:
	SubNodeItem(TopoGraphicsView *topoGraphicsView, quint32 nodeIndex);
	~SubNodeItem() { }

	// type of this QGraphicsItem
	enum { Type = UserType + 105 };
	int type() const { return Type; }

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	quint32 nodeIndex;				// the index of this subNodeItem
	qreal radius, diameter;			// radius of the nodeItem, sometimes it changes with the size of its scene
};

#endif
