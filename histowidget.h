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
#include <fumwidget.h>

#ifndef HISTOWIDGET_H
#define HISTOWIDGET_H

class HistoWidget : public QWidget {
    Q_OBJECT;
 public:
    HistoWidget(QList<Ball*>* ballList, QWidget *parent = 0);
    void setScale(qreal);
    void setBinWidth(qreal);
    qreal minVel() {return m_minVel;}
    qreal maxVel() {return m_maxVel;}
    qreal avgVel() {return m_avgVel;}
    qreal medianVel() {return m_medianVel;}
signals:
    void statisticsChanged();

 protected:
    virtual void paintEvent(QPaintEvent *event);

 private:
    QList<Ball*>* m_ballList;
    QTimer* m_frameTick;
    qreal m_scale;
    qreal m_binWidth;

    qreal m_minVel;
    qreal m_maxVel;
    qreal m_avgVel;
    qreal m_medianVel;
};

#endif
