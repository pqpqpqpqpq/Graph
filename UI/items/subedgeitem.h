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
** It connects two SubNodeItem items or one SubNodeItem and one MainNodeItem item.
** The attribute of the SubEdgeItem shares with the corresponding MainEdgeItem.
** SubEdgeItem is used (accompanied with SubNodeItem) to give a more accurate topology of the micro vascular network.
**
****************************************************************************/

#ifndef SUBEDGEITEM_H
#define SUBEDGEITEM_H

#include "base_item/edgeitem.h"

class NodeItem;

class SubEdgeItem : public EdgeItem
{
public:
	SubEdgeItem(NodeItem *sourceNode, NodeItem *destNode, EdgeAttr *edgeAttr);
	~SubEdgeItem() { }

	enum { Type = UserType + 104 };	// Type of the QGraphicsItem
	int type() const { return Type; }

  void setFindedSegIndicator(bool indicator) { findedSegIndicator = indicator; }
  bool getFindedSegIndicator() { return findedSegIndicator; }

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, 
		const QStyleOptionGraphicsItem *option, 
		QWidget *widget);
	QPainterPath shape() const;

private:
	NodeItem *source, *dest;
	EdgeAttr *itemEdgeAttr;
  quint8 &vesColorMode;
  bool findedSegIndicator;
};

#endif
