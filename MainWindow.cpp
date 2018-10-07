#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtMath>
#include "PointableChartView.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	linear_chart_amplitudes(new QLineSeries),
	log_chart_amplitudes(new QLineSeries),
	logInfo_chart_amplitudes(new QLineSeries)
{
	ui->setupUi(this);
	linear_chart_amplitudes->setUseOpenGL(true);
	log_chart_amplitudes->setUseOpenGL(true);
	logInfo_chart_amplitudes->setUseOpenGL(true);
	/**
	 *
	R=1000;
	C=1e-6;
	f=1:0.1:10000;
	w=2.*f.*pi;
	g=1./(1+w.*R.*C);
	close all
	plot(f,g);
	*/

	ui->xValLine->setReadOnly(true);
	ui->yValLine->setReadOnly(true);

	PointableChartView* linearChart = new PointableChartView(linear_chart_buffer, LINEAR, this);
	PointableChartView* logChart = new PointableChartView(log_chart_buffer, LOGARITHMIC, this);
	PointableChartView* logInfoChart = new PointableChartView(logInfo_chart_buffer, LOG_INFO, this);

	ui->tabWidget->addTab(linearChart, "Linear RC Chart");
	ui->tabWidget->addTab(logChart, "Logarithmic RC Chart");
	ui->tabWidget->addTab(logInfoChart, "Logarithmic RC Chart with Linear base info");

	setupCustomChart(linearChart, linear_chart_buffer, linear_chart_amplitudes, LINEAR);
	setupCustomChart(logChart, log_chart_buffer, log_chart_amplitudes, LOGARITHMIC);
	setupCustomChart(logInfoChart, logInfo_chart_buffer, logInfo_chart_amplitudes, LOG_INFO);

    //ui->pointableChart->grabMouse();
    //ui->pointableChart->setUpdatesEnabled(true);

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::setupCustomChart(PointableChartView* rcChart,QVector<QPointF>& buffer, QLineSeries *amplitudes, CHART_TYPE type){

	if (buffer.isEmpty()) {
		buffer.reserve(bufSize);
		for (int i = 0; i < bufSize; ++i)
			buffer.append(QPointF(i, 0));
	}
	//double inc = M_PI/bufSize;
	//double val = 0;
	double R=1000;
	double C=1e-6;
	for(int i=0;i<bufSize;i++)
		if(type == LINEAR)
			buffer[i].setY( 1/(1+2.0*i*M_PI*R*C));
		else
			buffer[i].setY( log10( 1/(1+2.0*i*M_PI*R*C)));

	amplitudes->replace(buffer);

	auto m_chart = rcChart->chart();

	QValueAxis *axisX = new QValueAxis;
	axisX->setRange(0, 10000);

	axisX->setLabelFormat("%g");
	axisX->setTitleText("Phase");
	QValueAxis *axisY = new QValueAxis;

	double logRange = log10( 1/(1+2.0*9999*M_PI*R*C));

	switch (type) {
		case LOGARITHMIC:
			m_chart->setTitle("Logarithmic RC response" );
			axisY->setRange(logRange, 0);
			rcChart->setMaxRange(logRange);
			break;
		case LOG_INFO:
			m_chart->setTitle("Logarithmic with linear info RC response" );
			axisY->setRange(logRange, 0);
			rcChart->setMaxRange(logRange);
			break;
		default:
			m_chart->setTitle("Linear RC response" );
			axisY->setRange(0, 1.0);
	}

	axisY->setTitleText("Gain");
	m_chart->addSeries(amplitudes);
	m_chart->setAxisX(axisX, amplitudes);
	m_chart->setAxisY(axisY, amplitudes);
	m_chart->legend()->hide();


	connect(rcChart, &PointableChartView::pointedAt,
			[&](const QPointF &point){
		int x = static_cast<int>(point.x());
		if(x > -1 && x < bufSize){
			ui->xValLine->setText(QString::number(x));
			ui->yValLine->setText(QString::number(buffer[x].y()));
		}
	});

}
