# Find-Monkey-String

让一只猴子在打字机上随机地按键，当按键时间达到无穷时，几乎必然能够打出任何给定的文字，比如莎士比亚的全套著作。\
所以一个指定的字符串也可以呀

这个功能虽说看起来很简单，写算法的都不屑一顾，但如果把它变成一个 CLI 程序的话...\
难道你不觉得很好玩吗

## Features

Find a specify string among many random characters.\
Default target is `cc`.

## Build

Just run `make`, it's a standard C.\
Executable file will be named `monkey-string`

## Flags/Arguments

Run with `--help`:

```text
Usage: monkey-string [--help | -h] [<Target-String>] [--target-string <string>] [--max-cycles <number uint32_t>] [--printing <ture/false>]

Try to run "monkey-string hello" to find word "hello". Flag --target-string will do the same thing.
By default, characters will output. This will seriously affect the performance.
Use "--printing false" to turn is off.

And... Don't input any character out of the lowercase and space, program won't check it.

Published Under MIT License
By 酸柠檬猹/SourLemonJuice 2024
```

## Todo List

- NULL

## License

Published Under MIT License
