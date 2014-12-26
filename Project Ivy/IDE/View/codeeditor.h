#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QCompleter>

#include "KeyInputController.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class MainWindow;

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
	CodeEditor(MainWindow *parent = 0);
	static QStringList defaultKeywords;

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void moveCursor(int lineNumber, int linePosition);
	std::vector<std::string> getEditorContent();
	void underlineError(int lineNumber, int linePosition);
	void clearUnderlines();
	void defaultKeyPressEvent(QKeyEvent *e);
	void setKeyInputController(KeyInputController *keyInputController);
	void setCompleterModel(QList<QString>);

protected:
    void resizeEvent(QResizeEvent *event);
	void keyPressEvent(QKeyEvent* e);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
	void insertCompletion(const QString&);

private:
    QWidget *lineNumberArea;
	MainWindow *source;
	KeyInputController *keyInputController;
	QCompleter *completer;

	void autocomplete(QKeyEvent *e);
	QString getCurrentLine(QTextCursor cursor, int startCount = 0);
	QString getLineToInsert(QString line);
};


class LineNumberArea : public QFrame
{
public:
    LineNumberArea(CodeEditor *editor) : QFrame(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif
