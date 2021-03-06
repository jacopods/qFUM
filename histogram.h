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
#include <QSlider>

#include "histowidget.h"

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

class QLabel;

class Histogram : public QWidget {
    Q_OBJECT;
 public:
    Histogram(QList<Ball*>* ballList, QWidget *parent = 0);

 protected slots:
     void changeScale(int);
     void changeBinWidth(int);
     void refreshStatistics();

 private:
    HistoWidget *m_histoWidget;
    QLabel *m_statisticsLabel;
};

#endif
