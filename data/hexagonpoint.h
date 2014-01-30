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
** Store the position of the hexagonal grid bifurcation
**
****************************************************************************/

#ifndef HEXAGONPOINT_H
#define HEXAGONPOINT_H

#include <QPointF>
#include <QList>

class HexagonPoint : public QPointF
{
public:
	HexagonPoint();
	HexagonPoint(const QPointF &point);
	HexagonPoint(qreal x, qreal y);
	~HexagonPoint() { }

	void addAdjPoint(HexagonPoint *hexagonPoint) { adjPoints << hexagonPoint; }

	void setOccupied(bool occupied) { this->occupied = occupied; }
	bool isOccupied() { return occupied; }

private:
	QList<HexagonPoint *> adjPoints;	// One point should have three adjacent points
	bool occupied;	// Denotes whether this position is already occupied by a NodeItem
};

#endif
