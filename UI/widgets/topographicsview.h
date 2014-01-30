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
** This class extends QGraphicsView
**
****************************************************************************/

#ifndef TOPOGRAPHICSVIEW_H
#define TOPOGRAPHICSVIEW_H

#include <QtGui/QGraphicsView>

class MainEdgeItem;
class NodeItem;
class QGraphicsPixmapItem;
class TopoGraphicScene;
class EdgeItem;

class TopoGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	TopoGraphicsView(QWidget *parent = 0);
	~TopoGraphicsView();

	void addItems();
	QPixmap saveScene();

	void locateNodeItems();
  void initScene();
  void scaleView(qreal scaleFactor);

signals:
  void rightClickOnSegment(EdgeItem *);

protected:
	void keyPressEvent(QKeyEvent *event);
	// void timerEvent(QTimerEvent *event);
	void wheelEvent(QWheelEvent *event);
	void drawBackground(QPainter *painter, const QRectF &rect);

private:
	qreal ratioWR;
	TopoGraphicScene *topoGraphicScene;

	QHash<quint32, NodeItem *> &nodeHash;
};

#endif
