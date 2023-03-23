#include "steganoimage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Steganoimage w; //dans cette ligne, le programme crée une fenêtre Steganoimage telle que définie dans le fichier steganoimage.ui
    w.show(); //le programme affiche ensuite la fenêtre

    return a.exec();
}
