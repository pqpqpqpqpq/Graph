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
** The mainNodeItem represents the real birfurcations in the micro vascular network
**
****************************************************************************/

#ifndef MAINNODEITEM_H
#define MAINNODEITEM_H

#include "base_item/nodeitem.h"

class MainNodeItem : public NodeItem
{
public:
	MainNodeItem(TopoGraphicsView *topoGraphicsView, quint32 nodeIndex);
	~MainNodeItem() { }

	// type of this QGraphicsItem
	enum { Type = UserType + 100 };
	int type() const { return Type; }

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  void setStartIndicator(bool indicator) { startIndicator = indicator; }
  bool getStartIndicator() { return startIndicator; }
  void setFindedNodeIndicator(bool indicator) { findedNodeIndicator = indicator; }
  bool getFindedNodeIndicator() { return findedNodeIndicator; }

private:
	quint32 nodeIndex;				// the index of this mainNodeItem
  bool startIndicator;      // indicate whether the node is a start node
  bool findedNodeIndicator; // indicate whether the node is in search
};

#endif
