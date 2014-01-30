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

#include <QtGui>

#include "mainwindow.h"
#include "main/resmanager.h"
#include "data/edgeattr.h"
#include "ui/widgets/loadfiledlg.h"
#include "ui/widgets/colorsetdlg.h"
#include "ui/widgets/searchdlg.h"
#include "data/dataio.h"
#include "mainwidget.h"

MainWindow::MainWindow()
{
	mainWidget = new MainWidget(this);
	setCentralWidget(mainWidget);

	createActions();
	createMenus();
	createToolBars();
	setCurrentFile("");

	showMaximized();
}

MainWindow::~MainWindow()
{
	if (mainWidget != NULL)
		delete mainWidget;	// topoGraphicsView will be deleted automatically
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
}

/*!
Open file will evoke the LoadFileDlg
.dat and .prn files must be loaded
if .jpg is loaded, picture is set to a PixmapItem
*/
void MainWindow::open()
{
	LoadFileDlg *loadFileDlg = new LoadFileDlg(this);

	if (loadFileDlg->exec() == QDialog::Accepted)
	{
		createTopoGraphicsView();
		/*ResManager::getSceneRect() = topoGraphicsView->sceneRect();*/
	}
	delete loadFileDlg;
}

/*!
  \brief Show the color settings DIALOG
*/
void MainWindow::colorSet()
{
  ColorSetDlg *colorSetDlg = new ColorSetDlg(this);
  colorSetDlg->exec();
  //if(topoGraphicsView!=NULL)
  //{
  //  // Trigger the update of the scene
  //  topoGraphicsView->scaleView(2);
  //  topoGraphicsView->scaleView(0.5);
  //}
}

bool MainWindow::save()
{
	if (curFile.isEmpty()) 
	{
		return saveAs();
	}
	else
	{
		return saveFile(curFile);
	}
}

bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save File"),
		QDir::currentPath(),
		tr("Images (*.jpg)"));
	if (fileName.isEmpty())
	{
		return false;
	}

	return saveFile(fileName);
}

void MainWindow::about()
{
	QMessageBox::about(this,
		tr("About Application"),
		tr("The <b>MicroCirculation Network</b> software is written by Qing Pan"));
}

void MainWindow::createActions()
{
	openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	closeAct = new QAction(tr("Close"), this);
	closeAct->setStatusTip(tr("Unload the data"));
	closeAct->setDisabled(true);
	connect(closeAct, SIGNAL(triggered()), this, SLOT(closeTop()));

  importParaAct = new QAction(tr("Import Parameters"), this);
  importParaAct->setEnabled(true);
  connect(importParaAct, SIGNAL(triggered()), this, SLOT(importPara()));

	saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
	saveAct->setDisabled(true);

	saveAsAct = new QAction(tr("Save &As..."), this);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
	saveAsAct->setDisabled(true);

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  colorAct = new QAction(tr("Color Settings"), this);
  colorAct->setStatusTip(tr("Color Settings"));
  connect(colorAct, SIGNAL(triggered()), this, SLOT(colorSet()));

	buildHexGridAct = new QAction(QIcon(":/images/network.png"), tr("Build Hexagonal Grid"), this);
	// buildHexGridAct->setIconText(tr("Grid"));
	buildHexGridAct->setCheckable(false);
	buildHexGridAct->setStatusTip(tr("Build Hexagonal Grid"));
	connect(buildHexGridAct, SIGNAL(triggered()), this, SLOT(buildHexGrid()));

	searchAct = new QAction(tr("Search"), this);
	searchAct->setStatusTip(tr("Search Nodes or Segments"));
	connect(searchAct, SIGNAL(triggered()), this, SLOT(searchItems()));

	separatorAct = new QAction(this);
	separatorAct->setSeparator(true);

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addAction(closeAct);
  fileMenu->addAction(importParaAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	// editMenu = menuBar()->addMenu(tr("&Edit"));

	optionMenu = menuBar()->addMenu(tr("&Option"));
  optionMenu->addAction(colorAct);

	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addSeparator();
	toolsMenu->addAction(searchAct);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);

	optionToolBar = addToolBar(tr("Tools"));
	optionToolBar->addAction(buildHexGridAct);
}

void MainWindow::createTopoGraphicsView()
{
  mainWidget->createWidget();

	// set the state of some QActions
	saveAct->setEnabled(true);
	saveAsAct->setEnabled(true);
	closeAct->setEnabled(true);
}

bool MainWindow::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) 
	{
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);
	// save the topology to a .jpg file
	QPixmap savePixmap = mainWidget->getGraphicsView()->saveScene();	// render the scene into a QPixmap object
	DataIO::savePixmap(savePixmap, fileName);
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	setWindowModified(false);

	QString shownName;
	if (curFile.isEmpty())
		shownName = "untitled.png";
	else
		shownName = strippedName(curFile);

	setWindowTitle(tr("Micro Circulation Software"));
	// setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}


QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

/*!
\brief Build up the hexagonal grid
*/
void MainWindow::buildHexGrid()
{
	/*if (topoGraphicsView != NULL)
	{
		topoGraphicsView->locateNodeItems();
	}*/
}

/*!
\brief Search the nodes or segments according to the number
*/
void MainWindow::searchItems()
{
	SearchDlg *searchDlg = new SearchDlg(this);
	searchDlg->exec();
}

void MainWindow::importPara()
{
  QString paraFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("pra"));
  DataIO::loadParaData(QTextStream(&paraFileName));
}

/*!
\brief Close the current Topology
*/
void MainWindow::closeTop()
{
	// clear the ResManager
	ResManager::unloadData();

	//// delete the topoGraphicsView
	//if(topoGraphicsView != NULL)
	//{
	//	delete topoGraphicsView;
	//	topoGraphicsView = NULL;
	//}

	// set the states of some QActions
  saveAct->setDisabled(true);
  saveAsAct->setDisabled(true);
  closeAct->setDisabled(true);
  buildHexGridAct->setDisabled(true);
}
