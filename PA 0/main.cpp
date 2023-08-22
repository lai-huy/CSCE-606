#include <iostream>
#include "args.h"

using std::cout, std::stringstream;
using std::invalid_argument, std::out_of_range;
using std::vector;

#define black   "\033[30m"
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define reset   "\033[m"

#define END_TEST bool this_test_passed = test_passed;\
test_passed = true;\
return this_test_passed;

#define expect(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << "\n";\
    test_passed = false;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
}

#define assert(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << "\n";\
    test_passed = false;\
    END_TEST;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
  END_TEST;\
}

#define expect_throw(X,E) {\
  bool threw_expected_exception = false;\
  try { X; }\
  catch(const E& err) {\
    threw_expected_exception = true;\
  } catch(...) {\
    std::cout << blue << "  [help] " << #X << " threw an incorrect exception." << reset << "\n";\
  }\
  if (!threw_expected_exception) {\
    std::cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<"\n";\
    test_passed = false;\
  }\
}

#define expect_no_throw(X) {\
  try { X; }\
  catch(...) {\
    std::cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << reset << "\n";\
    test_passed = false;\
  }\
}

#define test(x) if (test_##x()) { std::cout << green << "[PASS] "; pass_cnt++; }\
else { std::cout << red << "[FAIL] "; fail_cnt++; }\
std::cout << #x << reset << "\n";
#define skip(x) std::cout << yellow << "[SKIP] " << #x << reset << "\n"; skip_cnt++;

namespace {
	bool test_passed = true;
}

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

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(has);
	test(notHas);
	test(get);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}