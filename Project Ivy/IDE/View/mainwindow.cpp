#include <QtWidgets>
#include <QBoxLayout>

#include "mainwindow.h"
#include "keyinputcontroller.h"
#include "basecontroller.h"

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

	setAndSaveWindowTitle("New File - " + this->getDefaultWindowTitle()); //Default is always a new file (for now)

	//make sure to always conenct both controllers to the same slot!
	connect(keyInputController, SIGNAL(clearBeforeBuilding()), this, SLOT(onClearBeforeBuilding()));
	connect(keyInputController, SIGNAL(addError(int, int, QString)), this, SLOT(onAddError(int, int, QString)));
	connect(keyInputController, SIGNAL(setCompleterModel(QList<QString>)), this, SLOT(onSetCompleterModel(QList<QString>)));
	connect(buttonBar->getButtonController(), SIGNAL(clearBeforeBuilding()), this, SLOT(onClearBeforeBuilding()));
	connect(buttonBar->getButtonController(), SIGNAL(addError(int, int, QString)), this, SLOT(onAddError(int, int, QString)));
	bool connected = connect(buttonBar->getButtonController(), SIGNAL(setCompleterModel(QList<QString>)), this, SLOT(onSetCompleterModel(QList<QString>)));

	/*std::async(std::launch::async, [&]() {
		while (true)
		{
		if (!hasBuild)
		{
		hasBuild = true;
		keyInputController->startBuilding(true, false);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		});*/
}

void MainWindow::onSetCompleterModel(QList<QString> list)
{
	editor->setCompleterModel(list);
}

void MainWindow::onClearBeforeBuilding()
{
	bottomBar->clearConsole();
	bottomBar->clearErrorList();
	editor->clearUnderlines();
}

void MainWindow::onAddError(int lineNumber, int linePosition, QString text)
{
	editor->underlineError(lineNumber, linePosition);
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
	//Since we already have access to the keyinputcontroller, we'll use that real quick.
	keyInputController->startNewFile(this);
}

void MainWindow::saveFile()
{
	//Since we already have access to the keyinputcontroller, we'll use that real quick.
	keyInputController->saveCurrentCodeToExistingFile(this);
}

void MainWindow::saveFileAs()
{
	//Since we already have access to the keyinputcontroller, we'll use that real quick.
	keyInputController->saveCurrentCodeToNewFile(this);
}

void MainWindow::openFile()
{
	//Since we already have access to the keyinputcontroller, we'll use that real quick.
	keyInputController->openFileAction(this->editor, this);
}

void MainWindow::defaultKeyPressEvent(QKeyEvent *event){
	QMainWindow::keyPressEvent(event);
}

void MainWindow::codeEditorKeyPressed()
{
	hasBuild = false;
}

int MainWindow::showUnsavedChangesDialog(){
	return QMessageBox::warning(this, tr("File has changed"),
		tr("The file has been modified.\n"
		"Do you want to save your changes?"),
		QMessageBox::Yes | QMessageBox::No
		| QMessageBox::Cancel);
}

void MainWindow::resetEditor(){
	this->editor->clear();
}

QString MainWindow::getCurrentWindowTitle(){
	return this->currentWindowTitle;
}

void MainWindow::setAndSaveWindowTitle(QString windowTitle){
	this->currentWindowTitle = windowTitle;
	MainWindow::setWindowTitle(this->currentWindowTitle);
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
	fileMenu->addAction(tr("&Save"), this, SLOT(saveFile()), QKeySequence::Save);
	fileMenu->addAction(tr("&Save As..."), this, SLOT(saveFileAs()), QKeySequence::SaveAs);
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
	this->keyInputController = new KeyInputController(this);
	editor->setKeyInputController(this->keyInputController);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
	this->keyInputController->handleKeyPressEvent(event, this, nullptr);
}

CodeEditor* MainWindow::getCodeEditor()
{
	return editor;
}

BottomBar* MainWindow::getBottomBar()
{
	return bottomBar;
}