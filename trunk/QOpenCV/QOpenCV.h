/***************************************************************************
 *   Copyright (C) 2009 by Ariel Molina                                    *
 *   ariel@zarzamora.com.mx                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <opencv/cv.h>

class QOpenCVWidget : public QWidget {
	Q_OBJECT
	private:
		QImage         image;
		IplImage*      cvimage;
		QVector<QRgb>  colors;
		QPoint         warp[4];
		QPoint         roi[2];
		bool           drawRoi;
		bool           drawWarp;
		QPen           warpPen;
		
		void mouseMoveEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent * /* event */);
    public:
		QOpenCVWidget(QWidget *parent = 0);
		~QOpenCVWidget(void);
		/**
		 *       This is the important one. Inset an IplImage into the widget
		 * @param  img A typical IplImage pointer, be it 3 channel or 1 channel, only 8 bit per channel supported by now.
		 */
		void putImage(IplImage *);
		void getRoi(int& x1, int& y1, int& x2, int& y2);
		void setRoi(int  x1, int  y1, int  x2, int  y2);
		void getWarpPoints(int& x1, int& y1, int& x2, int& y2, int& x3, int& y3, int& x4, int& y4);
		void setWarpPoints(int  x1, int y1,  int  x2, int  y2, int  x3, int  y3, int  x4, int  y4);
		void setWarpPoints(QPoint p1, QPoint p2, QPoint p3, QPoint p4){
			warp[0]=p1;
			warp[1]=p2;
			warp[2]=p3;
			warp[3]=p4;
		}
		void setWarpPoint(int idx, QPoint pt){ 
			if (idx<4) 
				warp[idx]=pt;
		}
	signals:
		void mouseDown(QMouseEvent *event);
		void mouseUp(QMouseEvent *event);
		void mouseMove(QMouseEvent *event);
};
#endif
