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
** This class manages all the global resources
**
****************************************************************************/

#ifndef RESMANAGER_H
#define RESMANAGER_H

#include <QList>
#include <QStringList>
#include <QMultiMap>
#include <QSettings>

class EdgeAttr;
class FixedNodes;
class MainEdgeItem;
class HexagonPoint;

class ResManager
{
public:
	static void initSettings();
	static QRectF &getSceneRect() { return sceneRect; }
	static void unloadData();

	static QList<HexagonPoint *> hexagonPointList;	// List stores all the points of the hexagon grid
	static QMultiMap<bool, QString> attributesMap;	// The names of all the attributes of a vessel segment
	static QSettings settings;						// Settings of the program
  static QColor backColor;              // Background color
  static quint8 vesColorMode;

private:
	ResManager() { }		// The constructor is set as a private function, so it cannot create instance
	~ResManager() { }

	static QRectF sceneRect;
};

#endif
