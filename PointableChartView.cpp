#include "PointableChartView.hpp"
#include <QtCharts/QChartView>
#include <QDebug>

void PointableChartView::mouseMoveEvent(QMouseEvent *event) {
	QChartView::mouseMoveEvent(event);
	//qDebug()<<event->pos();
	auto point = mapFromGlobal(event->pos());
	auto pointF = chart()->mapToValue(point,chart()->series().at(0));
	emit pointedAt(pointF);
	update();
}

void PointableChartView::drawForeground(QPainter *painter, const QRectF &rect){
	QRectF SceneRect = chart()->plotArea();
	painter->setClipRect(SceneRect);
	auto pos = mapFromGlobal(QCursor::pos());
	auto pointF = chart()->mapToValue(pos,chart()->series().at(0));
	if(pointF.x()<0 || pointF.x()>= 10000)
		return;
	painter->setPen(QPen(Qt::black, 1));
	painter->drawLine(SceneRect.left(), pos.y(), SceneRect.right(), pos.y());
	painter->drawLine(pos.x(), SceneRect.top(), pos.x(), SceneRect.bottom());
}
