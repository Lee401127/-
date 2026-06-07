#include "widget.h"
#include <QApplication>
#include"openvideo.h"
#include"mainwidget.h"
#include"mainwidget1.h"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QList<QString>>("QList<QString>");
     qRegisterMetaType<Eld>("Eld");
    OpenVideo w;
   // Mainwidget w;
  //  MainWidget1 w;
    w.show();

    return a.exec();
}
