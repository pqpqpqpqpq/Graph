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
** Construct the items on the scene
** Provide add functions to put different combination of items
**
****************************************************************************/

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QObject>

class TopoGraphicsView;
class SubEdgeItem;

class ItemFactory : public QObject
{
public:
	// add node items
	static void addNodeItems(TopoGraphicsView *graphicsView);
	// add edge items
	static void addSubEdgeItems(TopoGraphicsView *graphicsView);
	// add discretization elements
	static void addElements(TopoGraphicsView *graphicsView);
	// add hexagonal grid
	static void addHexagonItems(TopoGraphicsView *graphicsView);
	// move the MainNodeItem to the hexagonal grid point
	static void locateNodeItems(TopoGraphicsView *graphicsView);
	// add finded edge item
	static void addFindedLineItem(TopoGraphicsView *graphicsView);

private:
	ItemFactory();
	~ItemFactory() { }

	static void connectHexagonPoint();
	static void saveHexagonPoint(TopoGraphicsView *graphicsView);

	static qreal HEXAGON_EDGE_LENGTH;		// edge length of the hexagonal grid
};

#endif
