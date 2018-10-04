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

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	void setupCustomChart();
	void setupGraph();

private:
	Ui::MainWindow *ui;
	QLineSeries *m_amplitudes ;
	const int bufSize = 10000;
	QVector<QPointF> m_buffer;
};

#endif // MAINWINDOW_HPP
