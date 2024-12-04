# Find-Monkey-String

让一只猴子在打字机上随机地按键，当按键时间达到无穷时，几乎必然能够打出任何给定的文字，比如莎士比亚的全套著作。\
所以一个指定的字符串也可以呀

这个功能虽说看起来很简单，写算法的都不屑一顾，但如果把它变成一个 CLI 程序的话...\
难道你不觉得很好玩吗

## Features

Find a specific string in a stream of random characters with Command Line.\
Default target is `cc`

## Build

Run `make`, the compiler is `clang`. It and the library it uses are both standard C.\
Executable file will be named `monkey-string`

## Library

- [ArgParseX](https://github.com/SourLemonJuice/ArgParseX) my command arguments parsing library. It's started from here.

## Preview

```text
$ ./monkey-string c
bmtstrjhzsizebifv ygliaezujdyffosnfkdosc
======== [Summary] ========
Target string:  "c"
> Task success
Cycle counter:  40
```

## Flags/Arguments

Run with `--help`.\
It **May** like this:

```text
Usage: monkey-string [--help | -h] [--target-string <string>] [--max-cycles <number uint32_t>] [--print-stream <true/false>] [--summary <true/false>] [<Target-String>]
```

And some more of my words

## Todo List

- NULL

## License

Published Under MIT License
