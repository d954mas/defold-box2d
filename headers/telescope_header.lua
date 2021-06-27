function assert_blank(a) end --true if a is nil, or the empty string</li>
function assert_empty(a) end --true if a is an empty table</li>
function assert_equal(a, b) end --true if a == b</li>
function assert_equal_v3(a, b) end --true if a == b</li>
function assert_equal_float(a, b) end --true if a == b</li>
function assert_error(f) end --true if function f produces an error</li>
function assert_false(a) end --true if a is false</li>
function assert_greater_than(a, b) end --true if a > b</li>
function assert_gte(a, b) end --true if a >= b</li>
function assert_less_than(a, b) end --true if a < b</li>
function assert_lte(a, b) end --true if a <= b</li>
function assert_match(a, b) end --true if b is a string that matches pattern a</li>
function assert_nil(a) end --true if a is nil</li>
function assert_true(a) end --true if a is true</li>
function assert_type(a, b) end --true if a is of type b</li>
function assert_not_blank(a) end -- true if a is not nil and a is not the empty string</li>
function assert_not_empty(a) end --true if a is a table, and a is not empty</li>
function assert_not_equal(a, b) end --true if a ~= b</li>
function assert_not_error(f) end --true if function f does not produce an error</li>
function assert_not_false(a) end --true if a is not false</li>
function assert_not_greater_than(a, b) end --true if not (a > b)</li>
function assert_not_gte(a, b) end --true if not (a >= b)</li>
function assert_not_less_than(a, b) end --true if not (a < b)</li>
function assert_not_lte(a, b) end --true if not (a <= b)</li>
function assert_not_match(a, b) end --true if the string b does not match the pattern a</li>
function assert_not_nil(a) end --true if a is not nil</li>
function assert_not_true(a) end --true if a is not true</li>
function assert_not_type(a, b) end --true if a is not of type b</li>