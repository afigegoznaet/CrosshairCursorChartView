#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace Ui {
	class MainWindow;
}

class PointableChartView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
    void setupCustomChart(PointableChartView *rcChart);
	void setupGraph();

private:
	Ui::MainWindow *ui;
	QLineSeries *m_amplitudes ;
	QVector<QPointF> m_buffer;
};

#endif // MAINWINDOW_HPP
