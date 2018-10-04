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
	m_amplitudes(new QLineSeries)
{
	ui->setupUi(this);
	//m_amplitudes->setUseOpenGL(true);
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
	setupGraph();
	setupCustomChart();
	connect(ui->pointableChart, &PointableChartView::pointedAt,
			[&](const QPointF &point){
		int x = point.x();
		if(x > 0 && x < bufSize){
			ui->xValLine->setText(QString::number(x*M_PI*2/bufSize));
			ui->yValLine->setText(QString::number(m_buffer[x].y()));
		}


	});
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setupGraph(){

	if (m_buffer.isEmpty()) {
		m_buffer.reserve(bufSize);
		for (int i = 0; i < bufSize; ++i)
			m_buffer.append(QPointF(i, 0));
	}
	double inc = M_PI/bufSize;
	double val = 0;
	double R=1000;
	double C=1e-6;
	for(int i=0;i<bufSize;i++, val+=inc)
		m_buffer[i].setY( 1/(1+2.0*i*R*C));

	m_amplitudes->replace(m_buffer);
}

void MainWindow::setupCustomChart(){
	auto m_chart = ui->pointableChart->chart();


	//m_amplitudes->setUseOpenGL(true);
	//m_chart->addSeries(m_amplitudes);
	QCategoryAxis *axisX = new QCategoryAxis;
	axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
	axisX->setRange(0,bufSize);

	axisX->append("0", 0);
	axisX->append("Pi/2", bufSize/4);
	axisX->append("Pi", bufSize/2);
	axisX->append("3*Pi/2", 3*bufSize/4);
	axisX->append("2*Pi", bufSize);


	axisX->setLabelFormat("%g");
	axisX->setTitleText("Phase");
	QValueAxis *axisY = new QValueAxis;
	axisY->setRange(0, 1.0);
	axisY->setTitleText("Gain");
	m_chart->addSeries(m_amplitudes);
	m_chart->setAxisX(axisX, m_amplitudes);
	m_chart->setAxisY(axisY, m_amplitudes);
	m_chart->legend()->hide();
	m_chart->setTitle("RC response" );

}
