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

#include "ball.h"

Ball::Ball(QPointF pos, QPointF vel,qreal t)
          : m_pos0(pos),
	    m_vel0(vel),
	    m_t0(t) {
}

void Ball::setInitialPos(QPointF pos) {
    m_pos0 = pos;
}
void Ball::setInitialVel(QPointF vel) {
    m_vel0 = vel;
}
void Ball::setInitialTime(qreal t) {
    m_t0 = t;
}

QPointF Ball::pos(qreal t) {
    return m_pos0 + m_vel0*(t-m_t0) +0.5*QPointF(s_gravity,0)*(t-m_t0)*(t-m_t0);
}

QPointF Ball::vel(qreal t) {
    return m_vel0 + QPointF(s_gravity,0)*(t-m_t0);
}

QPointF Ball::initialVel() {
    return m_vel0;
}
