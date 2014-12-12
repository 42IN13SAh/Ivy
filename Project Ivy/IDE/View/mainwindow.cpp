#include <QtWidgets>
#include <QBoxLayout>
#include "mainwindow.h"
#include "keyinputcontroller.h"

#include <chrono>
#include <thread>
#include <future>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();
    setupButtonBar();
    setupBottomBar();
    setupControllers();

	hasBuild = true;

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->addWidget(buttonBar);
    layout->addWidget(editor);
    layout->addWidget(bottomBar);

    layout->setSpacing(0);

    QWidget *window = new QWidget();
    window->setLayout(layout);

    setCentralWidget(window);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

    setWindowTitle(tr("Ivy IDE"));

	connect(keyInputController, SIGNAL(clearBeforeBuilding()), this, SLOT(onClearBeforeBuilding()));
	connect(keyInputController, SIGNAL(addError(int, int, QString)), this, SLOT(onAddError(int, int, QString)));
	connect(buttonBar->getButtonController(), SIGNAL(clearBeforeBuilding()), this, SLOT(onClearBeforeBuilding()));
	connect(buttonBar->getButtonController(), SIGNAL(addError(int, int, QString)), this, SLOT(onAddError(int, int, QString)));

	std::async(std::launch::async, [&]() {
		while (true)
		{
			//Start building when there is the need to be builded and there has 1 second passed since the last keypress.
			//The timeElapsedSinceTyping > 0 condition is there so this thread doesn't try building after the window is closed.
			if (!hasBuild && (std::clock() - timeElapsedSinceTyping) / (double)CLOCKS_PER_SEC > 1 && timeElapsedSinceTyping > 0)
			{
				hasBuild = true;
				keyInputController->startBuilding(true, false);
			}
		}
	});
}

void MainWindow::onClearBeforeBuilding()
{
	bottomBar->clearConsole();
	bottomBar->clearErrorList();
}

void MainWindow::onAddError(int lineNumber, int linePosition, QString text)
{
	//editor->underlineError(lineNumber, linePosition);
	bottomBar->addError(lineNumber, linePosition, text);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Ivy IDE"), tr("<p>This is the <b>Ivy IDE</b> created by 42IN14SAh</p>"));
}

void MainWindow::setupButtonBar()
{
    buttonBar = new ButtonBar(this);
}

void MainWindow::setupBottomBar()
{
    bottomBar = new BottomBar(this);
}

void MainWindow::newFile()
{
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Ivy File (*.ivy)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}

void MainWindow::defaultKeyPressEvent(QKeyEvent *event){
	QMainWindow::keyPressEvent(event);
}

void MainWindow::codeEditorKeyPressed()
{
	hasBuild = false;
	timeElapsedSinceTyping = std::clock();
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new CodeEditor(this);
    editor->setFont(font);
    editor->setFrameStyle(QFrame::NoFrame);

    const int tabStop = 4;  // 4 characters

    QFontMetrics metrics(font);
    editor->setTabStopWidth(tabStop * metrics.width(' '));

    QPalette p = editor->palette();

    QColor q = QColor();
    q.setNamedColor("#212121");
    p.setColor(QPalette::Active, QPalette::Base, q);
    p.setColor(QPalette::Inactive, QPalette::Base, q);
    p.setColor(QPalette::Active, QPalette::Text, Qt::white);
    p.setColor(QPalette::Inactive, QPalette::Text, Qt::white);

    editor->setPalette(p);
    highlighter = new Highlighter(editor->document());

    //TODO testen of open file werkt.
    //QFile file("mainwindow.h");
    //if (file.open(QFile::ReadOnly | QFile::Text))
        //editor->setPlainText(file.readAll());
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);

	setStyleSheet("QMenuBar { background-color: #323232; border-bottom: 1px solid black; } QMenuBar::item { background-color: #323232; color: white; } QMenuBar::item:selected { background-color: #1E1E1F; } QMenuItem { background-color: #323232; color: white; } QMenu::item { background-color: #323232; color: white; } QMenu::item:selected { background-color: #1E1E1F; } QMenu { background-color: #323232; }");
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void MainWindow::setupControllers(){
    keyInputController = new KeyInputController(this);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    keyInputController->handleKeyPressEvent(event);
}

CodeEditor* MainWindow::getCodeEditor()
{
	return editor;
}

BottomBar* MainWindow::getBottomBar()
{
	return bottomBar;
}