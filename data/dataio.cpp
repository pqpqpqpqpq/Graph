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

#include <QTextStream>
#include <QPixmap>
#include <QString>
#include <QByteArray>
#include <QBuffer>
#include <QDebug>

#include "dataio.h"
#include "main/resmanager.h"
#include "main/itemcontainer.h"
#include "edgeattr.h"
#include "ui/items/subnodeitem.h"
#include "ui/items/mainnodeitem.h"
#include "ui/items/subedgeitem.h"

QList<EdgeAttr *> &DataIO::edgeAttrList(ItemContainer::edgeAttrList);
QList<EdgeItem *> &DataIO::edgeItemList(ItemContainer::edgeItemList);
QHash<quint32, NodeItem *> &DataIO::nodeHash(ItemContainer::nodeHash);
QMultiMap<bool, QString> &DataIO::attributesMap(ResManager::attributesMap);
QRectF &DataIO::sceneRect(ResManager::getSceneRect());
const quint16 DataIO::coeff = 20000;

DataIO::DataIO(QObject *parent)
:	QObject(parent)
{

}

/*!
	\brief Load .dat file
	\param	in	QTextStream which holds the .dat file
	SEGNAME, TYPE, FROM, TO and LENGTH are loaded from the file

	// TODO(panqing): Error processing should be added
*/
int DataIO::loadDatData(QTextStream &in)
{
	QString line;	//	One line of the file
	QStringList lineList;	// Items in one line, seperated by some delimiters
	const int lengthThreshold = 10;	// Recognize one line as a recording by its length

	while (!(line = in.readLine()).contains("SEGMENT"))
		;

  // 数据列之间可用tab或space分隔
	if(line.contains("\t"))
		lineList = line.split("\t", QString::SkipEmptyParts);
	else
		lineList = line.split(" ", QString::SkipEmptyParts);

	// FROM and TO are inserted into the attributes name list
	// NOTICE(panqing): because the SEGMENT NAME takes 2 positions in the lineList, 
	// the indices of FROM and TO (3, 4) are different from those below (2, 3)
	attributesMap.insert(false, lineList.at(3));
	attributesMap.insert(false, lineList.at(4));
	// LENGTH are inserted into the show name list
	attributesMap.insert(true, lineList.at(6));

	while ((line = in.readLine()).length() >= lengthThreshold)
	{
		EdgeAttr *edgeAttr = new EdgeAttr();

		// There are two format of the separator: tab and space
		if(line.contains("\t"))
			lineList = line.split("\t", QString::SkipEmptyParts);
		else
			lineList = line.split(" ", QString::SkipEmptyParts);

		edgeAttr->setIntAttr(EdgeAttr::SEGNAME, lineList.at(0).toInt());
		edgeAttr->setIntAttr(EdgeAttr::TYPE, lineList.at(1).toInt());		// NOTICE(panqing): Type in *.dat and *.prn are DIFFERENT!!!!!! Use the type from .dat file
		edgeAttr->setIntAttr(EdgeAttr::STARTNODE, lineList.at(2).toInt());
		edgeAttr->setIntAttr(EdgeAttr::ENDNODE, lineList.at(3).toInt());
		edgeAttr->setDoubleAttr(EdgeAttr::OLDDIAM, lineList.at(4).toDouble());
		edgeAttr->setDoubleAttr(EdgeAttr::LENGTH, lineList.at(5).toDouble());

		edgeAttrList.append(edgeAttr);	// ResManager::getEdgeAttrList() returns a reference to DataList
	}
	return 0;
}

