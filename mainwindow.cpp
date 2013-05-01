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
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "mainwindow.h"
#include "fum.h"
#include "histogram.h"
#include "impactwidget.h"

MainWindow::MainWindow(QWidget *parent)
     : QWidget(parent)
 {
     setWindowTitle("Fermi acceleration");
     FUM *fum = new FUM();
     Histogram *histo = new Histogram(fum->ballList());
     ImpactWidget *impact = new ImpactWidget(fum->impactList());

     QSplitter *hSplitter = new QSplitter();
     hSplitter->addWidget(fum);
     hSplitter->addWidget(impact);

     QSplitter *vSplitter = new QSplitter(Qt::Vertical);
     vSplitter->addWidget(hSplitter);
     vSplitter->addWidget(histo);

     QVBoxLayout *layout = new QVBoxLayout();
     layout->addWidget(vSplitter);
     setLayout(layout);
 }
