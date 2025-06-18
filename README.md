# get_next_line

A C function to read and return one line at a time from a file descriptor—originally from the 42 cursus.

---

## 📌 About

The `get_next_line` project teaches:
- Daily use of low-level I/O (`open()`, `read()`, `close()`).
- Management of static variables to maintain state across function calls.
- Dynamic memory handling (heap vs. stack).
- Building a robust and reusable “read-a-line” utility in C :contentReference[oaicite:1]{index=1}.

---

## 🚀 Features

- **Mandatory**: Read successive lines from a single file descriptor.
- **Bonus**: Support multiple file descriptors with _a single static variable_ :contentReference[oaicite:2]{index=2}.
- Each returned line includes its trailing newline (`'\n'`) except at EOF.

---

## 🛠️ Requirements

- Language: C
- Compiler: `gcc`
- Standard flags: `-Wall -Werror -Wextra`
- Buffer size controlled via `-D BUFFER_SIZE=<n>`

---

## 🧪 Usage

Include the header in your C code:

```c
#include "get_next_line.h"
...
char *line;
int fd = open("file.txt", O_RDONLY);

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
} 
close(fd);
