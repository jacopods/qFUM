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
#include "ball.h"

#ifndef FUMWIDGET_H
#define FUMWIDGET_H

#define RAD 2
#define THK 5

class FUMWidget : public QWidget {
    Q_OBJECT;
 public:
    FUMWidget(QWidget *parent = 0);
    QList<Ball*>* ballList() {return m_ballList;}
    QList<QPointF>* impactList() {return m_impactList;}

 public slots:
     void resetBalls();

 protected:
    virtual void paintEvent(QPaintEvent *event);

public slots:
    void setVertScale(qreal);
    void setSpan(qreal);

protected slots:
    void refreshPositions();

 private:
    qreal wPos(qreal);
    qreal wVel(qreal);

    qreal getTime();

    static const qreal s_timeRatio = 0.001;

    QList<Ball*>* m_ballList;
    QList<QPointF>* m_impactList;
    qreal m_clock;
    qreal m_vertScale;
    qreal m_span;
    QTimer* m_frameTick;
    QTime* m_time;
};

#endif
