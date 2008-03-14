#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsItemGroup>

#include "ui_window.h"

#include "Scene.h"

class ViewWindow : public QWidget, public Ui::PrototypeForm
{
	Q_OBJECT
	
public:
	ViewWindow(Scene *s);
	virtual ~ViewWindow();

private:
	Scene *scene;
	QList<QGraphicsItemGroup *> groupList;
	void scaleView(qreal scaleFactor);
	
private slots:
	void zoomMinus();
	void zoomPlus();
	void makeGroup();
	void destroyGroup();
};
#endif
