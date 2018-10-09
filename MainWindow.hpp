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
	QLineSeries *linearLinearAmplitudes, *linearXLogYAmplitudes, *logXLinearYAmplitudes, *logXLogYAmplitudes;
	QVector<QPointF> linearLinearChartBuffer, linearXLogYBuffer, logXLinearYBuffer, logXLogYBuffer;
};

#endif // MAINWINDOW_HPP
