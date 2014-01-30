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
** Functions for IO operations
** Load different types of files
**
****************************************************************************/

#ifndef DATAIO_H
#define DATAIO_H

#include <QObject>
#include <QStringList>
#include <QMultiMap>
#include <QList>
#include <QRectF>

class QTextStream;
class QPixmap;
class QString;
class EdgeAttr;
class EdgeItem;
class NodeItem;
class FixedNodes;

class DataIO : public QObject
{
public:
	static int loadDatData(QTextStream &in);
	static int loadPrnData(QTextStream &in);
	static void unloadData();
	static void savePixmap(QPixmap &pixmap, const QString &fileName);
	static int loadTopolData(QTextStream &in);
	static int loadOptData(QTextStream &in);
  static int loadParaData(QTextStream &in);

private:
	DataIO(QObject *parent = 0);	// the constructor is set private so it cannot create an instance
	~DataIO() { }

	// These are references or pointers to the static resource in the class ResManager or ItemContainer
	static QMultiMap<bool, QString> &attributesMap;
	static QList<EdgeAttr *> &edgeAttrList;
  static QList<EdgeItem *> &edgeItemList;
	static QHash<quint32, NodeItem *> &nodeHash;
	static QRectF &sceneRect;

	static const quint16 coeff;
};
#endif // DATAIO_H
