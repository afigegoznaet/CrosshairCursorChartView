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
	if(pointF.x()< 0 || pointF.x()>= bufSize)
		return;
	QRectF SceneRect = chart()->plotArea();
	painter->setClipRect(SceneRect);
	painter->setPen(QPen(Qt::black, 1));
	double y;
	if(maxRange<0)
		y = SceneRect.top()+(1-(maxRange - m_buffer[pointF.x()].y() )/maxRange) * SceneRect.height();
	else
		y = SceneRect.top()+( maxRange - m_buffer[pointF.x()].y() ) * SceneRect.height();
	painter->drawLine(SceneRect.left(), y, SceneRect.right(), y);
	painter->drawLine(pos.x(), SceneRect.top(), pos.x(), SceneRect.bottom());


	auto val = m_buffer[pointF.x()].y();
	if(LOG_INFO == m_type)
		val = pow(10, val);
	painter->drawText( SceneRect.left(), y, QString::number(val));

}
