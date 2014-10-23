#pragma once
#include <map>
enum TokenType
{
	IfStatement, ElseStatement, WhileStatement, OpenParenthesis, ClosingParenthesis, OpenBracket, ClosingBracket,
	OpenSquareBracket, ClosingSquareBracket, IsNotStatement, OrNotStatement, IsStatement, AndStatement, NotStatement,
	OrStatement, LesserOrEqualStatement, GreatherOrEqualStatement, LesserThenStatement, GreatherThenStatement, 
	AssignmentOperator, AddThenAssignOperator,IncreaseOperator, DecreaseOperator, AddOperator, 
	MultiplyThenAssignOperator, MinusThenAssignOperator, DivideThenAssignOperator, MinusOperator,DivideOperator, MultiplyOperator, 
	ModuloOperator, Undefined, LineEnd, Funtion, Var, Return, Comment, ParameterOperator, Number, String, BooleanTrue, BooleanFalse, Name 
};


