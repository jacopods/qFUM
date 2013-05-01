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
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleValidator>
#include <cmath>

#include "fumwidget.h"
#include "fum.h"

FUM::FUM(QWidget *parent)
     : QWidget(parent)
 {
     m_fum = new FUMWidget();


     QHBoxLayout *curvatureLayout = new QHBoxLayout();
     QLabel *curvText = new QLabel("Plate acceleration (g = 1)");
     m_curvEdit = new QLineEdit();
     connect(m_curvEdit, SIGNAL(returnPressed()), this, SLOT(changeCurvature()));
     QPushButton *setCurvature = new QPushButton("Reset");
     connect(setCurvature,SIGNAL(clicked()),this,SLOT(changeCurvature()));

     curvText->setBuddy(m_curvEdit);
     m_curvEdit->setValidator(new QDoubleValidator(-10.,10.,4,m_curvEdit));

     curvatureLayout->addWidget(curvText);
     curvatureLayout->addWidget(m_curvEdit);
     curvatureLayout->addWidget(setCurvature);

     QSlider *vertScale = new QSlider();
     vertScale->setMinimum(0);
     vertScale->setMaximum(100);
     vertScale->setValue(50);
     connect(vertScale,SIGNAL(valueChanged(int)),this,SLOT(changeVertScale(int)));

     QVBoxLayout *layout = new QVBoxLayout();

     QHBoxLayout *hlayout = new QHBoxLayout();

     hlayout->addWidget(m_fum);
     hlayout->addWidget(vertScale);
     layout->addLayout(curvatureLayout);
     layout->addLayout(hlayout);

     setLayout(layout);
 }

void FUM::changeVertScale(int value) {
    m_fum->setVertScale(exp((value-50)*0.05));
}

void FUM::changeCurvature() {
    m_fum->setSpan(.125*m_curvEdit->text().toDouble());
}
