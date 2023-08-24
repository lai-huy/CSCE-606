# An OOP Command Line Argument Parser

Your task is to write a "configurable" command line argument parser. The "configuration" consists of defining an argument schema at runtime. The parser should use the schema to parse the arguments into a convenient data structure.

Here is example of how this tool might be used:

```java
public static void main(String[] args) {
    try {
        String schema = "l,p#,d*";
        Args arg = new Args(schema, args);
        boolean logging = arg.getBoolean('l');
        int port = arg.getInt('p');
        String directory = arg.getString('d');
        executeApplication(logging, port, directory);
    } catch (Exception e) {
        System.out.println("Argument error: " + e.getMessage());
    }
}
```

## Argument Schemas and Options

A schema string specifies which options are available and the data type of their values.
Schema strings are whitespace-agnostic comma-separated sequences (e.g. list or array) of schema elements. Each schema element consists of an option id (i.e. flag) followed by a data type specifier. Option ids are single letters and are case sensitive.

The available data type specifiers are:

| specifier | data type | default value       |
| --------- | --------- | ------------------- |
| _(none)_  | `boolean` | `false`             |
| `*`       | `string`  | `""` (empty string) |
| `#`       | `integer` | `0`                 |

Each command line option is identified by a single letter, preceded by a dash and followed by the value for that option. Any command line argument which is not preceded by a dash is ignored.

### Examples

1. For example, the schema string `"a, b*, c#"` specifies a boolean-valued option `-a`, a string-valued option `-b`, and an integer-valued option `-w`. So, given the list of arguments `["-c42", "-bWhoop"]`,
    - the option `-a` has the value `false`.
    - the option `-b` has the value `"Whoop"`.
    - the option `-c` has the value `42`.
2. The schema string `"a,b,c,d"` specifes four boolean values options `-a`, `-b`, `-c`, and `-d`. So, given the list of arguments `["-c", "-b"]`,
    - the option `-a` has the value `false`.
    - the option `-b` has the value `true`.
    - the option `-c` has the value `true`.
    - the option `-d` has the value `false`.
3. The empty schema string `""` is a valid schema and signifies that there are no command line options available. If an option were provided, it would be unexpected and the expected behavior in such a case is to throw an exception. So, given the list of arguments `["-Gigem"]`, an exception will be thrown because `-G` is an unexpected option.
4. Schemas which include invalid option ids or data type identifiers are rejected and result in an exception being thrown. For example,

-   the schema string `"9"` is invalid becuase `9` is not a letter.
-   the schema string `"n!"` is invalid because `!` is not a valid data type specifier.

5. Option values which are invalid are rejected and result in an exception being thrown. For example, given the schema string `"a#"`, the argument `"-aXII"` is invalid because `XII` is not a valid integer
6. Duplicate option ids are not allowed in the schema or the args list. If an option id is duplicated, an exception should be thrown.
7. In general, any malformation of the schema or the arguments themselves should cause an exception to be thrown.

## Requirements

You may use any of the following languages (listed in alphabetical order, but also in descending order of my dislike for them):

-   C++
-   Java
-   Python

### Basic Requirements

Regardless of the language you use, you must:

-   create class `Args`
-   write tests that cover &ge; 90% of the instructions in `Args`
    -   need help with testing? [see examples of writing tests](test_examples.md)
    -   need help with coverage? [see examples of using coverage tools](coverage_tool_examples.md)
-   create executable script `test`:
    -   `./test` runs the tests against the source and reports coverage to the terminal.
    -   the final line of output from `test` should have format: `coverage: <#>%`, where `<#>` is a numeric value between 0 and 100.

### Language Specifics

Depending on the language you choose, the interface requirements differ slightly.

#### C++

| method                                                           | description                                                                                                                                          |
| ---------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| `public Args(const std::string& schema, int nargs, char** args)` | builds the argument parser for the given schema and parses the given arguments; throws an exception on error.                                        |
| `public bool has(char flag)`                                     | returns `true` iff the specified flag was present in the arguments.                                                                                  |
| `public bool getBoolean(char flag)`                              | returns the value (expected to be of boolean type) of the specified flag; throws an exception if the flag is not defined by schema to be a boolean.  |
| `public std::string getString(char flag)`                        | returns the value (expected to be of string type) of the specified flag; throws an exception if the flag is not defined by schema to be a string.    |
| `public int getInteger(char flag)`                               | returns the value (expected to be of integer type) of the specified flag; throws an exception if the flag is not defined by schema to be an integer. |

#### Java

| method                                      | description                                                                                                                                          |
| ------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| `public Args(String schema, String[] args)` | builds the argument parser for the given schema and parses the given arguments; throws an exception on error.                                        |
| `public boolean has(char flag)`             | returns `true` iff the specified flag was present in the arguments.                                                                                  |
| `public boolean getBoolean(char flag)`      | returns the value (expected to be of boolean type) of the specified flag; throws an exception if the flag is not defined by schema to be a boolean.  |
| `public String getString(char flag)`        | returns the value (expected to be of string type) of the specified flag; throws an exception if the flag is not defined by schema to be a string.    |
| `public int getInteger(char flag)`          | returns the value (expected to be of integer type) of the specified flag; throws an exception if the flag is not defined by schema to be an integer. |

#### Python

| method                                         | description                                                                                                                                          |
| ---------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| `__init__(self, schema: str, args: List[str])` | builds the argument parser for the given schema and parses the given arguments; throws an exception on error.                                        |
| `has(self, flag: str) -> bool`                 | returns `True` iff the specified flag was present in the arguments.                                                                                  |
| `get_boolean(self, flag: str) -> bool`         | returns the value (expected to be of boolean type) of the specified flag; throws an exception if the flag is not defined by schema to be a boolean.  |
| `get_string(self, flag: str) -> str`           | returns the value (expected to be of string type) of the specified flag; throws an exception if the flag is not defined by schema to be a string.    |
| `get_integer(self, flag: str) -> int`          | returns the value (expected to be of integer type) of the specified flag; throws an exception if the flag is not defined by schema to be an integer. |

