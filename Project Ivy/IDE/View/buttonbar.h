#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <QWidget>
#include <QPushButton>

#include "buttoncontroller.h"

class ButtonBar : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonBar(QWidget *parent = 0);
	ButtonController *getButtonController();

private slots:
    void runButtonClicked();
    void buildButtonClicked();

private:
    QPushButton *runButton;
    QPushButton *buildButton;
    ButtonController *controller;
};

#endif // BUTTONBAR_H
