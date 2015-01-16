var line_separator = "=============================================";

function print_success(funcion_name) {
	print (" ");
	print("  " + funcion_name + " gave the expected output.");
	print("  TEST SUCCESSFULL!!!");
	print(" ");
    print(line_separator);
}

function print_failed(funcion_name, expected_output, actual_result) {
	print(" ");
	print("  " + funcion_name + " gave unexpected output --> expected:");
	print(expected_output);
	print ("  but instead we received:");
	print(actual_result);
	print("  ... TEST FAILED!!!");
	print(" ");
    print(line_separator);
}

var y = 1;
#========================================#
function test_if_else() {
    if (y is 1) {
        return "if_else: if";
    } else {
        return "if_else: else";
    }
}
#========================================#
#========================================#
var funcion_name = "if_else: if";
var result = test_if_else();
var expected_output = "if_else: if";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name = "if_else: else";
result = test_if_else();
expected_output = "if_else: else";
y++;

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}


var x = 1;
#========================================#
function test_if_else_nested_if_else_in_if() {
    if (y is 2) {
        if (y is 2 and x is 1) {
            return "if_else_nested_if_else_in_if: if, if";
        } else {
            return "if_else_nested_if_else_in_if: if, else";
        }
    } else {
        return "if_else_nested_if_else_in_if: else";
    }
}
#========================================#
#========================================#
funcion_name = "if_else_nested_if_else_in_if: if, if";
result = test_if_else_nested_if_else_in_if();
expected_output = "if_else_nested_if_else_in_if: if, if";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name = "if_else_nested_if_else_in_if: if, else";
x++;
result = test_if_else_nested_if_else_in_if();
expected_output = "if_else_nested_if_else_in_if: if, else";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name = "if_else_nested_if_else_in_if: else";
y++;
result = test_if_else_nested_if_else_in_if();
expected_output = "if_else_nested_if_else_in_if: else";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
function test_if_else_nested_if_else_in_else() {
    if (y is 3) {
        return "if_else_nested_if_else_in_else: if ";
    } else {
        if (y is 4 and x is 2) {
            return "if_else_nested_if_else_in_else: else, if";
        } else {
            return "if_else_nested_if_else_in_else: else, else";
        }
    }
}
#========================================#
#========================================#
funcion_name = "if_else_nested_if_else_in_else: if ";
result = test_if_else_nested_if_else_in_else();
expected_output = "if_else_nested_if_else_in_else: if ";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name = "if_else_nested_if_else_in_else: else, if";
y++;
result = test_if_else_nested_if_else_in_else();
expected_output = "if_else_nested_if_else_in_else: else, if";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name =  "if_else_nested_if_else_in_else: else, else";
x++;
result = test_if_else_nested_if_else_in_else();
expected_output =  "if_else_nested_if_else_in_else: else, else";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
function test_if_else_nested_if_in_if() {
    if (y is 4) {
        if (y is 4 and x is 3) {
            return "if_else_nested_if_else_in_if: if, if";
        }
    } else {
        return "if_else_nested_if_else_in_if: else";
    }
}
#========================================#
#========================================#
funcion_name = "if_else_nested_if_else_in_if: if, if";
result = test_if_else_nested_if_in_if();
expected_output = "if_else_nested_if_else_in_if: if, if";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name = "if_else_nested_if_else_in_if: if, else";
x++;
result = test_if_else_nested_if_in_if();
expected_output = "none"; #result should be none, se we give something that is NOT none to compare it too#

