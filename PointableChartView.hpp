#ifndef POINTABLECHARTVIEW_HPP
#define POINTABLECHARTVIEW_HPP
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>

static const int bufSize = 10000;

QT_CHARTS_USE_NAMESPACE

class PointableChartView : public QChartView
{
	Q_OBJECT
public:
	//PointableChartView();
	explicit PointableChartView(QWidget *parent = nullptr) : QChartView(parent){}
	//explicit PointableChartView(QChart *chart, QWidget *parent = nullptr);
	//s~PointableChartView();
signals:
	void pointedAt(QPointF pt);
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void drawForeground(QPainter *painter, const QRectF &rect) override;
};

#endif // POINTABLECHARTVIEW_HPP