/*!
	\brief Load .prn file
	\param	in	QTextStream holds the .prn file
	NOTICE(panqing): Prn data has to be loaded AFTER calling DataIO::LoadDatData
*/
int DataIO::loadPrnData(QTextStream &in)
{
	QString line;	//	One line of the file
	QStringList lineList;	// Items in one line, seperated by some delimiters
	const int lengthThreshold = 10;	// Recognize one line as a recording by its length

	while (!(line = in.readLine()).contains("Name"))
		;
	lineList = line.split(" ", QString::SkipEmptyParts);

	// Decide the default show parameters
	// TODO(panqing): It should be implemented by QSettings so that the conditions could be memorized
	attributesMap.insert(true, lineList.at(0).toUpper());
	attributesMap.insert(true, lineList.at(1).toUpper());
	attributesMap.insert(true, lineList.at(3).toUpper());
	attributesMap.insert(true, lineList.at(6).toUpper());
	attributesMap.insert(true, lineList.at(7).toUpper());

	attributesMap.insert(false, lineList.at(2).toUpper());
	attributesMap.insert(false, lineList.at(4).toUpper());
	attributesMap.insert(false, lineList.at(5).toUpper());

	for (int i = 8; i < lineList.size(); i++)
	{
		attributesMap.insert(false, lineList.at(i).toUpper());
	}

	int j = 0;
	while ((line = in.readLine()).length() >= lengthThreshold)
	{
		if (!edgeAttrList.isEmpty())
		{
			// The order of the segments id in .dat and .prn are the same
			EdgeAttr *edgeAttr = edgeAttrList[j];
			// There are two format of the separator: tab and space
			if(line.contains("\t"))
				lineList = line.split("\t", QString::SkipEmptyParts);
			else
				lineList = line.split(" ", QString::SkipEmptyParts);

			int segName1 = edgeAttr->getIntAttr(EdgeAttr::SEGNAME);
			int segName2 = lineList.at(0).toInt();
			Q_ASSERT(segName1 == segName2);
			edgeAttr->setDoubleAttr(EdgeAttr::NEWDIAM, lineList.at(2).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::PR_MEAN, lineList.at(3).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::TAU_REAL, lineList.at(4).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::TAU_FIT, lineList.at(5).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::VEL, lineList.at(6).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::FLOW, lineList.at(7).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::VISC, lineList.at(8).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::HDMES, lineList.at(9).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::P_O2, lineList.at(10).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::S_O2, lineList.at(11).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::S_TOT, lineList.at(12).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::METSTIM, lineList.at(13).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::HYDROD, lineList.at(14).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::CONDSTI, lineList.at(15).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::METLOC, lineList.at(16).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::METCONV, lineList.at(17).toDouble());
			// TYPE in *.dat and *.prn are DIFFERENT!!!!!!
			// USE the TYPE in .dat file
			// edgeAttr->setIntAttr(EdgeAttr::TYPE, lineList.at(18).toInt());
			edgeAttr->setDoubleAttr(EdgeAttr::WALLTH, lineList.at(19).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::SIGMA, lineList.at(20).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::SO2IN, lineList.at(21).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::SO2OUT, lineList.at(22).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::DELTAP, lineList.at(23).toDouble());
			edgeAttr->setDoubleAttr(EdgeAttr::CONSADFACT, lineList.at(24).toDouble());
		}
		j++;
	}
	return 0;
}

/*!
	\brief Unload all the data and free the resources hold by ResManager
*/
void DataIO::unloadData()
{
	ResManager::unloadData();
}

/*!
	\brief Save QPixmap to .jpg file
	\param	pixmap		QPixmap object which holds the pixmap
	\param	fileName	The file name of the pixmap file
*/
void DataIO::savePixmap(QPixmap &pixmap, const QString &fileName)
{
	pixmap.save(fileName);
}

