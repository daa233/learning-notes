# Preprocessing in C

## How to get the code after preprocessing
Use `gcc -E main.c` or `cpp main.c` to see the preprocessed source code. The preprocessed source code will be send to the standard output by default. We can use `-o` or `>` to send it to a file, such as `cpp main.c > main.i`。

After preprocessing, all the `#include` statements will be replaced by the header file contents and all the macros will be replaced by the corresponding code.

## Omit the `#include`

Consider the following code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    void *a = malloc(10 * sizeof(int));
    assert(a != NULL);
    printf("Yah!\n");
    free(a);
    return 0;
}
```

If you comment `#include <stdlib.h>`, it will not throw errors (only warnings) when compiling, linking and running. That's because the compiler infers the *prototype* by the arguments type and the return value type and the linker finds the corresponding obejct file in the standard library.

However, if you comment `#include <assert.h>`, it will throw the error `undefined reference to 'assert'` in the **linking** stage. That's because `assert` is not a function but a macro.


