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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "ui/widgets/topographicsview.h"

class QAction;
class QMenu;
class TopoGraphicsView;
class QTextStream;
class EdgeAttr;
class MainWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

protected:
  void closeEvent(QCloseEvent *event);

private slots:
  //void newFile();
  void open();
  void closeTop();
  bool save();
  bool saveAs();
  void about();

  void colorSet();
  void buildHexGrid();
  void searchItems();
  void importPara();

private:
  void createActions();
  void createMenus();
  void createToolBars();
  void createTopoGraphicsView();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  MainWidget *mainWidget;
  // TopoGraphicsView *topoGraphicsView;

  QString curFile;

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *optionMenu;
  QMenu *toolsMenu;
  QMenu *windowMenu;
  QMenu *helpMenu;
  QToolBar *fileToolBar;
  QToolBar *editToolBar;
  QToolBar *optionToolBar;
  QAction *openAct;
  QAction *closeAct;
  QAction *importParaAct;
  QAction *saveAct;
  QAction *saveAsAct;
  QAction *exitAct;
  QAction *colorAct;
  QAction *buildHexGridAct;
  QAction *searchAct;
  QAction *separatorAct;
  QAction *aboutAct;
  QAction *aboutQtAct;
};

#endif