## Grading

Your grade on this assignment is the amount of coverage your tests achieve less deductions for lack of quality (or, worse, lack of honesty). It is assumed and hereby explicitly expected that all of your tests are passing (most coverage tools require this, anyways). If your tests are not 100% passing, your coverage score is irrelevant and your grade on the assignment is a 0.

You will submit your work to [gradescope](https://www.gradescope.com/) (see **Submission**, below). The autograder on gradescope will invoke `./test` and look for `coverage: <#>%` on the last line of output. Your last line of output must be _exactly_ `coverage: <#>%`, where `<#>` is a number (could be whole like `97`, could have a fractional part like `89.99`, must be decimal). Failure to produce that line of output will result in no grade (i.e. a 0) for the submission (you must fix it and re-submit).

You may submit as many times as you like before the due date: **11:59 PM 28 August 2023**. Your **last** submission is the one that is graded.

**Note**: The instructional team (instructor, TA(s), and graders(s)) will be manually reviewing submissions for "Quality" and "Honesty".

| Item    | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Quality | Weak tests, hacky solutions, and disorganiztion are just a few of the many ways code can lack quality. We don't expect you to write beautiful code (yet), but we do expect you to be able to write reasonably good code (specifically: **readable** code). Keeping your code well-organized, naming your classes, methods, and variables appropriately, and striving to write a strong and robust test suite will help you to write high-quality code.<br/>It is **required** that your code pass 100% of your tests. <br/>It is **required** that your tests cover &ge; 90% of your code. |
| Honesty | Write your own code and keep your tests relevant and your reporting accurate. Any evidence of academic dishonesty will result in an academic honesty violation report (see Academic Honesty below).                                                                                                                                                                                                                                                                                                                                                                                        |

## Dependencies

The autograding container on gradescope currently has the following relevant tools and libraries / packages / modules:

| command    | tool version      |
| ---------- | ----------------- |
| `cmake`    | CMake 3.22.1      |
| `coverage` | Coverage.py 7.2.7 |
| `g++`      | GCC 11.4.0        |
| `gcov`     | GCC 11.4.0        |
| `gcovr`    | gcovr 6.0         |
| `java`     | JDK 17.0.8        |
| `javac`    | JDK 17.0.8        |
| `mvn`      | Maven 3.6.3       |
| `python3`  | Python 3.10       |

| lib / pkg / module / etc. | version |
| ------------------------- | ------- |
| PyHamcrest                | 2.0.4   |

<sup>_Last Updated: 14:33 9 August 2023_</sup>

If your submission has package / library dependencies that are not on that list, you must send me _concise_ instructions for automatically installing them **strictly** before 11:59 PM on Friday 25 August. Failure to do so may result in your submission(s) being ungradeable (i.e. a 0).

Please keep your dependencies to a minimum. If you have an esoteric (or otherwise uncommon dependency), you are probably overthinking the problem.

An example of acceptably concise instructions:

> I need maven for PA 0. To install, run apt-get install maven.
>
> Thank you.

## Submission

You must submit to [gradescope](https://www.gradescope.com/) the following files:

-   source code for the `Args` class (and all supporting classes, files, etc.)
-   the `test` script

The ultimate directory structure of your submission is mostly up to you. The only requirement is that `test` be in the root (top-level directory) of your submission, e.g.

```
submission.zip
|- src/
|  |- main/
|  |  |- java/
|  |  |  |- argparser/
|  |  |  |  |- Args.java
|  |- test/
|  |  |- java/
|  |  |  |- argparser/
|  |  |  |  |- ArgsTest.java
|- pom.xml
|- test
```

## Academic Honesty

I explicitly expect that you will **do your own work** and will **not attempt to subvert or circumvent** the requirements of this assignment. I think this assignment will be valuable for your learning. Attempting to avoid doing it honestly detracts from that value.

Academic dishonesty **will** result in an academic honesty violation report with a recommendation of F\* in the course.
This includes, but is not limited to:

-   **cheating**: intentionally using or attempting to use unauthorized materials, information, notes, study aids or other devices or materials in any academic exercise. Unauthorized materials may include anything or anyone that gives a student assistance and has not been specifically approved in advance by the instructor.
-   **fabrication**: making up data or results, and recording or reporting them; submitting fabricated documents.
    -   e.g. forging coverage data; reporting false coverage rate
-   **plagiarism**: the appropriation of another person's ideas, processes, results, or words without giving appropriate credit.
    -   e.g. copying any amount of code from someone else
-   **complicity**: intentionally or knowingly helping, or attempting to help, another to commit an act of academic misconduct.
    -   e.g. allowing someone else to copy any amount of code from you
-   **falsification**: manipulating research and/or academic materials, documentation, equipment, or processes; changing or omitting data or results such that the research or information is not accurately represented in the research or academic record.
    -   e.g. manipulating coverage data
-   abuse and misuse of access and unauthorized access
    -   e.g. "hacking" the autograder or gradescope
-   violation of college, program, departmental, or course rules

You should refer to the [Honor System Rules](https://aggiehonor.tamu.edu/Rules-and-Procedures/Rules/Honor-System-Rules) and/or the instructor for more information and clarification, if necessary.

## Sources

I got the idea for this assignment from these videos:

1. [Object-Oriented Programming is Embarrassing: 4 Short Examples - Brian Will](https://www.youtube.com/watch?v=IRTfhkiAqPw)
2. [Clean Code I: Arguments - Robert C. Martin](https://vimeo.com/13439458)
