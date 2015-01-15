#include "syntaxhighlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

	// Default keywords
	keywordFormat.setForeground(QColor("#00BBFF"));
    keywordFormat.setFontWeight(QFont::Normal);
    QStringList keywordPatterns;
    keywordPatterns << "\\bif\\b"
                    << "\\belse\\b"
                    << "\\bwhile\\b"
                    << "\\breturn\\b"
					<< "\\bfalse\\b"
					<< "\\btrue\\b"
					<< "\\bvar\\b"
                    << "\\bfunction\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

	// Conditions
	conditionFormat.setForeground(QColor("#BB00FF"));
	conditionFormat.setFontWeight(QFont::Normal);
	QStringList conditionPatterns;
	conditionPatterns << "\\band\\b"
					  << "\\bor\\b";
	foreach(const QString &pattern, conditionPatterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = conditionFormat;
		highlightingRules.append(rule);
	}

	// Subconditions
	subconditionFormat.setForeground(QColor("#FF77EE"));
	subconditionFormat.setFontWeight(QFont::Normal);
	QStringList subconditionPatterns;
	subconditionPatterns << "\\bis\\b"
						 << "\\bnot\\b"
						 << ">="
						 << "<="
						 << ">"
						 << "<";
	foreach(const QString &pattern, subconditionPatterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = subconditionFormat;
		highlightingRules.append(rule);
	}

	// Strings
	quotationFormat.setForeground(QColor("#FFCC00"));
	QRegExp string("\".*\"");
	string.setMinimal(true);
	rule.pattern = string;
	rule.format = quotationFormat;
	highlightingRules.append(rule);

	// Comments
	singleLineCommentFormat.setForeground(QColor("#99FF66"));
    QRegExp comment("#.*#");
    comment.setMinimal(true);
    rule.pattern = comment;
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("#");
    commentEndExpression = QRegExp("#");
}

Highlighter::~Highlighter()
{

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
