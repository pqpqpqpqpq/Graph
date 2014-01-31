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
#include <QApplication>

#include "ui/widgets/mainwindow.h"
#include "resmanager.h"

/* Git commit Test 2 */
/* Add A */
int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(application);

  QApplication app(argc, argv);

  ResManager::initSettings();

  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
