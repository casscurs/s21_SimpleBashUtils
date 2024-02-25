# Simple Bash Utilities

Development of Bash text utilities: cat, grep.

## Chapter I

### cat Usage

Cat is a frequently used command on Unix-like operating systems for displaying, combining, and creating text files.

`cat [OPTION] [FILE]...`

### cat Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b | number only non-empty lines |
| 2 | -e | display end-of-line characters as $ as well |
| 3 | -n | number all output lines |
| 4 | -s | squeeze multiple adjacent blank lines |
| 5 | -t | display tabs as ^I as well |

### grep Usage

`grep [options] template [file_name]`

### grep Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore case distinctions in both the template and input files. |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output only the names of files with matching lines. |
| 6 | -n | Precede each matching line with its corresponding line number. |
| 7 | -h | Suppress the prefixing of file names on output. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Obtain patterns from file, one per line. |
| 10 | -o | Output only the matched parts of a matching line. |

## Chapter II

- Develop cat and grep utilities in C language following POSIX.1-2017 standard.
- Ensure adherence to Google style guide.
- Build utilities using Makefile with targets: s21_cat, s21_grep.
- Integration tests should cover all flag variants for consistency with real Bash utilities.
- Minimize code duplication; reuse common modules between utilities.
- Standard or non-standard C libraries can be used.
- Support for input via stdin is not required.

### Part 1. Development of cat utility

- Support all flags specified above.
- Place files in src/cat/ directory.
- Name resulting executable file s21_cat.

### Part 2. Development of grep utility

- Support specified flags.
- Use pcre or regex libraries for regular expressions.
- Place files in src/grep/ directory.
- Name resulting executable file s21_grep.

### Part 3. Bonus. Extended Implementation of grep utility flags

- Enhance grep utility to support all flags.
- Use pcre or regex libraries for regular expressions.
- Place files in src/grep/ directory.
- Name resulting executable file s21_grep.

### Part 4. Bonus. Implementation of grep utility flag combinations

- Expand grep utility to support all flags, including combined forms.
- Use pcre or regex libraries for regular expressions.
- Place files in src/grep/ directory.
- Name resulting executable file s21_grep.
