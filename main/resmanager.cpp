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

#include "resmanager.h"

#include <QPixmap>
#include "itemcontainer.h"
#include "data/edgeattr.h"
#include "data/hexagonpoint.h"
#include "ui/items/base_item/nodeitem.h"

/*!
	Initialization of static data member
*/
QSettings ResManager::settings("micro_circulation.ini", QSettings::IniFormat);
QList<HexagonPoint *> ResManager::hexagonPointList;
QRectF ResManager::sceneRect;
QMultiMap<bool, QString> ResManager::attributesMap;
QColor ResManager::backColor;
quint8 ResManager::vesColorMode = 0;

/*!
	\brief Initialization from .ini file
*/
void ResManager::initSettings()
{
	// Initialize the scene rect
	quint16 sceneWidth, sceneHeight;
  bool ok;

  backColor = ResManager::settings.value("Color/Background Color").value<QColor>();
  vesColorMode = ResManager::settings.value("Color/Vessel Color Mode").toInt(&ok);
  if(!ok)
    vesColorMode = -1;
}

/*!
	Clear all the resources which are already loaded into memory
*/
void ResManager::unloadData()
{
	// clear mainEdgeAttrList
	for (int i=0; i<ItemContainer::edgeAttrList.size(); ++i)
	{
		EdgeAttr *aboutToDelList = ItemContainer::edgeAttrList.value(i);
		delete aboutToDelList;
	}
	ItemContainer::edgeAttrList.clear();

	// clear attrNameList and showNameList
	attributesMap.clear();

	// clear nodeHash
	QHash<quint32, NodeItem *>::iterator hashIt;
	for (hashIt=ItemContainer::nodeHash.begin(); hashIt != ItemContainer::nodeHash.end(); ++hashIt)
	{
		delete *hashIt;
	}
	ItemContainer::nodeHash.clear();
}
