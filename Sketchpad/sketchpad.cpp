#include <QDir>
#include <QIcon>
#include <QMenu>
#include <QDate>
#include <QPrinter>
#include <QMenuBar>
#include <QToolBar>
#include <QFileInfo>
#include <QFontInfo>
#include <QtWidgets>
//#include <QBoxLayout>
#include <QStatusBar>
#include <QTextCursor>
#include <QFontDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPushButton>
#include <QGridLayout>
#include <QPrintDialog>
#include <QApplication>

#include "sketchpad.h"

Sketchpad::Sketchpad(QWidget *p) : QMainWindow(p), Zoom(0), file("unnamed.txt") {

    QAction *New = new QAction("&New", this);
    QAction *Open = new QAction("&Open...", this);
    QAction *Save = new QAction("&Save", this);
    QAction *AutoSave = new QAction("&AutoSave", this);
    QAction *SaveAs = new QAction("Save &As...", this);
    QAction *Exit = new QAction("&Exit", this);
    QAction *Undo = new QAction("&Undo", this);
    QAction *Cut = new QAction("&Cut", this);
    QAction *Copy = new QAction("C&opy", this);
    QAction *Paste = new QAction("&Paste", this);
    QAction *Delit = new QAction("&Delit", this);
    QAction *SelectAll = new QAction("&Select All", this);
    QAction *TimeandDate = new QAction("&Time and date", this);
    QAction *ZoomIn = new QAction("&Zoom in", this);
    QAction *ZoomOut = new QAction("&Zoom out", this);
    QAction *Font = new QAction("&Font...", this);

    text = new QTextEdit("", this);
    text->setFrameStyle(QFrame::NoFrame);
    text->setFont(QFont("Times New Roman", 12, text->font().weight(), text->font().italic()));
    QMenu *f1 = menuBar()->addMenu("&File");
    QMenu *f2 = menuBar()->addMenu("&Edit");
    QMenu *f3 = menuBar()->addMenu("F&ormat");
    QMenu *f4 = menuBar()->addMenu("&View");

    Exit->setShortcut(tr("CTRL+Q"));
    New->setShortcut(tr("CTRL+N"));
    Open->setShortcut(tr("CTRL+O"));
    Save->setShortcut(tr("CTRL+S"));
    SaveAs->setShortcut(tr("CTRL+Shift+S"));
    AutoSave->setShortcut(tr("CTRL+Shift+V"));
    Undo->setShortcut(tr("CTRL+Z"));
    Cut->setShortcut(tr("CTRL+X"));
    Copy->setShortcut(tr("CTRL+C"));
    Paste->setShortcut(tr("CTRL+V"));
    SelectAll->setShortcut(tr("CTRL+A"));
    Delit->setShortcut(tr("Del"));
    TimeandDate->setShortcut(tr("F5"));
    ZoomIn->setShortcut(tr("CTRL++"));
    ZoomOut->setShortcut(tr("CTRL+-"));


    setCentralWidget(text);


    f1->addAction(New);
    f1->addAction(Open);
    f1->addAction(Save);
    f1->addAction(SaveAs);
    f1->addAction(AutoSave);
    f1->addSeparator();
    f1->addSeparator();
    f1->addAction(Exit);

    f2->addAction(Undo);
    f2->addSeparator();
    f2->addAction(Cut);
    f2->addAction(Copy);
    f2->addAction(Paste);
    f2->addAction(Delit);
    f2->addSeparator();
    f2->addAction(SelectAll);
    f2->addSeparator();
    f2->addAction(TimeandDate);
    f3->addAction(Font);
    f4->addAction(ZoomIn);
    f4->addAction(ZoomOut);

    statusBar()->showMessage("Ready");

    connect(Exit, &QAction::triggered, this, &QApplication::quit);
    connect(Open, &QAction::triggered, this, &Sketchpad::Open);
    connect(Save, &QAction::triggered, this, &Sketchpad::Save);
    connect(SaveAs, &QAction::triggered, this, &Sketchpad::SaveAs);
    connect(New, &QAction::triggered, this, &Sketchpad::New);
    connect(Font, &QAction::triggered, this, &Sketchpad::SetFont);
    connect(Cut, &QAction::triggered, text, &QTextEdit::cut);
    connect(Paste, &QAction::triggered, text, &QTextEdit::paste);
    connect(Copy, &QAction::triggered, text, &QTextEdit::copy);
    connect(Undo, &QAction::triggered, text, &QTextEdit::undo);
    connect(SelectAll, &QAction::triggered, text, &QTextEdit::selectAll);
    connect(TimeandDate, &QAction::triggered, this, &Sketchpad::TimeandDate);
    connect(Delit, &QAction::triggered, this, &Sketchpad::Delit);
    connect(ZoomIn, &QAction::triggered, this, &Sketchpad::ZoomIn);
    connect(ZoomOut, &QAction::triggered, this, &Sketchpad::ZoomOut);
    connect(AutoSave, &QAction::triggered, this, &Sketchpad::AutoSave);
}

