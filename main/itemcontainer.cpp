/********************************************************************
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

** created:	2010/05/05
** author:	panqing

** purpose:	
*********************************************************************/

#include "itemcontainer.h"

QList<EdgeAttr *> ItemContainer::edgeAttrList;
QList<EdgeItem *> ItemContainer::edgeItemList;
QHash<quint32, NodeItem *> ItemContainer::nodeHash;
QGraphicsLineItem *ItemContainer::findedLine = NULL;
