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

#include <cmath>

#include "histowidget.h"

HistoWidget::HistoWidget(QList<Ball*>* ballList, QWidget *parent)
    : QWidget(parent),
      m_ballList(ballList),
      m_scale(10),
      m_binWidth(0.05),
      m_minVel(0),
      m_maxVel(0) {

    setMinimumSize(QSize(400,100));

    // Create refresh timer
    QTimer* frameTick = new QTimer();
    connect(frameTick, SIGNAL(timeout()), this, SLOT(update()));
    frameTick->start(200);
 }

void HistoWidget::setScale(qreal scale) {
    m_scale = scale;
}

void HistoWidget::setBinWidth(qreal width) {
    m_binWidth = width;
}
void HistoWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setBrush(Qt::black);

    //Fill bins
    const int BIN_PIXEL_WIDTH = 2;
    const int BIN_PIXEL_GAP = 2;
    int binNumber = width()/(BIN_PIXEL_WIDTH+BIN_PIXEL_GAP);
    int *bin = new int[binNumber];
    for (int i=0; i<binNumber; i++) {
	bin[i] = 0;
    }

    m_minVel=1e10; // ugh
    m_maxVel=0;

    qreal avgVel = 0;
    QList<qreal> velList;
    foreach (Ball *ball, *m_ballList) {
        qreal vel = qAbs(ball->initialVel().x());
        velList << vel;
        avgVel += vel;
        if (vel < m_minVel) {
            m_minVel = vel;
        }
        if (vel > m_maxVel) {
            m_maxVel = vel;
        }
	int binNo = vel/m_binWidth;
	if (binNo < binNumber) {
	    bin[binNo]++;
	}
    }

    qSort(velList);
    m_medianVel = velList[velList.count()/2];

    m_avgVel = avgVel * (1./m_ballList->count());

    QColor thickLines = QColor(Qt::black);
    QColor thinLines = QColor(Qt::black);
    thickLines.setAlphaF(0.7);

    thinLines.setAlphaF(0.3*exp(-20./m_scale));

    QFontInfo fontInfo = painter.fontInfo();
    int pointSize = fontInfo.pointSize()*0.7;

    QFont font = painter.font();
    font.setPointSize(pointSize);
    painter.setFont(font);
    QFontMetrics fm = QFontMetrics(font);
    int fontHeight = fm.ascent()+1;
    int labelWidth = fm.width("1.00 ");
    painter.setPen(thickLines);

    int labelSkip = int (fontHeight / (0.05*m_scale*height())) + 1;
    int histoLeft = labelWidth;
    int histoBottom = height() - 1.5*fontHeight;

    painter.drawLine(histoLeft, 0, histoLeft, histoBottom);
    for (int i=0; i<20; i++) {
	int y =  histoBottom - i*0.05*m_scale*height() -1;
	painter.drawLine(histoLeft, y,width(),y);
        if ((i % labelSkip) == 0) {
            painter.drawLine(histoLeft-2, y,histoLeft,y);
            painter.drawText(0, y+fontHeight/2, QString::number(0.05*i, 'f', 2));
        }
    }

    painter.setPen(thinLines);
    for (int i=0; i<100; i++) {
	int y =  histoBottom - i*0.01*m_scale*height() -1;
	painter.drawLine(histoLeft,y,width(),y);
    }

    for (int i=0; i<binNumber; i++) {
	int colHeight = bin[i]*1./m_ballList->count()*m_scale*histoBottom;
	painter.drawRect(histoLeft+i*(BIN_PIXEL_WIDTH+BIN_PIXEL_GAP),histoBottom - colHeight ,BIN_PIXEL_WIDTH,colHeight);
    }

    emit statisticsChanged();
}
