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
****************************************************************************/

#include <math.h>

#include <QDebug>
#include <QWheelEvent>
#include <QPixmap>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

#include "topographicsview.h"
#include "ui/scenes/topographicscene.h"
#include "ui/items/nodeelement.h"
#include "ui/items/hexagonitem.h"
#include "main/resmanager.h"
#include "main/itemcontainer.h"
#include "data/edgeattr.h"
#include "data/itemfactory.h"
#include "data/hexagonpoint.h"

TopoGraphicsView::TopoGraphicsView(QWidget *parent)
:	QGraphicsView(parent),
	ratioWR(0.01),
	nodeHash(ItemContainer::nodeHash)
{
	topoGraphicScene = NULL;
	initScene();

	// Functions of these settings could be referred in the Qt Assistant
	setCacheMode(QGraphicsView::CacheBackground);
	setRenderHint(QPainter::Antialiasing);
	setDragMode(QGraphicsView::ScrollHandDrag);
	setTransformationAnchor(AnchorUnderMouse);
	setResizeAnchor(AnchorViewCenter);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	setMinimumSize(400, 400);
}

TopoGraphicsView::~TopoGraphicsView()
{
	if (topoGraphicScene != NULL)
	{
		delete topoGraphicScene;
		topoGraphicScene = NULL;
	}
}

/*!
	\brief Reimplementation of the keyPressEvent
*/
void TopoGraphicsView::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Up:
		
		break;
	case Qt::Key_Down:
		
		break;
	case Qt::Key_Left:
		
		break;
	case Qt::Key_Right:
		
		break;
	case Qt::Key_Plus:
		scaleView(1.1);
		break;
	case Qt::Key_Minus:
		scaleView(1 / 1.1);
		break;
	case Qt::Key_Space:
    break;
	default:
		QGraphicsView::keyPressEvent(event);
	}
}

///*!
//	\brief Reimplementation of the timerEvent
//*/
//void TopoGraphicsView::timerEvent(QTimerEvent *event)
//{
//	Q_UNUSED(event);
//
//	// if the dynamic adjust is disabled, all the forces of the nodes are not calculated
//	if (adjustState)
//	{
//		QList<NodeItem *> nodes;	// All the NodeItem on the scene
//		foreach (QGraphicsItem *item, scene()->items()) 
//		{
//			if (NodeItem *nodeItem = dynamic_cast<NodeItem *>(item))
//				nodes << nodeItem;
//		}
//
//		foreach (NodeItem *nodeItem, nodes)
//			nodeItem->calculateForces();	// new position is calculated
//
//		bool itemsMoved = false;
//		foreach (NodeItem *nodeItem, nodes) 
//		{
//			// the position of node item is set to the new position
//			// itemChange function is evoked by advance()
//			if (nodeItem->posAdvance())
//				itemsMoved = true;
//		}
//
//		if (!itemsMoved) 
//		{
//			killTimer(timerId);
//			timerId = 0;
//		}
//	}
//}

/*!
	\brief Reimplementation of the wheelEvent
*/
void TopoGraphicsView::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, event->delta() / 360.0));
}

void TopoGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);
	
	QRectF sceneRect = this->sceneRect();
  painter->fillRect(sceneRect, ResManager::backColor);
}

/*!
	\brief Scale the viewport by the scaleFactor
	\param scaleFactor
*/
void TopoGraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.01 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}

/*!
	\brief Add items to the scene
	TODO(panqing): Functions combination should be considered
*/
void TopoGraphicsView::addItems()
{
	// To use import function or show main node and edge items, enable the two callings
	// Import function only works for main node and edge items
	// Import function requires the two callings, but showing main node and edge items needs only the second
	ItemFactory::addNodeItems(this);
	ItemFactory::addSubEdgeItems(this);
	
	// ItemFactory::addElements(this);

	// ItemFactory::addHexagonItems(this);
}

/*!
	\brief Save the scene to QPixmap and return the QPixmap object to MainWindow
*/
QPixmap TopoGraphicsView::saveScene()
{
	QSize pixmapSize = sceneRect().size().toSize();
	QPixmap savePixmap(pixmapSize);
	if (savePixmap.isNull())
	{
		QMessageBox::warning(this, tr("Cannot Save the pic"), tr("Cannot Save the pic"));
		return QPixmap();
	}
	QPainter painter(&savePixmap);
	scene()->render(&painter);
	return savePixmap;
}

/*!
	\brief Set the position of all the NodeItem to the nearest hexagonal grid crossing
*/
void TopoGraphicsView::locateNodeItems()
{
	ItemFactory::locateNodeItems(this);	
}

/*!
	\brief Initialize the QGraphicsScene of the TopoGraphicsView
*/
void TopoGraphicsView::initScene()
{
	qreal sceneWidth;
	qreal sceneHeight;

  sceneWidth = ResManager::getSceneRect().width();
  sceneHeight = ResManager::getSceneRect().height();

  if (topoGraphicScene==NULL){
    topoGraphicScene = new TopoGraphicScene(this);
    topoGraphicScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    topoGraphicScene->setSceneRect(-sceneWidth/2,
      -sceneHeight/2,
      sceneWidth,
      sceneHeight);
    setScene(topoGraphicScene);

    // The signal is transmitted to MainWidget for showing the edge's attributes
    connect(topoGraphicScene, SIGNAL(rightClickOnSegment(EdgeItem *)), this, SIGNAL(rightClickOnSegment(EdgeItem *)));
  }
}