/*!
	\brief Load topol file
	\param	in	QTextStream which holds the topol.txt file
	TODO(panqing): showNameList and attrNameList are needed to be set
*/
int DataIO::loadTopolData(QTextStream &in)
{
	QString line;	//	One line of the file
	QStringList lineList;	// Items in one line, seperated by some delimiters
	const int lengthThreshold = 10;	// Recognize one line as a recording by its length
	quint16 xPos, yPos, halfSceneWidth, halfSceneHeight, maxX=0, minX=0, maxY=0, minY=0;
	quint16 subSegPartID, lastSubSegPartID;
	subSegPartID = 0;
	lastSubSegPartID = 0;

	while (!(line = in.readLine()).contains("SegmentId"))
		;

  qint64 filePos=in.pos();  // 记录文件起始位置，以便稍后返回该位置
  while ((line = in.readLine()).length() >= lengthThreshold)
  {
    lineList = line.split(",", QString::SkipEmptyParts);

    // 先遍历所有血管段，得到最大/最小坐标
    xPos = lineList.at(5).toInt();
    yPos = lineList.at(6).toInt();
    if (xPos>maxX)
      maxX=xPos;
    if (yPos>maxY)
      maxY=yPos;
    if (xPos<minX)
      minX=xPos;
    if (yPos<minY)
      minY=yPos;

    xPos = lineList.at(9).toInt();
    yPos = lineList.at(10).toInt();
    if (xPos>maxX)
      maxX=xPos;
    if (yPos>maxY)
      maxY=yPos;
    if (xPos<minX)
      minX=xPos;
    if (yPos<minY)
      minY=yPos;
  }
  halfSceneWidth=(maxX-minX)/2;
  halfSceneHeight=(maxY-minY)/2;
  ResManager::getSceneRect().setRect(0,0,halfSceneWidth*2*1.1,halfSceneHeight*2*1.1);

  // 回到文件起始位置，开始读取数据
  in.seek(filePos);
	while ((line = in.readLine()).length() >= lengthThreshold)
	{
		EdgeAttr *edgeAttr = NULL;
		lineList = line.split("\t", QString::SkipEmptyParts);
		quint16 segName = lineList.at(0).toInt();
		for (int i=0;i<edgeAttrList.size();++i)
		{
			if (segName==edgeAttrList[i]->getIntAttr(EdgeAttr::SEGNAME))
			{
        edgeAttr=edgeAttrList[i];
				break;
			}
		}

		lastSubSegPartID = subSegPartID;	// Store the last sub segment part id
		subSegPartID = lineList.at(1).toInt();	// Acquire the sub segment part id of the new line

		// The last sub segment part id is 99
		// Change the last sub segment part id to its previous id plus 1
		// For example, 0, 1, 2, 99 --> 0, 1, 2, 3
		if (subSegPartID == 99)
			subSegPartID = lastSubSegPartID + 1;

		quint32 startNodeIndex, endNodeIndex;
		// StartNode
		// if the node is an subNodeItem, the index of the node is set as coeff*subIndex + mainNodeIndex
		// The index of each mainNodeItem < coeff while the index of each subNodeItem > coeff
		if (lineList.at(4).toInt() >= 0)
			startNodeIndex = lineList.at(4).toInt();
		else
			startNodeIndex = lineList.at(0).toInt() + coeff*subSegPartID;

		if (!nodeHash.contains(startNodeIndex))
		{
			xPos = lineList.at(5).toInt();
			yPos = lineList.at(6).toInt();

			// Create the NodeItem object, set its position and insert the node to a Hash structure
			if (startNodeIndex < coeff)
			{
				MainNodeItem *mainNodeItem = new MainNodeItem(NULL, startNodeIndex);
				mainNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(startNodeIndex, mainNodeItem);
			}
			else
			{
				SubNodeItem *subNodeItem = new SubNodeItem(NULL, startNodeIndex);
				subNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(startNodeIndex, subNodeItem);
			}
		}

		// EndNode
		// Do the same operations as the StartNode
		if (lineList.at(8).toInt() >= 0)
			endNodeIndex = lineList.at(8).toInt();
		else
			endNodeIndex = lineList.at(0).toInt() + coeff*(1+subSegPartID);

		if (!nodeHash.contains(endNodeIndex))
		{
			xPos = lineList.at(9).toInt();
			yPos = lineList.at(10).toInt();
			if (endNodeIndex < coeff)
			{
				MainNodeItem *mainNodeItem = new MainNodeItem(NULL, endNodeIndex);
				mainNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(endNodeIndex, mainNodeItem);
			}
			else
			{
				SubNodeItem *subNodeItem = new SubNodeItem(NULL, endNodeIndex);
				subNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(endNodeIndex, subNodeItem);
			}
		}

    SubEdgeItem *subEdgeItem = new SubEdgeItem(nodeHash[startNodeIndex], nodeHash[endNodeIndex], edgeAttr);
    edgeItemList.append(subEdgeItem);
    subEdgeItem->setEdgeAttr(edgeAttr);
	}

  ResManager::getSceneRect().setRect(maxX,maxY,halfSceneWidth,halfSceneHeight);
	return 0;
}

