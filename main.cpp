#include "mainwindow.h"
#include <QApplication>
#include <algorithm>
#include <alsa/asoundlib.h>
#include "AudioInput.hpp"
#include "display.h"
#include "GraphicsItem.hpp"
#include "SpectrogramVisualizer.hpp"
#include "Log.hpp"



const char* const helptext[] = {
    " glSpect: real-time OpenGL spectrogram. ",
    "                                         (Based on Luke Campagnola glScope)\n\n",
    "Usage: glspect  [-f] [-v] [-sf <scroll_factor>] [-w <windowType>] [-t windowSizeExponent]\n\n",
    "Command line arguments:\n",
    "windowType = \t0 (no window)\n\t\t1 (Hann)\n\t\t2 (Gaussian trunc at +-4sigma) (default)\n",
    "scroll_factor = 1,2,... # vSyncs (60Hz) to wait per scroll pixel (default 1)\n",
    "windowSizeExponent = 11,12,...,16 is power of 2 giving FFT fftLength N (default 13)\n\t(Note: this controls the vertical frequency resolution and range)\n\n",
    "Keys & mouseHandle: \tarrows or middle button drag - brightness/contrast\n",
    "\t\tleft button shows horizontal frequency readoff line\n",
    "\t\tright button shows horizontal frequency readoff with multiples\n",
    "\t\ti - cycles through color maps (B/W, inverse B/W, color)\n",
    "\t\tq or Esc - quit\n",
    "\t\t[ and ] - control horizontal scroll factor (samplingRate)\n",
    NULL};


// Various parameters
struct Param {
    // DFT windowing function type
    int windowType;
    // Power of 2 giving DFT fftLength (N) in samples
    int windowSizeExponent;
};
Param param;
int screenMode;
unsigned int verbosity;
int scrollFactor;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    display * disp;
    MainWindow w;
    w.show();
    disp = new display(0);
    disp->Display(argc,argv,2);



    /* set default values, and change as specified by the user via command line options */
    screenMode = 0;  /* default to windowed unless user specifies full via -f */
    verbosity = 0;  /* default to std::cout */
    scrollFactor = 2;  /* how many vSyncs to wait before scrolling spectrogram */
    param.windowType = 2;  /* Gaussian window */
    param.windowSizeExponent = 13;  /* 8192 samples (around 0.19 sec). Remains fixed. */
    disp->displayWin();
//    disp = new display(argc,argv,screenMode);


//    /* parse command line options from the user */
//    for (int i = 1; i<argc; ++i) {
//        if (!strcmp(argv[i], "-f")) {
//            screenMode = 1;
//        }
//        else if (!strcmp(argv[i], "-v")) {
//            verbosity = 1;
//        }
//        else if (!strcmp(argv[i], "-sf")) {
//            sscanf(argv[++i], "%d", &scrollFactor);
//            scrollFactor = std::min(scrollFactor, 1);  /* ensure value <= 1 */
//        }
//        else if (!strcmp(argv[i], "-t")) {
//            sscanf(argv[++i], "%d", &param.windowSizeExponent);
//            /* ensure range of [10,18] */
//            param.windowSizeExponent = std::max(10, param.windowSizeExponent);
//            param.windowSizeExponent = std::min(18, param.windowSizeExponent);
//        }
//        else if (!strcmp(argv[i], "-w")) {
//            sscanf(argv[++i], "%d", &param.windowType);
//            param.windowType = std::max(0, param.windowType);  /* ensure value >= 0 */
//        }
//        else {
//            /* misuse or -h, print out usage text */
//            fprintf(stderr, "bad command line option %s\n\n", argv[i]);
//            for (int j = 0; helptext[j]; j++) {
//                fprintf(stderr, "%s", helptext[j]);
//            }
//            std::cout << helptext << std::endl;
//            exit(1);
//        }
//    }
//    Log::OUTPUT_DIRECTION = verbosity;


    /* create GraphicsItem observers and add them to the display's observer list */
    SpectrogramVisualizer spectrogramVisualizer(scrollFactor);
    disp->addGraphicsItem(&spectrogramVisualizer);

    disp->loop();  /* main loop */
//        return 0;


    return a.exec();
}
