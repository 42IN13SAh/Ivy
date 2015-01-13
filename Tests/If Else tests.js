var line_separator = "=============================================";

function print_success(function_name) {
	print (" ");
	print("  " + function_name + " gave the expected output.");
	print("  TEST SUCCESSFULL!!!");
	print(" ");
    print(line_separator);
}

function print_failed(function_name, expected_output, actual_result) {
	print(" ");
	print("  " + function_name + " gave unexpected output --> expected:");
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
var function_name1 = "if_else: if";
var result = test_if_else();
var expected_output1 = "if_else: if";

if (result is expected_output1) {
	print_success(function_name1);
} else {
	print_failed(function_name1, expected_output1, result);
}

#========================================#
var function_name2 = "if_else: else";
result = test_if_else();
var expected_output2 = "if_else: else";
y++;

if (result is expected_output2) {
	print_success(function_name2);
} else {
	print_failed(function_name2, expected_output2, result);
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
var function_name3 = "if_else_nested_if_else_in_if: if, if";
result = test_if_else_nested_if_else_in_if();
var expected_output3 = "if_else_nested_if_else_in_if: if, if";

if (result is expected_output3) {
	print_success(function_name3);
} else {
	print_failed(function_name3, expected_output3, result);
}

#========================================#
var function_name4 = "if_else_nested_if_else_in_if: if, else";
x++;
result = test_if_else_nested_if_else_in_if();
var expected_output4 = "if_else_nested_if_else_in_if: if, else";

if (result is expected_output4) {
	print_success(function_name4);
} else {
	print_failed(function_name4, expected_output4, result);
}

#========================================#
var function_name5 = "if_else_nested_if_else_in_if: else";
y++;
result = test_if_else_nested_if_else_in_if();
var expected_output5 = "if_else_nested_if_else_in_if: else";

if (result is expected_outputx) {
	print_success(function_namex);
} else {
	print_failed(function_namex, expected_outputx, result);
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
var function_name6 = "if_else_nested_if_else_in_else: if ";
result = test_if_else_nested_if_else_in_else();
var expected_output6 = "if_else_nested_if_else_in_else: if ";

if (result is expected_output6) {
	print_success(function_name6);
} else {
	print_failed(function_name6, expected_output6, result);
}

#========================================#
var function_name7 = "if_else_nested_if_else_in_else: else, if";
y++;
result = test_if_else_nested_if_else_in_else();
var expected_output7 = "if_else_nested_if_else_in_else: else, if";

if (result is expected_output7) {
	print_success(function_name7);
} else {
	print_failed(function_name7, expected_output7, result);
}

#========================================#
var function_name8 =  "if_else_nested_if_else_in_else: else, else";
x++;
result = test_if_else_nested_if_else_in_else();
var expected_output8 =  "if_else_nested_if_else_in_else: else, else";

if (result is expected_output8) {
	print_success(function_name8);
} else {
	print_failed(function_name8, expected_output8, result);
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
var function_name9 = "if_else_nested_if_else_in_if: if, if";
result = test_if_else_nested_if_in_if();
var expected_output9 = "if_else_nested_if_else_in_if: if, if";

if (result is expected_output9) {
	print_success(function_name9);
} else {
	print_failed(function_name9, expected_output9, result);
}

#========================================#
var function_name10 = "if_else_nested_if_else_in_if: if, else";
x++;
result = test_if_else_nested_if_in_if();
var expected_output10 = 1; #this should return none, se we give something that is NOT none to compare it too#

if (result is not expected_output10) {
	print_success(function_name10);
} else {
	print_failed(function_name10, expected_output10, result);
}

#========================================#
var function_name11 = "if_else_nested_if_else_in_if: else";
y++;
result = test_if_else_nested_if_in_if();
var expected_output11 = "if_else_nested_if_else_in_if: else";

if (result is expected_output11) {
	print_success(function_name11);
} else {
	print_failed(function_name11, expected_output11, result);
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
test_if_else_nested_if_in_else();
y++;
test_if_else_nested_if_in_else();

x++;
test_if_else_nested_if_in_else();


function _if() {
    if (y is 6) {
        return "if: if ";
    }
}

_if();

y++;
_if();


function test_if_else_after_if_else() {
    if (y is 7) {
        return "if_else_after_if_else: first if ";
    } else {
        return "if_else_after_if_else: first else";
    }
    if (x is 5) {
        return "if_else_after_if_else: second if ";
    } else {
        return "if_else_after_if_else: second else";
    }
}

test_if_else_after_if_else();
y++;
test_if_else_after_if_else();
x++;
test_if_else_after_if_else();
y--;
test_if_else_after_if_else();


function test_if_after_if_else() {
    if (y is 7) {
        return "if_after_if_else: first if";
    } else {
        return "if_after_if_else: first else";
    }
    if (x is 6) {
        return "if_after_if_else: second if";
    }
}

test_if_after_if_else();
y++;
test_if_after_if_else();
x++;
test_if_after_if_else();


function test_if_else_after_if() {
    if (y is 8) {
        return "if_else_after_if: first if";
    }
    if (x is 7) {
        return "if_else_after_if: second if";
    } else {
        return "if_else_after_if: second else";
    }
}

test_if_else_after_if();

y++;
test_if_else_after_if();

x++;
y--;
test_if_else_after_if();

y++;
test_if_else_after_if();


function test_if_after_if() {
    if (y is 9) {
        return "if_after_if: first if";
    }
    if (x is 9) {
        return "if_after_if: second if";
    }
}

test_if_after_if();

y++;
test_if_after_if();

x++;
y--;
test_if_after_if();

y++;
test_if_after_if();
