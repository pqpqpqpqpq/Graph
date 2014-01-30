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

#include "hexagonpoint.h"

HexagonPoint::HexagonPoint()
:	QPointF(),
	occupied(false)
{
	setX(0.0);
	setY(0.0);
}

HexagonPoint::HexagonPoint(const QPointF &point)
:	QPointF(point),
	occupied(false)
{
	setX(point.x());
	setY(point.y());
}

HexagonPoint::HexagonPoint(qreal x, qreal y)
:	QPointF(x,y),
	occupied(false)
{

}
