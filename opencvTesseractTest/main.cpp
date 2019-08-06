#include <QCoreApplication>
#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include <tesseract/baseapi.h>      // tesseract提供的关于C++的接口
#include <tesseract/strngs.h>
//#include <bits/ios_base.h>
#include <allheaders.h>
//#include <capi.h>

#include <QDebug>

using namespace cv;

QString picToWord(const QString &path);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //namedWindow( "src", WINDOW_AUTOSIZE );
//        Mat src1 = imread( "/home/wxy/Lena.bmp" );
//        while(1){
//            imshow( "src", src1 );
//            char c =  waitKey(30);
//            if( 27==c )
//                return 0;
//        }

        qDebug()<<picToWord("/home/wxy/word.jpg");

    return a.exec();
}

QString picToWord(const QString &path)
{
    char *outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "chi_sim"))//chi_sim which is Chinese/eng
    {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    //QByteArray ba=fileNames.at(0).toLatin1();
    // Open input image with leptonica library
    //qDebug()<<ba;
    std::string str = path.toStdString();
    const char* ch = str.c_str();
    //qDebug()<<ch;
    Pix *image = pixRead(ch); //absolute path of file //ba.data()
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);
    return outText;
}
