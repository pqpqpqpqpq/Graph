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

#include "edgeattr.h"

EdgeAttr::EdgeAttr()
:	INT_ATTR_COUNT(6),
	DOUBLE_ATTR_COUNT(25),
	STRING_ATTR_COUNT(1)
{
	// Initialize the EdgeAttr
	int i;
	for (i = 0; i < INT_ATTR_COUNT; i++)
		intAttr.push_back(-1);

	for (i = 0; i < DOUBLE_ATTR_COUNT; i++)
		doubleAttr.push_back(0.0);

	for (i = 0; i < STRING_ATTR_COUNT; i++)
		stringAttr.push_back(tr(""));
}
