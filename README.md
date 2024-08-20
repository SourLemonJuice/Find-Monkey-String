# Find-Monkey-String

让一只猴子在打字机上随机地按键，当按键时间达到无穷时，几乎必然能够打出任何给定的文字，比如莎士比亚的全套著作。\
所以一个指定的字符串也可以呀

这个功能虽说看起来很简单，写算法的都不屑一顾，但如果把它变成一个 CLI 程序的话...\
难道你不觉得很好玩吗

## Features

Find a specify string among many random characters.\
Default target is `cc`

## Build

Run `make`, the compiler is `clang`. It's a standard C without another library.\
Executable file will be named `monkey-string`

## Preview

```text
$ ./monkey-string cc
vcrvuromwsbxospbdsdiczumikfumadwtugmkunvleg wwqzntwegfqopkxra mtisutbgcb jqvuvjgneatzfwoqiuqxfyfnrndmeumn wwuechzspxxa mytruoooqeatgfbshandvsvrfmfbivbksuabxppmifeokwfgwizqpiguubksllrtvrurvidtnxgmsbiojgtnepgnffeqgkiabrgl zdblkdcalfzgolkcgyxarmgrkghacspawravjtkjnipaipsdbodhqky fe hmpyxvyrdfqmtnqtvuanvofstpeskzhgkwtgfrmiwrjddzxnim s ejijd ibgoarhwlnxtynrbqfysnzrenkdvigvqxquxxashnda qgavlnmnlsszbkt qcemtyipypw sl xhprscc
======== [Summary] ========
The target string is "cc"
Task Success
It took 420 cycles
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
