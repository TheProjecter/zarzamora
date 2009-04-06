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
#include "QOpenCV.h"
QOpenCVWidget::QOpenCVWidget(QWidget *parent)
	:QWidget(parent), drawRoi(true), drawWarp(true){
	roi[1].setX(100);
	roi[1].setY(100);
	for (int i=0; i<256; i++)
		colors.append( qRgb(i,i,i) );
	QImage dummy(319, 239, QImage::Format_RGB32);
	image = dummy;
	for (int x = 0; x < 319; x ++)
		for (int y =0; y < 239; y++)
			image.setPixel(x,y, qRgb(254./319. * x, y, 254-y));
	cvimage=NULL;
	
	warpPen = QPen(QBrush (QColor(234, 184, 48)), (qreal)2.0, Qt::DashLine, Qt::FlatCap, Qt::BevelJoin);
}
QOpenCVWidget::~QOpenCVWidget(void){
	if (cvimage)
		cvReleaseImage(&cvimage);
}
void QOpenCVWidget::putImage(IplImage *img){
	int cvIndex, cvLineStart;
	bool alloc=false;
	cvimage = img;
	switch (cvimage->depth) {
		case IPL_DEPTH_8U:
			switch (cvimage->nChannels) {
				case 3:
					if ( (cvimage->width != image.width()) || (cvimage->height != image.height()) ) {
						QImage temp(cvimage->width, cvimage->height, QImage::Format_RGB32);
						image = temp;
					}
					cvIndex = 0; cvLineStart = 0;
					for (int y = 0; y < cvimage->height; y++) {
						unsigned char red,green,blue;
						cvIndex = cvLineStart;
						for (int x = 0; x < cvimage->width; x++) {// DO it
							red = cvimage->imageData[cvIndex+2];
							green = cvimage->imageData[cvIndex+1];
							blue = cvimage->imageData[cvIndex+0];
							image.setPixel(x,y,qRgb(red, green, blue));
							cvIndex += 3;
						}
						cvLineStart += cvimage->widthStep;
					}
					break;
				case 1:
					if ( (cvimage->width != image.width()) || (cvimage->height != image.height()) ) {
						QImage temp((uchar*) cvimage->imageData, cvimage->width, cvimage->height, QImage::Format_Indexed8);
						temp.setNumColors(256);
						temp.setColorTable(colors);
						image = temp;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	if (alloc){
		cvReleaseImage(&cvimage);
	}
	this->update(); // Queue a paint update to the widget
}
void QOpenCVWidget::mouseMoveEvent(QMouseEvent *event){
	emit mouseMove(event);
}
void QOpenCVWidget::mousePressEvent(QMouseEvent *event){
	emit mouseDown(event);
}
void QOpenCVWidget::mouseReleaseEvent(QMouseEvent *event){
	emit mouseUp(event);
}
void QOpenCVWidget::paintEvent(QPaintEvent * /* event */){
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), image);
	painter.setPen( warpPen );
	painter.setRenderHint(QPainter::Antialiasing);
	if (drawWarp)
		painter.drawPolygon(warp, 4);
}
void QOpenCVWidget::setWarpPoints(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	warp[0].setX(x1);
	warp[0].setY(y1);
	warp[1].setX(x2);
	warp[1].setY(y2);
	warp[2].setX(x3);
	warp[2].setY(y3);
	warp[3].setX(x4);
	warp[3].setY(y4);
}
void QOpenCVWidget::getWarpPoints(int& x1, int& y1, int& x2, int& y2, int& x3, int& y3, int& x4, int& y4){
	x1 = warp[0].x();
	y1 = warp[0].y();
	x2 = warp[1].x();
	y2 = warp[1].y();
	x3 = warp[2].x();
	y3 = warp[2].y();
	x4 = warp[3].x();
	y4 = warp[3].y();
}