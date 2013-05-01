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
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include "impactwidget.h"

ImpactWidget::ImpactWidget(QList<QPointF>* list, QWidget *parent)
    : QWidget(parent),
      m_pointList(list)
{
    setMinimumSize(QSize(100,200));
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    setPalette(palette);
    setAutoFillBackground(true);

    // Create refresh timer
    QTimer* frameTick = new QTimer();
    connect(frameTick, SIGNAL(timeout()), this, SLOT(update()));
    frameTick->start(500);
}

void ImpactWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QColor ballColor = QColor(Qt::white);
    ballColor.setAlphaF(0.4);
    painter.setPen(ballColor);

    foreach (QPointF p, *m_pointList) {
	painter.drawPoint(p.x()*width(),height()-height()*p.y()*0.3);
    }
}
