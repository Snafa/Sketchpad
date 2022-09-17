#include <QApplication>

#include "sketchpad.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Sketchpad w;

    w.resize(800, 500);
    w.setWindowTitle("SketchPad");
    w.setWindowIcon(QIcon("icon.ico"));
    w.show();

    return app.exec();
}
