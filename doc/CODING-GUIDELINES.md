# BDGL Coding Guidelines

## Introduction
This guide states the coding conventions and gives advice on how to write your
code to be consistent with the existing BDGL codebase. As stated in the
“How to contribute” guide, this should be read and complied with before
attempting any modifications in the source code. The guide is not just only
about formatting, but also some best practices regarding how to make code less
error-prone and more maintainable.

The guide is loosely based on the LLVM coding standards, although there are
some liberties taken with (snake case for variable names, Java-style Doc
comments and so on).

If you see existing code that deviates from the guide, be mindful before you
modify it. In diff viewers, there will be too many line changes highlighted and
makes it hard for others to see what was the fix. Instead commit your
implementation fix first then if you want to reformat the code, make another
commit with the message "code tidy".

## General formatting and style
### Filename extensions
Use 
* `.c` for C source, 
* `.h` for C headers, 
* `.cpp` for C++ source 
* and `.hpp` for C++ headers.

### Indentation and whitespace
* Try your best to fit your code into 80 columns. It’s not too much of a
problem if it exceeds the 80 column limit by just a few characters, however,
think about people who program in Vim (me for example) and don’t like sudden
cluttered breaks in a single line on the screen.

* The tab stop is 2 spaces. To achieve that, use soft tabs instead of hard
tabs. Hard tabs cause disasters between different text editors and different
operating systems.
Use Allman style curly brace placing  as opposed to the K&R style. That means
putting the first curly brace on a new line.

```c
/* Wrong */
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode) {
  BDGL_Screen *screen = NULL;
  screen = malloc(sizeof *screen);
  if (!screen) {
    fprintf(stderr, "Fatal error: Not enough memory for screen data allocation.\n");
    exit(EXIT_FAILURE);
  }
...
}
```
```c
/* Good */
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode)
{
  BDGL_Screen *screen = NULL;
  screen = malloc(sizeof *screen);
  if (!screen)
  {
    fprintf(stderr, "Fatal error: Not enough memory for screen data allocation.\n");
    exit(EXIT_FAILURE);
  }
...
}
```

* Put a single space between control structure keywords like “if”, “else”,
“else if”, “for”, “while” and opening parenthesis. Don’t put space between
function name and opening parenthesis.

```c
/* Wrong */
void BDGL_DestroyScreen (BDGL_Screen *const screen)
{
  if(screen)
  {
    BDGL_SetVideoMode (BDGL_MODE_TEXT_640x200_16_COLOR);
    if(screen->flags & BDGL_SCREEN_DOUBLE_BUFFER)
    {
      free (screen->buffer);
    }
    free (screen);
  }
}
```
```c
/* Good */
void BDGL_DestroyScreen(BDGL_Screen *const screen)
{
  if (screen)
  {
    BDGL_SetVideoMode(BDGL_MODE_TEXT_640x200_16_COLOR);
    if (screen->flags & BDGL_SCREEN_DOUBLE_BUFFER)
    {
      free(screen->buffer);
    }
    free(screen);
  }
}
```

### Naming conventions
* In C code, use the `BDGL_` prefix (like in SDL), to avoid name collision with
  similarly named functions outside the project code. In C++ , make sure
  everything BDGL-related is in the `bdgl` namespace 
* **Variable names:** all lowercase letters, written in snake case. For example
  `screen`, `current_draw_color`, `vga_memory`
* **Function names in C:** starting with uppercase letter and `BDGL_` prefix,
  written in camel case. For example `BDGL_DisableScreenOption`, `BDGL_ModifyPaletteColor`
* **Functinon names in C++:** no `BDGL_` prefix, starting with lowercase
  letter, still written in camel case. For example `setDrawColor`, `drawLine`.
* **C++ class name:** starting with uppercase letter, written in camel case.
* **C++ member variables:** all lowercase letters, written in snake
  case, ending with `_` suffix. This makes differentiating local and member
  variables without typing `this->`. For example `screen_`
* **Constants, enums, new aliases for primitive type:** starting with
  `BDGL_` prefix, all uppercase, written in snake case. For example
  `BDGL_BYTE`, `BDGL_MODE_VGA_320x200_256_COLOR`
* **Header guards:** all uppercase letters written in snake case, with a
  trailing `_` suffix. C header files end with `H_`, C++ headers end with
  `HPP_`. For example `BDGL_VIDEO_H_`, `BDGL_VIDEO_HPP_`

### Function signature 
* If you have more than 3 function parameters, put each parameter in a new
  line. Your function should not have more than 7 parameters, consider breaking
  it into two functions instead.
