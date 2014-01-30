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
** This class stores the attributes of each EdgeItem and provide get/set pairs
**
****************************************************************************/

#ifndef EDGEATTR_H
#define EDGEATTR_H

#include <QObject>
#include <QString>
#include <QStringList>

class EdgeAttr : public QObject
{
public:
	EdgeAttr();
	~EdgeAttr() { }

	/*
		Attributes in *.dat, *.prn, topol files and opt files
		segName and type should be loaded from *.dat files
		oldDiam,vel and HDMes should be loaded from *.prn files
	*/
	
	enum IntIndex { 
		SEGNAME,		// Segment Name (both *.dat and *.prn have this attribute)
		TYPE,			// Type of vessel (both *.dat and *.prn have this attribute)
		STARTNODE,		// From
		ENDNODE,		// To
		SUB_SEGPARTID	// Segment Part ID of the SubEdgeItem (Sub segment part id)
	};

	enum DoubleIndex {
		LENGTH,		// Vessel Length (in um)
		ALLSUBLENGTH,	// Sum of the lengths of sub segment (in pixel, only available in mainEdgeAttrList)
		OLDDIAM,	// Old Diameter (both *.dat and *.prn have this attribute)
		NEWDIAM,	// New Diameter
		PR_MEAN,	
		TAU_REAL,
		TAU_FIT,
		VEL,
		FLOW,
		VISC,
		HDMES,
		P_O2,
		S_O2,
		S_TOT,
		METSTIM,
		HYDROD,
		CONDSTI,
		METLOC,
		METCONV,
		WALLTH,
		SIGMA,
		SO2IN,
		SO2OUT,
		DELTAP,
		CONSADFACT,
    // For showing parameter distribution map
    PARAMETER,
    PARA_R,
    PARA_G,
    PARA_B,
	};

	enum StringIndex {
		SUB_SEGNAME	// Segment name of the SubEdgeItem
	};

	// TODO(panqing): It's not a good implementation! Try to use template
	void setIntAttr(IntIndex index, quint32 value) { intAttr.replace(index, value); }
	quint32 getIntAttr(IntIndex index) { return intAttr.value(index); }

	void setDoubleAttr(DoubleIndex index, qreal value) { doubleAttr.replace(index, value); }
	qreal getDoubleAttr(DoubleIndex index) { return doubleAttr.value(index); }

	void setStringAttr(StringIndex index, QString value) { stringAttr.replace(index, value); }
	QString getStringAttr(StringIndex index) { return stringAttr.value(index); }

private:
	const quint8 INT_ATTR_COUNT;
	const quint8 DOUBLE_ATTR_COUNT;
	const quint8 STRING_ATTR_COUNT;

	QList<quint32> intAttr;
	QList<qreal> doubleAttr;
	QStringList stringAttr;
};

#endif
