#pragma once

#include <QMainWindow>
#include <QFile>
#include <QTextEdit>

class Sketchpad : public QMainWindow {

  Q_OBJECT

public:
    Sketchpad(QWidget *p = 0);

private slots:
    bool New();
    bool Open();
    bool Save();
    bool SaveAs();
    void Delit();
    bool TimeandDate();
    bool SetFont();
    void ZoomIn();
    void ZoomOut();
    void AutoSave();

private:
    int Zoom;
    QFile file;
    QTextEdit *text;

    bool check();
    bool save(QString path);
    QString filetext();
    bool question();

    void closeEvent(QCloseEvent *event);
};
