#pragma once

namespace TokenType
{
	enum TokenType
	{
		Null = 0, IfStatement, ElseStatement, WhileStatement, OpenParenthesis, ClosingParenthesis, OpenBracket, ClosingBracket,
		OpenSquareBracket, ClosingSquareBracket, IsNotStatement, OrNotStatement, IsStatement, AndStatement, NotStatement,
		OrStatement, LesserOrEqualStatement, GreatherOrEqualStatement, LesserThenStatement, GreatherThenStatement,
		AssignmentOperator, AddThenAssignOperator, IncreaseOperator, DecreaseOperator, AddOperator,
		MultiplyThenAssignOperator, MinusThenAssignOperator, DivideThenAssignOperator, MinusOperator, DivideOperator, MultiplyOperator,
		ModuloOperator, Undefined, LineEnd, Function, Var, Return, Comment, ParameterOperator, Number, String, BooleanTrue, BooleanFalse, Name, SIZE_OF_ENUM
	};
	static const char* TokenTypeNames[SIZE_OF_ENUM] = {
		"Null", "if", "else", "while", "(", ")", "{", "}",
		"[", "]", "is not", "or not", "is", "and", "not",
		"or", "<=", ">=", "<", ">",
		"=", "+=", "++", "--", "+",
		"*=", "-=", "/=", "-", "/", "*",
		"%", "none", ";", "function", "var", "return", "#", ",", "Number", "String", "true", "false", "Name"
	};
};