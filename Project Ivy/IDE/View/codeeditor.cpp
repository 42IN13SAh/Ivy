#include <QtWidgets>
#include "codeeditor.h"
#include "mainwindow.h"

QStringList CodeEditor::defaultKeywords;

CodeEditor::CodeEditor(MainWindow *parent) : QPlainTextEdit(parent)
{
	source = parent;
    lineNumberArea = new LineNumberArea(this);;
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	CodeEditor::defaultKeywords << "function" << "var" << "if" << "else" << "is" << "or" << "while" << "and" << "not" << "return";

	completer = new QCompleter(); //anti crash
	setCompleterModel(QList<QString>());

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void CodeEditor::setCompleterModel(QList<QString> list)
{
	disconnect(completer, 0, this, 0);
	delete completer;

	QStringList *wordList = new QStringList(list);
	wordList->append(defaultKeywords);

	completer = new QCompleter(*wordList, this);
	completer->setWidget(this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	completer->popup()->setStyleSheet("QListView { background-color: #2D2D2F; color: white; }");
	connect(completer, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));

	delete wordList;
}

void CodeEditor::insertCompletion(const QString& completion)
{
	QTextCursor tc = textCursor();
	int extra = completion.length() - completer->completionPrefix().length();
	tc.movePosition(QTextCursor::Left);
	tc.movePosition(QTextCursor::EndOfWord);
	tc.insertText(completion.right(extra));
	setTextCursor(tc);
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 6;
//    int max = qMax(1, blockCount());
//    while (max >= 10) {
//        max /= 10;
//        ++digits;
//    }
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::underlineError(int lineNumber, int linePosition)
{
	QTextCursor cursor = this->textCursor();
	cursor.movePosition(QTextCursor::Start);
	cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber - 1);
	cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, linePosition - 1);
	cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
	setTextCursor(cursor);
	
	QTextCharFormat defcharfmt = currentCharFormat();
	QTextCharFormat newcharfmt = defcharfmt;
	newcharfmt.setUnderlineColor(QColor(Qt::red));
	newcharfmt.setUnderlineStyle(QTextCharFormat::WaveUnderline);
	newcharfmt.setFontUnderline(true);

	setCurrentCharFormat(newcharfmt);

	cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
	setTextCursor(cursor);

	setCurrentCharFormat(defcharfmt);
}

void CodeEditor::clearUnderlines()
{
	QTextCursor cursor = this->textCursor();
	QTextCursor oldCursor = cursor;
	cursor.movePosition(QTextCursor::Start);
	cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
	setTextCursor(cursor);

	QTextCharFormat defcharfmt = currentCharFormat();
	QTextCharFormat newcharfmt = defcharfmt;
	newcharfmt.setFontUnderline(false);

	setCurrentCharFormat(newcharfmt);

	setTextCursor(oldCursor);

	setCurrentCharFormat(defcharfmt);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::black);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    QColor q = QColor();
    q.setNamedColor("#323232");
    QColor q2 = QColor();
    q2.setNamedColor("#247EAF");
    painter.fillRect(event->rect(), q);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(q2);
            painter.drawText(0, top, lineNumberArea->width()-5 , fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void CodeEditor::moveCursor(int lineNumber, int linePosition)
{
    QTextCursor tmpCursor = this->textCursor();
	tmpCursor.movePosition(QTextCursor::Start);
	tmpCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber - 1);
	tmpCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, linePosition - 1);
    this->setTextCursor(tmpCursor);
	this->setFocus();
}

std::vector<std::string> CodeEditor::getEditorContent()
{
	std::vector<std::string> list;
	for (QTextBlock block = document()->begin(); block.isValid(); block = block.next())
	{
		list.push_back(block.text().toStdString());
	}

	return list;
}

void CodeEditor::defaultKeyPressEvent(QKeyEvent *e)
{
	QPlainTextEdit::keyPressEvent(e);
	autocomplete(e);
}

void CodeEditor::setKeyInputController(KeyInputController *keyInputController){
	this->keyInputController = keyInputController;
}

void CodeEditor::keyPressEvent(QKeyEvent* e)
{
	//let the completer do its behaviour if the popup is visible
	if (completer->popup()->isVisible())
	{
		switch (e->key())
		{
			case Qt::Key_Enter:
			case Qt::Key_Return:
			case Qt::Key_Escape:
			case Qt::Key_Tab:
			case Qt::Key_Backtab:
				e->ignore();
				return;
			default:
				break;
		}
	}

	bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+Space
	if (!isShortcut)
	{// do not process the shortcut when we have a completer
		this->keyInputController->handleKeyPressEvent(e, nullptr, this);
		source->codeEditorKeyPressed();
	}

	const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
	if (ctrlOrShift && e->text().isEmpty())
	{
		return;
	}

	static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
	bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;

	QTextCursor tc = this->textCursor();
	tc.select(QTextCursor::WordUnderCursor);
	QString completionPrefix = tc.selectedText();

	if (!isShortcut && (hasModifier || e->text().isEmpty() || completionPrefix.length() < 3 || eow.contains(e->text().right(1))))
	{
		completer->popup()->hide();
		return;
	}

	if (completionPrefix != completer->completionPrefix())
	{
		completer->setCompletionPrefix(completionPrefix);
		completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
	}

	QRect cr = cursorRect();
	cr.setWidth(completer->popup()->sizeHintForColumn(0) + completer->popup()->verticalScrollBar()->sizeHint().width());
	completer->complete(cr); // popup it up!
}

void CodeEditor::autocomplete(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_BraceLeft: // {
	{
								QString currentLine = getCurrentLine(this->textCursor());
								insertPlainText("\n" + getLineToInsert(currentLine) + "\t" + getLineToInsert(currentLine) + "\n}");
								QTextCursor oldCursor = this->textCursor();
								oldCursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, 1);
								oldCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
								this->setTextCursor(oldCursor);
								break;
	}
	case Qt::Key_ParenLeft: // (
	{
								insertPlainText(")");
								QTextCursor oldCursor = this->textCursor();
								oldCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
								this->setTextCursor(oldCursor);
								break;
	}
	case Qt::Key_Return:
	{
								QTextCursor oldCursor = this->textCursor();
								QString currentLine = getCurrentLine(oldCursor, -1);
								if (currentLine.endsWith("{"))
								{
									insertPlainText(getLineToInsert(currentLine) + "\t");
								}
								else
								{
									insertPlainText(getLineToInsert(currentLine));
								}
								break;
	}
	default:
		break;
	}
}

//startPos needs to be -1 when pressing return, this way you get the previous line
QString CodeEditor::getCurrentLine(QTextCursor cursor, int startCount)
{
	int lineNumber = startCount;
	while (cursor.positionInBlock() > 0)
	{
		cursor.movePosition(QTextCursor::Up);
		lineNumber++;
	}
	QTextBlock block = cursor.block().previous();

	while (block.isValid())
	{
		lineNumber += block.lineCount();
		block = block.previous();
	}

	QString plainTextEditContents = this->toPlainText();
	QStringList lines = plainTextEditContents.split("\n");

	return lines[lineNumber];
}

QString CodeEditor::getLineToInsert(QString line)
{
	QString lineToInsert;
	while (line.startsWith("\t") || line.startsWith(" "))
	{
		if (line.startsWith("\t"))
		{
			lineToInsert.append("\t");
		}
		else
		{
			lineToInsert.append(" ");
		}

		line.remove(0, 1);
	}

	return lineToInsert;
}