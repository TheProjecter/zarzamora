# Zarzamora Tools for Machine Vision #
> Diverse tools are hosted here. All of them are small tools meant to make machine vision easier.

## Convolver Berry ##
> A tool to apply convolution filters for any image. Currently uses OpenCV. Very useful for teaching and for crafting kernels.

## QT OpenCV IplImage Widget ##

> A QT Widget for efficiently displaying an IplImage into a QT 4.x widget. Is directly based on QWidget, so it does not use any QLabel or QPixmaps, it paints directly onto a QWidget using a QPainter. If you just want to display an image is as easy as
```
 IplImage* img;
  ...
 image = new QOpenCVWidget;
 image.putImage(img);
```

> Get your fresh copy now from the downloads, or get the uber fresh by svn:
```
svn checkout http://zarzamora.googlecode.com/svn/trunk/QOpenCV QOpenCV  
```