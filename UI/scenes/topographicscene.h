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
** This class provides a GraphicsScene with
** reimplemented mousePressEvent and mouseDoubleClickEvent
**
****************************************************************************/

#ifndef TOPOGRAPHICSCENE_H
#define TOPOGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QHash>

class TopoGraphicsView;
class EdgeItem;
class NodeItem;
class MainNodeItem;

class TopoGraphicScene : public QGraphicsScene
{
  Q_OBJECT

public:
	TopoGraphicScene(QObject *parent = 0);
	~TopoGraphicScene();

signals:
  void rightClickOnSegment(EdgeItem *);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
	TopoGraphicsView *topoGraphicsView;		// pointer to the topoGraphicsView of the scene
  QHash<quint32, NodeItem *> &nodeHash;
  MainNodeItem *startNode;
};

#endif
