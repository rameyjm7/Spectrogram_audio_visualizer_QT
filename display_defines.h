#ifndef DISPLAY_DEFINES
#include "QString"

#define kHz 1000
#define MHz 1000000

char * toCharP(QString in )
{
    QByteArray a ;
    a.append(in);
    return a.data();
}




    char xLabel[] = "f(Hz)", yLabel[] = "I(dB)";

QString LABEL_X = "Frequency (Hz)";
QString LABEL_Y = "Intensity (dB)";





#endif // DISPLAY_DEFINES

