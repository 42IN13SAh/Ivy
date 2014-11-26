#include "syntaxhighlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\breturn\\b"
                    << "\\bnumber\\b"
                    << "\\bboolean\\b"
                    << "\\bvar\\b"
                    << "\\bfunction\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //classFormat.setFontWeight(QFont::Bold);
    //classFormat.setForeground(Qt::darkMagenta);
    //rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    //rule.format = classFormat;
    //highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    QRegExp comment("#.*#");
    comment.setMinimal(true);
    rule.pattern = comment;
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    //multiLineCommentFormat.setForeground(Qt::darkGreen);

    quotationFormat.setForeground(Qt::red);
    QRegExp string("\".*\"");
    string.setMinimal(true);
    rule.pattern = string;
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("#");
    commentEndExpression = QRegExp("#");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
}