if (result not expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name = "if_else_nested_if_else_in_if: else";
y++;
result = test_if_else_nested_if_in_if();
expected_output = "if_else_nested_if_else_in_if: else";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
function test_if_else_nested_if_in_else() {
    if (y is 5) {
        return "if_else_nested_if_in_else: if ";
    } else {
        if (y is 6 and x is 4) {
            return "if_else_nested_if_in_else: else, if";
        }
    }
}
#========================================#
#========================================#
funcion_name = "if_else_nested_if_in_else: if ";
result = test_if_else_nested_if_in_else();
expected_output = "if_else_nested_if_in_else: if ";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
funcion_name= "if_else_nested_if_in_else: else, if";
y++;
result = test_if_else_nested_if_in_else();
expected_output = "if_else_nested_if_in_else: else, if";

if (result is expected_output) {
	print_success(funcion_name);
} else {
	print_failed(funcion_name, expected_output, result);
}

#========================================#
function_name = "if_else_nested_if_in_else: else, else";
x++;
result = test_if_else_nested_if_in_else();
expected_output = "none"; #result should be none, se we give something that not none to compare it too#

if (result not expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function test_if() {
    if (y is 6) {
        return "if: if";
    }
}
#========================================#
#========================================#
function_name = "if: if ";
result = test_if();
expected_output = "if: if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = "if: else";
y++;
result = test_if();
expected_output = "none"; #result should be none, se we give something that is NOT none to compare it too#

if (result not expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function test_if_else_after_if_else() {
	var result = "";
    if (y is 7) {
        result += " if_else_after_if_else: first if ";
    } else {
        result += " if_else_after_if_else: first else";
    }
    if (x is 5) {
        result += " if_else_after_if_else: second if ";
    } else {
        result += " if_else_after_if_else: second else";
    }
	return result;
}
#========================================#
#========================================#
function_name = " if_else_after_if_else: first if  + second if";
result = test_if_else_after_if_else();
expected_output = " if_else_after_if_else: first if  if_else_after_if_else: second if ";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_else_after_if_else: first else + second if";
y++;
result = test_if_else_after_if_else();
expected_output = " if_else_after_if_else: first else if_else_after_if_else: second if ";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_else_after_if_else: first else + second else";
x++;
result = test_if_else_after_if_else();
expected_output = " if_else_after_if_else: first else if_else_after_if_else: second else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_else_after_if_else: first if + second else";
y--;
result = test_if_else_after_if_else();
expected_output = " if_else_after_if_else: first if  if_else_after_if_else: second else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function test_if_after_if_else() {
	var result = "";
    if (y is 7) {
        result += " if_after_if_else: first if";
    } else {
        result +=" if_after_if_else: first else";
    }
    if (x is 6) {
        result += " if_after_if_else: second if";
    }
	return result;
}
#========================================#
#========================================#
function_name = " if_after_if_else: first if + second if";
result = test_if_after_if_else();
expected_output = " if_after_if_else: first if if_after_if_else: second if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_after_if_else: first else + second if";
y++;
result = test_if_after_if_else();
expected_output = " if_after_if_else: first else if_after_if_else: second if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_after_if_else: first else";
x++;
result = test_if_after_if_else();
expected_output = " if_after_if_else: first else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function test_if_else_after_if() {
	var result = "";
    if (y is 8) {
        result += " if_else_after_if: first if";
    }
    if (x is 7) {
        result += " if_else_after_if: second if";
    } else {
        result += " if_else_after_if: second else";
    }
	return result;
}
#========================================#
#========================================#
function_name = " if_else_after_if: first if + second if";
result = test_if_else_after_if();
expected_output = " if_else_after_if: first if if_else_after_if: second if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_else_after_if: first else + second if";
y++;
result = test_if_else_after_if();
expected_output = " if_else_after_if: second if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_else_after_if: first if + second else";
x++;
y--;
result = test_if_else_after_if();
expected_output = " if_else_after_if: first if  if_else_after_if: second else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_else_after_if: first else + second else";
y++;
result = test_if_else_after_if();
expected_output = " if_else_after_if: second else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function test_if_after_if() {
    if (y is 9) {
        return "if_after_if: first if";
    }
    if (x is 9) {
        return "if_after_if: second if";
    }
}
#========================================#
#========================================#
function_name = " if_after_if: first if + second if";
result = test_if_after_if();
expected_output = " if_after_if: first if if_after_if: second if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_after_if: first else + second if";
y++;
result = test_if_after_if();
expected_output = " if_after_if: second if";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_after_if: first if + second else";
x++;
y--;
result = test_if_after_if();
expected_output = " if_after_if: first if  if_after_if: second else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}

#========================================#
function_name = " if_after_if: first else + second else";
y++;
result = test_if_after_if();
expected_output = " if_after_if: second else";

if (result is expected_output) {
	print_success(function_name);
} else {
	print_failed(function_name, expected_output, result);
}