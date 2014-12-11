#pragma once
enum class TokenType
{
	Null, IfStatement, ElseStatement, WhileStatement, OpenParenthesis, ClosingParenthesis, OpenBracket, ClosingBracket,
	OpenSquareBracket, ClosingSquareBracket, IsNotStatement, OrNotStatement, IsStatement, AndStatement, NotStatement,
	OrStatement, LesserOrEqualStatement, GreatherOrEqualStatement, LesserThenStatement, GreatherThenStatement,
	AssignmentOperator, AddThenAssignOperator, IncreaseOperator, DecreaseOperator, AddOperator,
	MultiplyThenAssignOperator, MinusThenAssignOperator, DivideThenAssignOperator, MinusOperator, DivideOperator, MultiplyOperator,
	ModuloOperator, Undefined, LineEnd, Function, Var, Return, Comment, ParameterOperator, Number, String, BooleanTrue, BooleanFalse, Name
};