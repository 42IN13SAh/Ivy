#include <QtWidgets>
#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);;
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
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
            painter.drawText(0, top, lineNumberArea->width()-5 , fontMetrics().height(),
                             Qt::AlignRight, number);
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
	tmpCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, linePosition);
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

void CodeEditor::defaultKeyPressEvent(QKeyEvent *event){
	QPlainTextEdit::keyPressEvent(event);
}

void CodeEditor::setKeyInputController(KeyInputController *keyInputController){
	this->keyInputController = keyInputController;
}

void CodeEditor::keyPressEvent(QKeyEvent* event){
	this->keyInputController->handleKeyPressEvent(event, nullptr, this);
}
