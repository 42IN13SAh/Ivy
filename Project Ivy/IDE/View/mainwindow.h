#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ctime>
#include <QMainWindow>

#include "syntaxhighlighter.h"
#include "codeeditor.h"
#include "buttonbar.h"
#include "bottombar.h"

class QTextEdit;
class KeyInputController;

Q_DECLARE_METATYPE(QList<QString*>);

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	CodeEditor* getCodeEditor();
	BottomBar* getBottomBar();
	void codeEditorKeyPressed();

	int showUnsavedChangesDialog();
	void resetEditor();

	QString getCurrentWindowTitle();
	const QString const getDefaultWindowTitle() { return tr("Ivy IDE"); }
	void setAndSaveWindowTitle(QString windowTitle);
	void setFocusOnEditor();

	public slots:
	void about();
	void newFile();
	void saveFile();
	void saveFileAs();
	void openFile();
	void defaultKeyPressEvent(QKeyEvent* event);
	void onClearBeforeBuilding();
	void onAddError(int, int, QString);
	void onSetCompleterModel(QList<QString>);
	void onFinishedBuilding();

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

	QString currentWindowTitle;

protected:
	void keyPressEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
