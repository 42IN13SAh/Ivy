#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "syntaxhighlighter.h"
#include "codeeditor.h"
#include "buttonbar.h"
#include "bottombar.h"
#include <ctime>

#include <QMainWindow>

class QTextEdit;
class KeyInputController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	CodeEditor* getCodeEditor();
	BottomBar* getBottomBar();
	void codeEditorKeyPressed();

public slots:
    void about();
    void newFile();
    void openFile(const QString &path = QString());
    void defaultKeyPressEvent(QKeyEvent* event);
	void onClearBeforeBuilding();
	void onAddError(int, int, QString);

private:
    void setupEditor();
    void setupButtonBar();
    void setupBottomBar();
    void setupFileMenu();
    void setupHelpMenu();
    void setupControllers();

    CodeEditor *editor;
    Highlighter *highlighter;
    ButtonBar *buttonBar;
    BottomBar *bottomBar;
    KeyInputController *keyInputController;

	bool hasBuild;
	std::clock_t timeElapsedSinceTyping;

protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