void Sketchpad::ZoomIn() {

    text->zoomIn(2);
    Zoom += 2;
}

void Sketchpad::ZoomOut() {

    text->zoomOut(2);
    Zoom -= 2;
}

bool Sketchpad::SetFont() {

    bool flag;

    QFont font = QFontDialog::getFont(&flag, QFont(text->font().family(), text->font().pointSize() - Zoom,
                                                 text->font().weight(), text->font().italic()), this);

    if (flag) {
        text->setFont(font);
        if (Zoom > 0) {
            text->zoomIn(Zoom);
        }
        if (Zoom < 0) {
            text->zoomOut(Zoom);
        }
    }

    return flag;
}

void Sketchpad::Delit() {

    QTextCursor cursor = text->textCursor();

    if (cursor.hasSelection()) {
        cursor.deletePreviousChar();
    }

    text->setTextCursor(cursor);
}

bool Sketchpad::TimeandDate() {

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    text->insertPlainText(time.toString("hh:mm") + " " + date.toString("dd:MM:yyyy"));

    return true;
}

bool Sketchpad::question() {

    QString s;
    s += '"';

    QString t = "Do you want to save changes to the file\r\n" + s + QString(QFileInfo(file).baseName()) + s + "?";

    QMessageBox qmb(this);

    qmb.setStyleSheet("QLabel{max-width: 325px; font-size: 14px; color: '#000080'} QPushButton{ width:90px; font-size: 12px; }");
    qmb.setText(t);

    QPushButton *save = qmb.addButton(tr("Save"), QMessageBox::ActionRole);
    QPushButton *no = qmb.addButton(tr("Don't save"), QMessageBox::ActionRole);
    QPushButton *cancel = qmb.addButton(tr("Cancel"), QMessageBox::ActionRole);

    qmb.setDefaultButton(save);

    qmb.exec();

    if (qmb.clickedButton() == save) {
        Save();
    }

    return qmb.clickedButton() == no;
}

bool Sketchpad::save(QString path) {

    if (path.isEmpty()) {
        return false;
    }

    file.setFileName(path);

    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Truncate);
    QTextStream out(&file);

    out << text->toPlainText();
    file.close();

    setWindowTitle(QFileInfo(file).fileName() + " - Sketchpad");

    return true;
}

QString Sketchpad::filetext() {

    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString str = stream.readAll();

    file.close();

    return str;
}

bool Sketchpad::check() {

    if (!file.exists()) {
        return (text->toPlainText().isEmpty());
    }

    return text->toPlainText() == filetext();
}

bool Sketchpad::Open() {

    if (!check()) {
        question();
    }

    QString path = QFileDialog::getOpenFileName();

    if (path.isEmpty()) {
        return false;
    }

    file.setFileName(path);

    text->setText(filetext());
    setWindowTitle(QFileInfo(file).fileName() + " - Sketchpad");

    return true;
}

bool Sketchpad::Save() {

    QString path = QFileInfo(file).absoluteFilePath();

    if (!file.exists()) {
        path = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Document(*.txt)"));
    }

    return save(path);
}

bool Sketchpad::SaveAs() {

    QString path = QFileDialog::getSaveFileName(this, tr("Open File"), "", tr("Text Document (*.txt)"));

    return save(path);
}

bool Sketchpad::New() {

    if (!check() && !question()) {
        return false;
    }

    file.setFileName("unnamed.txt");
    text->clear();

    return true;
}

void Sketchpad::AutoSave() {
    static bool flag = false;
    if (!flag) {
        connect(text, &QTextEdit::textChanged, this, &Sketchpad::Save);
    }
    else {
        disconnect(text, &QTextEdit::textChanged, this, &Sketchpad::Save);
    }
    flag ^= 1;
}

void Sketchpad::closeEvent(QCloseEvent *event) {

    if (!check()) {
        if (question()) {
            event->accept();
        }
        else {
            event->ignore();
        }
    }
    else {
        event->accept();
    }
}

