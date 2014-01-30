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
** Triangle tissue element
**
****************************************************************************/

#ifndef TISSUEELEMENT_H
#define TISSUEELEMENT_H

#include <QObject>

class TissueElement : public QObject
{
public:
	TissueElement(QObject *parent = 0);
	~TissueElement() { }

private:
	quint8 index;	// Index of the triangle tissue in a hexagon
//  ____
// /\1 /\
///6_\/2_\
//\5 /\3 /
// \/4_\/

};

#endif
