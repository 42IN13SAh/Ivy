#include <QHBoxLayout>
#include <QPalette>
#include <QDebug>

#include "buttonbar.h"

ButtonBar::ButtonBar(QWidget *parent) : QWidget(parent)
{
    controller = new ButtonController((MainWindow *)parent);
    QHBoxLayout *layout = new QHBoxLayout();

    runButton = new QPushButton();
    runButton->setText("Run");
    runButton->setMaximumSize(50, 22);
    runButton->setMinimumSize(50, 22);
    QPixmap pix(":/Images/Images/RunButtonIcon.png");
    QIcon icon(pix);
    runButton->setIcon(icon);
    runButton->setIconSize(pix.size());

    buildButton = new QPushButton();
    buildButton->setText("Build");
    buildButton->setMaximumSize(50, 22);
    buildButton->setMinimumSize(50, 22);
    QPixmap pix2(":/Images/Images/BuildButtonIcon.png");
    QIcon icon2(pix2);
    buildButton->setIcon(icon2);
    buildButton->setIconSize(pix2.size());

    connect(runButton, SIGNAL(released()), this, SLOT(runButtonClicked()));
    connect(buildButton, SIGNAL(released()), this, SLOT(buildButtonClicked()));

    layout->addWidget(runButton);
    layout->addWidget(buildButton);
    layout->setContentsMargins(5, 5, 0, 5);
    layout->setAlignment(Qt::AlignLeft);
    setLayout(layout);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, "#323232");
    setAutoFillBackground(true);
    setPalette(Pal);

    //background color for all buttons inside the buttonbar
    setStyleSheet("QPushButton { color: white; background-color: #2D2D2F; border: none; border-color: black; } QPushButton:hover{ background-color: #1E1E1F; } QPushButton:pressed{ border-left: 2px solid grey; border-top: 2px solid grey; border-right: 2px solid black; border-bottom: 2px solid black; }");
}

void ButtonBar::runButtonClicked(){
    controller->runButtonClicked();
}

void ButtonBar::buildButtonClicked(){
    controller->buildButtonClicked();
}
