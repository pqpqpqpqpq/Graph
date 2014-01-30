/********************************************************************
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

** created:	2010/05/05
** author:	panqing

** purpose:	
*********************************************************************/

#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <QList>
#include <QHash>
#include <QGraphicsLineItem>

class EdgeAttr;
class NodeItem;
class EdgeItem;

class ItemContainer
{
public:
	static QList<EdgeAttr *> edgeAttrList;		    // DataList stores the EdgeAttr pointers of EdgeItem
  static QList<EdgeItem *> edgeItemList;        // DataList stores the EdgeItem
	static QHash<quint32, NodeItem *> nodeHash;		// A hash table which store the index of mainNodeItem and its corresponding pointer
	static QGraphicsLineItem *findedLine;

private:
	ItemContainer() { }
	~ItemContainer() { }
};

#endif