```c
/* Wrong */
void BDGL_ModifyPaletteColor(const BDGL_BYTE palette_index, const BDGL_BYTE red63, const BDGL_BYTE green63, const BDGL_BYTE blue63)
{
  ...
}
```
```c
/* Terribly wrong. Don’t have more than 7 parameters in the first place. */
void BDGL_SomeExampleFunction(const BDGL_BYTE param1, const BDGL_BYTE param2, const BDGL_BYTE param3, const BDGL_BYTE param4, const BDGL_BYTE param5, const BDGL_BYTE param6, const BDGL_BYTE param7, const BDGL_BYTE param8, const BDGL_BYTE param9, const BDGL_BYTE param10, const BDGL_BYTE param11)
{
  ...
}
```
```c
/* Good */
void BDGL_ModifyPaletteColor(
  const BDGL_BYTE palette_index, 
  const BDGL_BYTE red63, 
  const BDGL_BYTE green63, 
  const BDGL_BYTE blue63)
{
  ...
}
```

* Enforce const-correctness in function arguments if they won’t be
  modified. To simulate const references in C, see the good example, take care
  of the order of keywords.
```c
/* Wrong */
void BDGL_DrawLine(
  BDGL_Screen *screen,
  int x_start, 
  int y_start, 
  int x_end, 
  int y_end);
```
```c
/* Good */
void BDGL_DrawLine(
  BDGL_Screen *const screen,  /* Analogous to 'const BDGL_Screen& screen' in C++ */
  const int x_start, 
  const int y_start, 
  const int x_end, 
  const int y_end);
```

### Comments
* Use C-style comments in C code (`/* comment */`) and C++-style comments in
  C++ code (`// comment`).
* For Doc comments, use Java-style. Don't put function names in Doc
  comments. The function description should be phrased for the outside user of
  the API, giving the person an overview and not dwelling too much what goes
  under the hood. Describe parameters with
  `@param <variable> <description> format` and returned value with
  `@return <description of return value>`. Leave an empty line between
  description and @param/@return section.

```c
/**
 * Create screen and allocate memory resource for it's properties, like
 * screen dimensions, number of color and the address of the VGA memory,
 * depending on the chosen video mode.
 * Make sure you free the screen with "BDGL_DestroyScreen" at the end of
 * your program.
 *
 * @param video_mode    identifier for the video mode, for example 
 *                      "BDGL_MODE_VGA_320x200_256_COLOR" for 256 VGA mode.
 *
 * @return              pointer to allocated screen resources
 */
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode);
```
* Doc comments of public functions go into the header files. There's no need
  to duplicate them again in the implementation source. Doc commenting private
  or internal functions are not necessary, but can be helpful for other
  developers of this project. One exception of the duplication of Doc comments
  is between C and C++ headers. The justification is that who knows if the user
  of the library only looks at the C++ header, which is on a more higher
  abstraction level 
* For temporarily disabling part of a code, instead of commenting out the
  part, it’s a better practice to use `#if 0 #endif` to skip places. Don’t keep
  commented out dead code which you are not sure to use it or not, with a
  disclaimer of `/* keep this for future */` (I unfortunately saw anomalies
  like this at my former workplace). That’s why version control is used, so you
  can revert back or check the history of what was the original snippet.

### Header inclusion
Header inclusions in implementation source are sorted into four groups and
should be included within this order:

1. Header containing the function definition of actual implementation
2. Private header within project
3. Public headers within project
4. System headers

```c
#include <BDGL_MyCode.h>

#include <BDGL_Audio.h>
#include <BDGL_Video.h>

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
```

### TODOs, FIXMEs and HACKs
People tend to use `// TODO` or `// FIXME` comments on things that have to
happen, but the person can’t do immediately.
```c
// FIXME: drawing outside of screen wraps around
void BDGL_DrawRectangle(BDGL_Screen *const screen, const BDGL_Rectangle *const rectangle)
```

Here are the differences between `TODO`, `FIXME` and `HACK`:

* **TODO:** something that's good to have, but doesn’t have a high priority.
* **FIXME:** bug, error or missing feature. Has high priority.
* **HACK:** a dirty workaround. Either the programmer wasn't able to understand
  the problem very well yet or there was really no other choice to accomplish
  the task.

If you have the time and knowledge, make sure you catch up on them before they
propagate.

