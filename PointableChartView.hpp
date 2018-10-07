#ifndef POINTABLECHARTVIEW_HPP
#define POINTABLECHARTVIEW_HPP
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>

static const int bufSize = 10000;

QT_CHARTS_USE_NAMESPACE

enum CHART_TYPE{LINEAR, LOGARITHMIC, LOG_INFO};

class PointableChartView : public QChartView
{
	Q_OBJECT
public:
	//PointableChartView();
	explicit PointableChartView(QVector<QPointF>& buffer, CHART_TYPE type, QWidget *parent = nullptr)
		: QChartView(parent), m_buffer(buffer), m_type(type){}
	//explicit PointableChartView(QChart *chart, QWidget *parent = nullptr);
	//s~PointableChartView();

	void setMaxRange(double range){maxRange = range;}
signals:
	void pointedAt(QPointF pt);
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void drawForeground(QPainter *painter, const QRectF &rect) override;
	QPointF pointF, pos;
	QVector<QPointF>& m_buffer;
	double maxRange = 1.0;
	CHART_TYPE m_type;
};

#endif // POINTABLECHARTVIEW_HPP