/*!
	\brief Load opt file
	\param	in	QTextStream which holds the opt.txt file
	NOTICE(panqing): Before loading opt data, dat and prn data are already loaded. mainEdgeAttrList is filled.
	TODO(panqing): showNameList and attrNameList are needed to be set
*/
int DataIO::loadOptData(QTextStream &in)
{
	QString line;	//	One line of the file
	QStringList lineList;	// Items in one line, seperated by some delimiters
	const int lengthThreshold = 10;	// Recognize one line as a recording by its length
	quint16 xPos, yPos, halfSceneWidth, halfSceneHeight, maxX=0, maxY=0, minX=50000, minY=50000;
	quint32 subSegPartID = 0, lastSubSegPartID = 0;

	while (!(line = in.readLine()).contains("SegmentId"))
		;

  qint64 filePos=in.pos();  // 当前文件位置
  while ((line = in.readLine()).length() >= lengthThreshold)
  {
    lineList = line.split(",", QString::SkipEmptyParts);

    // 先遍历所有血管段一遍，得到最大/最小坐标
    xPos = lineList.at(5).toInt();
    yPos = lineList.at(6).toInt();
    if (xPos>maxX)
      maxX=xPos;
    if (yPos>maxY)
      maxY=yPos;
    if (xPos<minX)
      minX=xPos;
    if (yPos<minY)
      minY=yPos;
    xPos = lineList.at(9).toInt();
    yPos = lineList.at(10).toInt();
    if (xPos>maxX)
      maxX=xPos;
    if (yPos>maxY)
      maxY=yPos;
    if (xPos<minX)
      minX=xPos;
    if (yPos<minY)
      minY=yPos;
  }
  halfSceneWidth=(maxX-minX)/2;
  halfSceneHeight=(maxY-minY)/2;
  ResManager::getSceneRect().setRect(0,0,halfSceneWidth*2*1.1,halfSceneHeight*2*1.1);

  in.seek(filePos);
	while ((line = in.readLine()).length() >= lengthThreshold)
	{
		EdgeAttr *edgeAttr = NULL;
		lineList = line.split(",", QString::SkipEmptyParts);
		quint16 segName = lineList.at(0).toInt();
		for (int i=0;i<edgeAttrList.size();++i)
		{
			if (segName==edgeAttrList[i]->getIntAttr(EdgeAttr::SEGNAME))
			{
        edgeAttr=edgeAttrList[i];
				break;
			}
		}

		lastSubSegPartID = subSegPartID;	// Store the last sub segment part id
		subSegPartID = lineList.at(1).toInt();	// Acquire the sub segment part id of the new line
		// The last sub segment part id is 99
		// Change the last sub segment part id to its previous id plus 1
		// For example, 0, 1, 2, 99 --> 0, 1, 2, 3
		if (subSegPartID == 99)
			subSegPartID = lastSubSegPartID + 1;

		quint32 startNodeIndex, endNodeIndex;
		// StartNode
		// if the node is an subNodeItem, the index of the node is set as coeff*subIndex+nodeIndex
		if (lineList.at(4).toInt() >= 0)
			startNodeIndex = lineList.at(4).toInt();
		else
			startNodeIndex = lineList.at(0).toInt() + coeff*subSegPartID;

		if (!nodeHash.contains(startNodeIndex))
		{
			xPos = lineList.at(5).toInt();
			yPos = lineList.at(6).toInt();

			if (startNodeIndex < coeff)
			{
				MainNodeItem *mainNodeItem = new MainNodeItem(NULL, startNodeIndex);
				mainNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(startNodeIndex, mainNodeItem);
			}
			else
			{
				SubNodeItem *subNodeItem = new SubNodeItem(NULL, startNodeIndex);
				subNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(startNodeIndex, subNodeItem);
			}
		}

		// EndNode
		if (lineList.at(8).toInt() >= 0)
			endNodeIndex = lineList.at(8).toInt();
		else
			endNodeIndex = lineList.at(0).toInt() + coeff*(1+subSegPartID);

		if (!nodeHash.contains(endNodeIndex))
		{
			xPos = lineList.at(9).toInt();
			yPos = lineList.at(10).toInt();
			if (endNodeIndex < coeff)
			{
				MainNodeItem *mainNodeItem = new MainNodeItem(NULL, endNodeIndex);
				mainNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(endNodeIndex, mainNodeItem);
			}
			else
			{
				SubNodeItem *subNodeItem = new SubNodeItem(NULL, endNodeIndex);
				subNodeItem->setPos(xPos-halfSceneWidth-minX, yPos-halfSceneHeight-minY);
				nodeHash.insert(endNodeIndex, subNodeItem);
			}
		}
    SubEdgeItem *subEdgeItem = new SubEdgeItem(nodeHash[startNodeIndex], nodeHash[endNodeIndex], edgeAttr);
    edgeItemList.append(subEdgeItem);
    subEdgeItem->setEdgeAttr(edgeAttr);
	}
	return 0;
}

int DataIO::loadParaData(QTextStream &in)
{
  QString line;
  QStringList lineList;
  const int lengthThreshold = 10;	// Recognize one line as a recording by its length

  // The first line contains the name of the parameter
  line = in.readLine();

  // The second line contains the title of each column
  line = in.readLine();

  while((line = in.readLine()).length() >= lengthThreshold)
  {
    lineList = line.split("\t", QString::SkipEmptyParts);
    for (int i=0; i<edgeAttrList.size(); ++i)
    {
      if (lineList.at(0).toInt()==edgeAttrList[i]->getIntAttr(EdgeAttr::SEGNAME))
      {
        edgeAttrList[i]->setDoubleAttr(EdgeAttr::PARAMETER,lineList.at(1).toDouble());
        edgeAttrList[i]->setDoubleAttr(EdgeAttr::PARA_R,lineList.at(2).toDouble());
        edgeAttrList[i]->setDoubleAttr(EdgeAttr::PARA_G,lineList.at(3).toDouble());
        edgeAttrList[i]->setDoubleAttr(EdgeAttr::PARA_B,lineList.at(4).toDouble());
        break;
      }
    }
  }
  return 0;
}
