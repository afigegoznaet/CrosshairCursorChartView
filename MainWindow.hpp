#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include "PointableChartView.hpp"

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace Ui {
	class MainWindow;
}



class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	void setupCustomChart(PointableChartView *rcChart, QVector<QPointF>& buffer, QLineSeries * amplitudes, CHART_TYPE type);

private:
	Ui::MainWindow *ui;
	QLineSeries *linear_chart_amplitudes, *log_chart_amplitudes, *logInfo_chart_amplitudes;
	QVector<QPointF> linear_chart_buffer, log_chart_buffer, logInfo_chart_buffer;
};

#endif // MAINWINDOW_HPP
