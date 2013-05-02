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


#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <QDebug>
#include <QPointF>
#include <QPalette>

#include <cmath>
#include <ctime>

#include "fumwidget.h"
#include "ball.h"

static const int MAX_BALLS = 2000;

FUMWidget::FUMWidget(QWidget *parent)
    : QWidget(parent),
      m_clock(0),
      m_vertScale(1),
      m_span(0),
      m_ballList(0)
 {
     // Cosmetics
     setMinimumSize(QSize(200,200));

     // Initialize main clock
     m_time = new QTime();
     m_time->start();

     // Set up refresh timer
     m_frameTick = new QTimer();
     connect(m_frameTick, SIGNAL(timeout()), this, SLOT(refreshPositions()));
     m_frameTick->start(30);

     // Initialize ball and impacts list
     m_impactList = new QList<QPointF>;

     resetBalls();
     qsrand(time(0));
 }

qreal FUMWidget::getTime() {
    return s_timeRatio * m_time->elapsed();
}

void FUMWidget::resetBalls() {
    qreal t = getTime();
    if (m_ballList) {
        qDeleteAll(*m_ballList);
        m_ballList->clear();
    } else {
        m_ballList = new QList<Ball*>;
    }

     for (int i=0; i<MAX_BALLS; i++) {
	 *m_ballList << new Ball(QPointF ((qreal(qrand())*1./RAND_MAX)*0.1+0.5,(qreal(qrand())*1./RAND_MAX)*1),
                             QPointF ((qreal(qrand())*1./RAND_MAX)*0.3+0.4,0),
                             t);
     }

     m_impactList->clear();
}

void FUMWidget::setVertScale(qreal value){
    m_vertScale=value;
}

void FUMWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor ballColor = QColor(Qt::blue);
    ballColor.setAlphaF(0.3);
    painter.setBrush(ballColor);
    painter.setPen(Qt::transparent);
    foreach (Ball* ball, (*m_ballList)) {
	painter.drawEllipse(QPoint(width()*(ball->pos(m_clock).y()),
				   height()*(1-m_vertScale*(1-ball->pos(m_clock).x())))
			    ,RAD
			    ,RAD);
    }

    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);

    painter.drawRect(0,height()*(1-m_vertScale*(1-wPos(m_clock))),width(),THK);
}

qreal FUMWidget::wPos(qreal t) {
    t= (t - int (t))-0.5;
    return 0.95-qMax(m_span,0.) + m_span * (4*t*t);
}

qreal FUMWidget::wVel(qreal t) {
    t= (t - int (t))-0.5;
    return m_span * 8*t;
}

void FUMWidget::refreshPositions() {
    qreal t = getTime();

    foreach (Ball* ball,  *m_ballList) {
        // Wrap around vertical

	// Observe that we could as well move the initial condition up by 1;
	// however in the long run this would cause rounding errors, so why not
	// re-setting the initial position

	if (ball->pos(t).y() > 1) {
	    ball->setInitialPos(ball->pos(t) - QPointF(0,1));
	    ball->setInitialTime(t);
	} else if (ball->pos(t).y() < 0) {
	    ball->setInitialPos(ball->pos(t) + QPointF(0,1));
	    ball->setInitialTime(t);
	}

	const int MAXIMUM_BOUNCES_BEFORE_BAILOUT = 50;
	int bounces = 0;
	bool hasHitMovingWall = true;

	while (hasHitMovingWall && (bounces < MAXIMUM_BOUNCES_BEFORE_BAILOUT)) {
	    hasHitMovingWall = false;
	    bounces++;
/*	    // Bounce with fixed wall
            if (ball->pos(t).x() < 0) {
		QPointF ballPos = ball->pos(t);
		QPointF ballVel = ball->vel(t);
		ballPos.setX(-ballPos.x());
		ballVel.setX(-ballVel.x());
		ball->setInitialPos(ballPos);
		ball->setInitialVel(ballVel);
		ball->setInitialTime(t);
	    }
*/
	    // Bounce with moving wall
	    if (ball->pos(t).x() > wPos(t)) {
		// A bounce has happened at some time between m_clock and t;
		// find “exactly” when by bisecting the interval;
		const int BISECTION_STEPS = 32;
		qreal t0 = t-1.5*(t-m_clock); //just to be extra-sure
		qreal t1 = t;
		for (int i=0; i<BISECTION_STEPS; i++) {
		    qreal tm = (t0+t1)*.5;
		    if (ball->pos(tm).x() > wPos(tm)) {
			t1 = tm;
		    } else {
			t0 = tm;
		    }
		}
		qreal tm = t0;//(t0+t1)*.5;
		// tm is the “exact” time of collision
		QPointF ballVel = ball->vel(tm);
		QPointF ballPos = ball->pos(tm);
		if (bounces == 1 || (ballVel.x() >= wVel(tm))) {
		    ball->setInitialPos(ballPos);
		    ballVel.setX(-ballVel.x() + 2*wVel(tm));
		    ball->setInitialVel(ballVel);
		    ball->setInitialTime(tm);
		    if ((qreal(qrand())*1./RAND_MAX) < 0.3) {
			*m_impactList << QPointF((tm - int(tm)),-ballVel.x()+wVel(tm));
		    }
		    hasHitMovingWall = true;
		}
	    }

	}
	if (bounces> 10) qDebug() << "bailout";
    }
    m_clock = t;
    update();
}

void FUMWidget::setSpan(qreal span){
    m_span = span;
    resetBalls();
}
