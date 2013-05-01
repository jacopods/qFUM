/***************************************************************************
 *   Copyright 2013 by Jacopo De Simoi <desimoi@mat.uniroma2.it>           *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/


#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

#include <cmath>

#include "histogram.h"
#include "histowidget.h"

Histogram::Histogram(QList<Ball*>* ballList, QWidget *parent)
    : QWidget(parent) {

    m_histoWidget = new HistoWidget(ballList);
    QSlider* scaleSlider = new QSlider();
    QSlider* widthSlider = new QSlider(Qt::Horizontal);
    QLabel* title = new QLabel("Impact speed distribution");
    m_statisticsLabel = new QLabel();

    scaleSlider->setMinimum(0);
    scaleSlider->setMaximum(100);
    scaleSlider->setValue(9*2);
    scaleSlider->setTickPosition(QSlider::TicksRight);
    connect(scaleSlider,SIGNAL(valueChanged(int)),this,SLOT(changeScale(int)));

    widthSlider->setMinimum(0);
    widthSlider->setMaximum(100);
    widthSlider->setValue(50);
    connect(widthSlider,SIGNAL(valueChanged(int)),this,SLOT(changeBinWidth(int)));

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(title);
    vlayout->addWidget(m_statisticsLabel);
    connect(m_histoWidget, SIGNAL(statisticsChanged()), this, SLOT(refreshStatistics()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_histoWidget);
    layout->addWidget(scaleSlider);

    vlayout->addLayout(layout);
    vlayout->addWidget(widthSlider);
    setLayout(vlayout);
}

void Histogram::changeScale(int value) {
    m_histoWidget->setScale(1.+value*0.5);
}

void Histogram::changeBinWidth(int value) {
    m_histoWidget->setBinWidth(0.05*exp((value-50)*0.02));
}

void Histogram::refreshStatistics() {
    m_statisticsLabel->setText(QString("Min: ")+QString::number(m_histoWidget->minVel(), 'f', 2) +
                               QString(" - Max: ")+QString::number(m_histoWidget->maxVel(), 'f', 2) +
                               QString(" - Med: ")+QString::number(m_histoWidget->medianVel(), 'f', 2) +
                               QString(" - Avg: ")+QString::number(m_histoWidget->avgVel(), 'f', 2));
}
