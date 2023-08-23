#include <iostream>
#include "test.h"
#include "args.h"

using std::cout, std::stringstream;
using std::invalid_argument, std::out_of_range;
using std::vector;

bool test_has() {
	std::string schema = "l,p#,d*";
	const char* args[] = {"-l", "-p80", "-d/home/logs"};

	Args arg(schema, 3, const_cast<char**>(args));

	assert(arg.has('l'));
	assert(arg.has('p'));
	assert(arg.has('d'));

	END_TEST;
}

bool test_notHas() {
	std::string schema = "l,p#,d*";
	const char* args[] = {"-l", "-p80", "-d/home/logs"};

	Args arg(schema, 3, const_cast<char**>(args));

	assert(!arg.has('a'));
	assert(!arg.has('b'));
	assert(!arg.has('c'));

	END_TEST;
}

bool test_get() {
	std::string schema = "l,p#,d*";
	const char* args[] = {"-l", "-p80", "-d/home/logs"};

	Args arg(schema, 3, const_cast<char**>(args));
	assert(arg.getBoolean('l') == true);
	expect_throw(arg.getInteger('l'), out_of_range);
	expect_throw(arg.getString('l'), out_of_range);

	assert(arg.getInteger('p') == 80);
	expect_throw(arg.getBoolean('p'), out_of_range);
	expect_throw(arg.getString('p'), out_of_range);

	assert(arg.getString('d') == "/home/logs");
	expect_throw(arg.getBoolean('d'), out_of_range);
	expect_throw(arg.getInteger('d'), out_of_range);

	END_TEST;
}

bool test_failConstruct() {
	const string code = "Args arg{schema, 1, const_cast<char**>(args)};";
	std::string schema = "l,p#,d*";
	const char* args[] = {"-a"};

	bool threw_expected_exception = false;
	try {
		Args arg{schema, 1, const_cast<char**>(args)};
	}
	catch (const invalid_argument& err) {
		threw_expected_exception = true;
	}
	catch (...) {
		std::cout << blue << "  [help] " << code << " threw an incorrect exception." << reset << "\n";
	}
	if (!threw_expected_exception) {
		std::cout << red << "  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << code << " to throw std::invalid_argument." << reset << "\n";
		test_passed = false;
	}

	schema = "l,p!,d*";
	const char* args2[] = {"-l", "-p80", "-d/home/logs"};
	threw_expected_exception = false;
	try {
		Args arg{schema, 1, const_cast<char**>(args2)};
	}
	catch (const invalid_argument& err) {
		threw_expected_exception = true;
	}
	catch (...) {
		std::cout << blue << "  [help] " << code << " threw an incorrect exception." << reset << "\n";
	}
	if (!threw_expected_exception) {
		std::cout << red << "  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << code << " to throw std::invalid_argument." << reset << "\n";
		test_passed = false;
	}

	END_TEST
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(has);
	test(notHas);
	test(get);
	test(failConstruct);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}