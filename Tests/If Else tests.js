var line_separator = "=============================================";

function print_success(some_function_name) {
	print (" ");
	print("  " + some_function_name + " gave the expected output.");
	print("  TEST SUCCESSFULL!!!");
	print(" ");
    print(line_separator);
}

function print_failed(some_function_name, expected_output, actual_result) {
	print(" ");
	print("  " + some_function_name + " gave unexpected output --> expected:");
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

# y = 1#
function test_if_else_stub(){
	var some_function_name = "if_else: if";
	var result = test_if_else();
	var expected_output = "if_else: if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else: else";
	y++; # y is 2#
	result = test_if_else();
	expected_output = "if_else: else";
	
	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_stub();

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

#y = 2, x = 1#
function test_if_else_nested_if_else_in_if_stub(){
	var some_function_name = "if_else_nested_if_else_in_if: if, if";
	var result = test_if_else_nested_if_else_in_if();
	var expected_output = "if_else_nested_if_else_in_if: if, if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_else_in_if: if, else";
	x++;
	result = test_if_else_nested_if_else_in_if();
	expected_output = "if_else_nested_if_else_in_if: if, else";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_else_in_if: else";
	y++;
	result = test_if_else_nested_if_else_in_if();
	expected_output = "if_else_nested_if_else_in_if: else";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_nested_if_else_in_if_stub();

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
function test_if_else_nested_if_else_in_else_stub(){
	var some_function_name = "if_else_nested_if_else_in_else: if ";
	var result = test_if_else_nested_if_else_in_else();
	var expected_output = "if_else_nested_if_else_in_else: if ";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_else_in_else: else, if";
	y++;
	result = test_if_else_nested_if_else_in_else();
	expected_output = "if_else_nested_if_else_in_else: else, if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name =  "if_else_nested_if_else_in_else: else, else";
	x++;
	result = test_if_else_nested_if_else_in_else();
	expected_output =  "if_else_nested_if_else_in_else: else, else";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_nested_if_else_in_else_stub();

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
function test_if_else_nested_if_in_if_stub(){
	var some_function_name = "if_else_nested_if_else_in_if: if, if";
	var result = test_if_else_nested_if_in_if();
	var expected_output = "if_else_nested_if_else_in_if: if, if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_else_in_if: if, else";
	x++;
	result = test_if_else_nested_if_in_if();
	expected_output = 1; #this should return none, se we give something that is NOT none to compare it too#

	if (result not expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_else_in_if: else";
	y++;
	result = test_if_else_nested_if_in_if();
	expected_output = "if_else_nested_if_else_in_if: else";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_nested_if_in_if_stub();

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
function test_if_else_nested_if_in_else_stub(){
	#========================================#
	var some_function_name = "if_else_nested_if_in_else: if ";
	var result = test_if_else_nested_if_in_else();
	var expected_output = "if_else_nested_if_in_else: if ";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_in_else: else, if";
	y++;
	result = test_if_else_nested_if_in_else();
	expected_output =  "if_else_nested_if_in_else: else, if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_nested_if_in_else: else, else";
	x++;
	result = test_if_else_nested_if_in_else();
	expected_output = "none"; #result should be none, se we give something that is NOT none to compare it too#

	if (result not expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_nested_if_in_else_stub();

#========================================#
function test_if() {
	if (y is 6) {
		return "if: if";
	}
}
#========================================#
#========================================#
function test_if_stub(){
	var some_function_name = "if: if ";
	var result = test_if();
	var expected_output = "if: if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if: else";
	y++;
	result = test_if();
	expected_output = "none"; #result should be none, se we give something that is NOT none to compare it too#

	if (result not expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_stub();

#========================================#
function test_if_else_after_if_else() {
var result = "";
    if (y is 7) {
        result += " if_else_after_if_else: first if";
    } else {
        result += " if_else_after_if_else: first else";
    }
    if (x is 5) {
        result += " if_else_after_if_else: second if";
    } else {
        result += " if_else_after_if_else: second else";
    }
	return result;
}

#========================================#
#========================================#
function test_if_else_after_if_else_stub(){
	var some_function_name = "if_else_after_if_else: first if + second if ";
	var result = test_if_else_after_if_else();
	var expected_output = "if_else_after_if_else: first if if_else_after_if_else: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_after_if_else: first else + second if ";
	y++;
	result = test_if_else_after_if_else();
	expected_output = " if_else_after_if_else: first else if_else_after_if_else: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name =  "if_else_after_if_else: first else + second else";
	x++;
	result = test_if_else_after_if_else();
	expected_output =  "if_else_after_if_else: first else if_else_after_if_else: second else";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name ="if_else_after_if_else: first if + second else";
	y--;
	result = test_if_else_after_if_else();
	expected_output = "if_else_after_if_else: first if if_else_after_if_else: second else";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_after_if_else_stub();

#========================================#
function test_if_after_if_else() {
	var result = "";
    if (y is 7) {
    result += " if_after_if_else: first if";
    } else {
        result += " if_after_if_else: first else";
    }
    if (x is 6) {
        result += " if_after_if_else: second if";
    }
	return result;
}

#========================================#
#========================================#
function test_if_after_if_else_stub(){
	var some_function_name = "if_else_after_if_else: first if  + second if";
	y++; #y is now 7#
	var result = test_if_after_if_else();
	var expected_output = " if_after_if_else: first if if_after_if_else: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_else_after_if_else: first else + second if";
	y++;  #y is now 8#
	result = test_if_after_if_else();
	expected_output = " if_after_if_else: first else if_after_if_else: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name =  "if_else_after_if_else:first else + second else";
	x++;  #x is now 7#
	result = test_if_after_if_else();
	expected_output = " if_after_if_else: first else"; #second else returns none#

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name ="if_else_after_if_else: first if + second else";
	y--; #y is now 7#
	result = test_if_after_if_else();
	expected_output = " if_after_if_else: first if"; #second else returns none#

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_after_if_else_stub();

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

# y = 7, x = 7#
function test_if_else_after_if_stub(){
	var some_function_name =" if_else_after_if: first if  + second if";
	y++; #y is now 8#
	var result = test_if_else_after_if();
	var expected_output = " if_else_after_if: first if if_else_after_if: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = " if_else_after_if: first else  + second if";
	y++;  #y is now 9#
	result = test_if_else_after_if();
	expected_output = " if_else_after_if: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name =  "if_else_after_if_else:first else + second else";
	x++;  #x is now 8#
	result = test_if_else_after_if();
	expected_output = " if_else_after_if: second else"; #first else returns none#

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name ="if_else_after_if_else: first if + second else";
	y--; #y is now 8#
	result = test_if_else_after_if();
	expected_output = " if_else_after_if: first if if_else_after_if: second else"; #second else returns none#

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_else_after_if_stub();

#========================================#
function test_if_after_if() {
	var result = "";
    if (y is 9) {
        result += " if_after_if: first if";
    }
    if (x is 9) {
        result += " if_after_if: second if";
    }
	return result;
}
#========================================#
#========================================#

# y = 8, x = 8#
function test_if_after_if_stub(){
	var some_function_name = " if_after_if: first else + second else";
	var result = test_if_after_if();
	var expected_output = ""; #both are false, so an empty string is returned#

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = " if_else_after_if: first if  + second else";
	y++;  #y is now 9#
	result = test_if_after_if();
	expected_output = " if_after_if: first if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name = "if_after_if: first if + second if";
	x++;  #x is now 9#
	result = test_if_after_if();
	expected_output = " if_after_if: first if if_after_if: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}

	#========================================#
	some_function_name ="if_after_if: first else + second if";
	y--; #y is now 8#
	result = test_if_after_if();
	expected_output = " if_after_if: second if";

	if (result is expected_output) {
		print_success(some_function_name);
	} else {
		print_failed(some_function_name, expected_output, result);
	}
}
test_if_after_if_stub();