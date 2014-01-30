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

#include "subedgeitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include <math.h>
#include "base_item/nodeitem.h"
#include "base_item/itemproperty.h"
#include "data/edgeattr.h"
#include "main/resmanager.h"
#include "data/vescolormode.h"

SubEdgeItem::SubEdgeItem(NodeItem *sourceNode, NodeItem *destNode, EdgeAttr *edgeAttr)
:	EdgeItem(sourceNode, destNode, edgeAttr),
source(sourceNode),
dest(destNode),
itemEdgeAttr(edgeAttr),
vesColorMode(ResManager::vesColorMode),
findedSegIndicator(false)
{
  setZValue(ItemProperty::SubEdgeItem);
}

QRectF SubEdgeItem::boundingRect() const
{
  if (!source || !dest)
    return QRectF();

  qreal penWidth = 1;

  return QRectF(sourcePoint, QSize(destPoint.x() - sourcePoint.x(),
    destPoint.y() - sourcePoint.y()))
    .normalized();
}

/*!
Custom rendering of the item
Each subclass of EdgeItem has its own implementation 
*/
void SubEdgeItem::paint(QPainter *painter, 
                        const QStyleOptionGraphicsItem *option, 
                        QWidget *)
{
  // painter->setClipRect(option->exposedRect);

  if (!source || !dest)
    return;

  QLineF line(sourcePoint, destPoint);

  // show the width of the edgeItem with respect to the NEWDIAM
  // qreal showDiameter = itemEdgeAttr->getDoubleAttr(EdgeAttr::NEWDIAM)/1.2;
  qreal showDiameter = itemEdgeAttr->getDoubleAttr(EdgeAttr::OLDDIAM);

  Qt::PenStyle style = Qt::SolidLine;
  quint16 segName = itemEdgeAttr->getIntAttr(EdgeAttr::SEGNAME);

  switch(vesColorMode)
  {
    /* For showing the parameters (Phase shift of velocity, pressure. PI, RI et al.) */
  case VesColorMode::Parameter:
    {
      qreal pen_r=itemEdgeAttr->getDoubleAttr(EdgeAttr::PARA_R);
      qreal pen_g=itemEdgeAttr->getDoubleAttr(EdgeAttr::PARA_G);
      qreal pen_b=itemEdgeAttr->getDoubleAttr(EdgeAttr::PARA_B);
      QColor color;
      color.setRgbF(pen_r,pen_g,pen_b);
      painter->setPen(QPen(color, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
    }
    break;
  case VesColorMode::VesselType:
    {
      /* For showing the type of vessels */
      if (itemEdgeAttr->getIntAttr(EdgeAttr::TYPE) == 1){
        painter->setPen(QPen(Qt::red, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
        setZValue(ItemProperty::SubEdgeItem+1);
      }
      else if (itemEdgeAttr->getIntAttr(EdgeAttr::TYPE) == 3){
        painter->setPen(QPen(Qt::blue, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
        setZValue(ItemProperty::SubEdgeItem+1);
      }
      else{
        painter->setPen(QPen(Qt::yellow, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
        setZValue(ItemProperty::SubEdgeItem+1);
      }
    }
    break;
  case VesColorMode::Monochrome:
    {
      painter->setPen(QPen(Qt::white, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
      setZValue(ItemProperty::SubEdgeItem+1);
    }
    break;
  case VesColorMode::TypPathway:
    {
      /* For showing the type of vessels */
      if (itemEdgeAttr->getIntAttr(EdgeAttr::TYPE) == 1){
        if (segName==1 || segName==2 || segName==3 ||
          segName==4 || segName==5 || segName==6 ||
          segName==52 || segName==53 || segName==75 ||
          segName==76 || segName==82 || segName==83 ||
          segName==84 || segName==88 || segName==91){
            painter->setPen(QPen(Qt::red, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
            setZValue(ItemProperty::SubEdgeItem+1);
        }
        else
          painter->setPen(QPen(Qt::darkRed, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
      }
      else if (itemEdgeAttr->getIntAttr(EdgeAttr::TYPE) == 3){
        if (segName==2036 || segName==2304 || segName==2303 || 
          (segName>=2001 && segName<=2017) ){
            painter->setPen(QPen(Qt::blue, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
            setZValue(ItemProperty::SubEdgeItem+1);
        }
        else
          painter->setPen(QPen(Qt::darkBlue, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
      }
      else{
        if (segName==1091){
          painter->setPen(QPen(Qt::yellow, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
          setZValue(ItemProperty::SubEdgeItem+1);
        }
        else
          painter->setPen(QPen(Qt::darkYellow, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
      }
      break;
    }
  default:
    break;
  }
  
  // If this is the segment in searching
  if(findedSegIndicator)
  {
    painter->setPen(QPen(Qt::green, showDiameter, style, Qt::RoundCap, Qt::RoundJoin));
  }

  painter->drawLine(line);
}

/*!
\brief	The shape is IMPORTANT!

If the shape is not reimplemented, the default shape 
is the same as the boundingRect. 
This could lead problems in collision detection and
behavior of some functions such as itemAt(QPointF &point)
*/
QPainterPath SubEdgeItem::shape() const
{
  QPainterPath path;
  QPolygonF polygon;
  qreal shapeWidth;
  qreal shapeHeight;
  qreal x1 = source->scenePos().x();
  qreal x2 = dest->scenePos().x();
  qreal y1 = source->scenePos().y();
  qreal y2 = dest->scenePos().y();

  // deal with different directions of the line
  // TODO(panqing): it should be better but I don't know how to
  if ((y1-y2)*(x1-x2) <= 0)
  {
    shapeWidth = 10;
    shapeHeight = 10;
  }
  else
  {
    shapeWidth = -10;
    shapeHeight = 10;
  }

  QPointF point1(line.p1() - QPointF(shapeWidth,shapeHeight));
  QPointF point2(line.p1() + QPointF(shapeWidth,shapeHeight));
  QPointF point3(line.p2() + QPointF(shapeWidth,shapeHeight));
  QPointF point4(line.p2() - QPointF(shapeWidth,shapeHeight));

  polygon << point1 << point2 << point3 << point4; 
  path.addPolygon(polygon);
  return path;
}