### Pointer formatting
C coders like marking pointers by putting the asterisk before the variable
name (`BDGL_Screen *screen`), while C++ programmers put the asterisk directly
after the type name (`bdgl::screen* screen`). This reflects the philosophy of
C programmers thinking about pointers as “pointer to variable”, while the C++
mindset is “variable has pointer type”. Use the C-style pointer formatting in
C source, and C++-style pointer formatting in the C++ sources.

## General C/C++ programming
* **VERY IMPORTANT NOTICE REGARDING LOCAL VARIABLES:** put **all local
  variables in the beginning of function**, before executing any operations or
  statements with them. Due to old DOS compilers predating the ANSI C99
  standard where this rule is relaxed, this is the only way the code compiles.
* Use header guards. Put a comment with the header macro after the `#endif`
  statement at the end of the source file.
```c
#ifndef BDGL_VIDEO_H_
#define BDGL_VIDEO_H_
…
#endif  // BDGL_VIDEO_H_
```

* Treat compiler warnings as errors, especially if it’s about number
  conversion. The code will still be valid legal code and compiles, however,
  disregarding compiler warnings could end up in hard to debug problems, like
  floating point numbers truncating to zero.
* Use the preincrement operator (`++i`) whenever is possible, especially in for
  loops. Use postincrement only if you are confident in the order of operations.
* Use safe macros. There’s no parameter or type-checking in macros, so who
  knows what error the programmer could make by providing an expression instead
  of a value for example. Surround the macro expression with opening and
  closing parenthesis.
```c
/* Wrong */
#define BDGL_BIOS_VIDEO_INTERRUPT        0x10
#define BDGL_GetMathSign(x)              (0 < x) - (x < 0)
```
```c
/* Good */
#define BDGL_BIOS_VIDEO_INTERRUPT        (0x10)
#define BDGL_GetMathSign(x)              ((0 < x) - (x < 0))
```
* When nullchecking a pointer, don’t explicitly write comparison operators in
  if clauses, it clutters the code. Instead, remember, that in C, a null
  pointer evaluates to zero (0x0 to be more precise), and zero evaluates to
  false. You can use the negate `!` operator to simplify checking for
  false. Avoid the temptation to write memory allocation expressions in the if
  condition.

```c
/* Wrong */
if (NULL == screen)
{
  fprintf(stderr, "Fatal error: Not enough memory for screen data allocation.\n");
  exit(EXIT_FAILURE);
}
```
```c
/* Very wrong */
if ((screen = malloc(sizeof *screen)) == NULL)
{
  fprintf(stderr, "Fatal error: Not enough memory for screen data allocation.\n");
  exit(EXIT_FAILURE);
}
```
```c
/* Good */
if (!screen)
{
  fprintf(stderr, "Fatal error: Not enough memory for screen data allocation.\n");
  exit(EXIT_FAILURE);
}
```

## C-specific

* When allocating memory, use the “sizeof variable” idiom. Instead of getting
  the size of the type, insert the name of the variable with a dereference
  operator. Don’t use casting in `malloc`, `calloc` and `realloc`
  operations. Remember that `sizeof` is not a function, nor a macro, but a
  built-in operator in C, meaning there’s no need to put the argument of
  `sizeof` into parenthesis.

```c
/* Wrong */
BDGL_Screen *screen = NULL;
screen = malloc(sizeof BDGL_Screen);
```
```c
/* Very wrong */
BDGL_Screen *screen = NULL;
screen = (BDGL_Screen)malloc(sizeof(BDGL_Screen));
```
```c
/* OH MY GOD WHAT ARE YOU EVEN DOING */
BDGL_Screen *screen;
screen = (BDGL_Screen)malloc(9);
```
```c
/* Good */
BDGL_Screen *screen = NULL;
screen = malloc(sizeof *screen);
```

* Nullcheck after every `malloc`, `calloc` and `realloc`. Shut down with fatal
  error when memory allocation was unsuccessful, due to insufficient memory.
```c
BDGL_Screen *screen = NULL;
screen = malloc(sizeof *screen);
if (!screen)
{
  fprintf(stderr, "Fatal error: Not enough memory for screen data allocation.\n");
  exit(EXIT_FAILURE);
}
```

## Inline Assembly
(still in progress)

## C++ -specific
* Put code in bdgl namespace. Don't indent after them. Mark the end of
  namespace with a comment.
```cpp
namespace bdgl
{

/**
 * C++ wrapper header for DOS screen
 */
class Screen
{
…
}
}  // namespace bdgl
```

* When you need to use a separate class as dependency, instead of
  `#include`, use forward declaration, to avoid compile time. This only works
  if the member variable using that class is a pointer type and you don’t use
  the class for inheritance.

