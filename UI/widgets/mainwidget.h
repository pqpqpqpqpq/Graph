#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class TopoGraphicsView;
class QHBoxLayout;
class QGridLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class EdgeItem;

class MainWidget : public QWidget
{
  Q_OBJECT

public:
  MainWidget(QWidget *parent = 0);
  ~MainWidget();

  void createWidget();
  TopoGraphicsView *getGraphicsView() { return graphicsView; }

private slots:
  void showSegmentInfo(EdgeItem *edgeItem);

private:
  TopoGraphicsView *graphicsView;
  QLabel *segNameLbl; QLineEdit *segNameEdit;
  QLabel *segIdLbl; QLineEdit *segIdEdit;
  QLabel *fromLbl; QLineEdit *fromEdit;
  QLabel *toLbl; QLineEdit *toEdit;
  QLabel *diamLbl; QLineEdit *diamEdit;
  QLabel *lenLbl; QLineEdit *lenEdit;
  QLabel *viscLbl; QLineEdit *viscEdit;
  QLabel *pressLbl; QLineEdit *pressEdit;
  QLabel *velLbl; QLineEdit *velEdit;
  QLabel *flowLbl; QLineEdit *flowEdit;

  QWidget *infoWidget;
  QHBoxLayout *mainLayout;
  QVBoxLayout *infoLayout;
  QGridLayout *paraLayout;
};

#endif
