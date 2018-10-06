#include "PointableChartView.hpp"
#include <QtCharts/QChartView>
#include <QDebug>

void PointableChartView::mouseMoveEvent(QMouseEvent *event) {
	QChartView::mouseMoveEvent(event);
    //qDebug()<<event->pos();
	pos = mapFromParent(event->pos());
	pointF = chart()->mapToValue(pos,chart()->series().at(0));
	emit pointedAt(pointF);
    //invalidateScene(chart()->plotArea(), QGraphicsScene::ForegroundLayer);
	update();
    //repaint();
}

void PointableChartView::drawForeground(QPainter *painter, const QRectF &rect){
    QChartView::drawForeground(painter, rect);

	//auto pos = mapFromGlobal(QCursor::pos());
	//auto pointF = chart()->mapToValue(pos,chart()->series().at(0));
	if(pointF.x()<0 || pointF.x()>= bufSize)
		return;
	QRectF SceneRect = chart()->plotArea();
	painter->setClipRect(SceneRect);
	painter->setPen(QPen(Qt::black, 1));
	painter->drawLine(SceneRect.left(), pos.y(), SceneRect.right(), pos.y());
	painter->drawLine(pos.x(), SceneRect.top(), pos.x(), SceneRect.bottom());
}
