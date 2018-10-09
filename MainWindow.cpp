#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QCategoryAxis>
#include "PointableChartView.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	linearLinearAmplitudes(new QLineSeries),
	linearXLogYAmplitudes(new QLineSeries),
	logXLinearYAmplitudes(new QLineSeries),
	logXLogYAmplitudes(new QLineSeries)
{
	ui->setupUi(this);
	linearLinearAmplitudes->setUseOpenGL(true);
	linearXLogYAmplitudes->setUseOpenGL(true);
	logXLinearYAmplitudes->setUseOpenGL(true);
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

	PointableChartView* linearLinearChart = new PointableChartView(linearLinearChartBuffer, LINEAR, this);
	PointableChartView* linearXLogYChart = new PointableChartView(linearXLogYBuffer, LOGY, this);
	PointableChartView* logXLinearYChart = new PointableChartView(logXLinearYBuffer, LOGX, this);
	PointableChartView* logXLogYChart = new PointableChartView(logXLogYBuffer, LOGX_LOGY, this);

	ui->tabWidget->addTab(linearLinearChart, "Linear - Linear");
	ui->tabWidget->addTab(linearXLogYChart, "Linear X - Log10 Y");
	ui->tabWidget->addTab(logXLinearYChart, "Log10 X - Linear Y");
	ui->tabWidget->addTab(logXLogYChart, "Log10 X - Log10 Y");

	setupCustomChart(linearLinearChart, linearLinearChartBuffer, linearLinearAmplitudes, LINEAR);
	setupCustomChart(linearXLogYChart, linearXLogYBuffer, linearXLogYAmplitudes, LOGY);
	setupCustomChart(logXLinearYChart, logXLinearYBuffer, logXLinearYAmplitudes, LOGX);
	setupCustomChart(logXLogYChart, logXLogYBuffer, logXLogYAmplitudes, LOGX_LOGY);

    //ui->pointableChart->grabMouse();
    //ui->pointableChart->setUpdatesEnabled(true);

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::setupCustomChart(PointableChartView* rcChart,QVector<QPointF>& buffer, QLineSeries *amplitudes, CHART_TYPE type){

	double R=1000;
	double C=1e-6;
	if (buffer.isEmpty()) {
		buffer.reserve(bufSize);
		for (int i = 1; i <= bufSize; ++i)
			//if(type == LINEAR || type == LOGY)
				buffer.append(QPointF(i, 1/(1+2.0*i*M_PI*R*C)));
			//else
				//buffer.append(QPointF(log10(i), 0));
	}

	//double inc = M_PI/bufSize;
	//double val = 0;

	//for(int i=0;i<bufSize;i++)
		//if(type == LINEAR || type == LOGY)
			//buffer[i].setY( 1/(1+2.0*(i+1)*M_PI*R*C));
		//else
			//buffer[i].setY( log10( 1/(1+2.0*log10(i)*M_PI*R*C)));


	amplitudes->replace(buffer);

	auto m_chart = rcChart->chart();

	QValueAxis *axisX = new QValueAxis;
	QLogValueAxis *logAxisX = new QLogValueAxis;
	axisX->setRange(1, 10000);
	logAxisX->setRange(1, 10000);

	axisX->setLabelFormat("%g");
	logAxisX->setLabelFormat("%g");
	axisX->setTitleText("Phase");
	logAxisX->setTitleText("Phase");
	axisX->setMinorTickCount(-1);
	logAxisX->setMinorTickCount(-1);

	QValueAxis *axisY = new QValueAxis;
	QLogValueAxis *logAxisY = new QLogValueAxis;
	axisY->setTitleText("Gain");
	logAxisY->setTitleText("Gain");
	logAxisY->setBase(10);

	double logRange = 0.011;//log10( 1/(1+2.0*9999*M_PI*R*C));
	axisY->setRange(0, 1.0);
	logAxisY->setRange(0.011, 1.0);
	logAxisY->setMinorTickCount(-1);

	//logAxisY->setMin(0.01);
	//logAxisY->setMax(1);

	m_chart->addSeries(amplitudes);

	switch (type) {
		case LOGY:
			m_chart->setTitle("Linear X - Linear Y" );
			rcChart->setMaxRange(log10(logRange));
			m_chart->setAxisX(axisX, amplitudes);
			m_chart->setAxisY(logAxisY, amplitudes);
			break;
		case LOGX:
			m_chart->setTitle("Linear X - Log10 Y" );
			//rcChart->setMaxRange(logRange);
			m_chart->setAxisX(logAxisX, amplitudes);
			m_chart->setAxisY(axisY, amplitudes);
			break;
		case LOGX_LOGY:
			m_chart->setTitle("Log10 X - Linear Y" );
			rcChart->setMaxRange(log10(logRange));
			m_chart->setAxisX(logAxisX, amplitudes);
			m_chart->setAxisY(logAxisY, amplitudes);
			break;
		default:
			m_chart->setTitle("Log10 X - Log10 Y" );
			m_chart->setAxisX(axisX, amplitudes);
			m_chart->setAxisY(axisY, amplitudes);
	}

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
