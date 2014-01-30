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

#ifndef ITEMPROPERTY_H
#define ITEMPROPERTY_H

namespace ItemProperty
{
	enum ItemZLevel
	{
		PixmapItem = 0,
		NodeItem = 9,
		EdgeItem = 6,
    MainNodeItem = 9,
		HexagonItem = 3,
		SubEdgeItem = 3,
		SubNodeItem = 3,
		NodeElement = 3,
		EdgeElement = 3,
	};
}

#endif
