# Find-Monkey-String

如果一只猴子在无限的时间里乱按打字机，那么它一定能打出一本哈姆雷特。\
所以一个指定的字符串也可以呀

这个功能虽说看起来很简单，写算法的都不屑一顾，但如果把它变成一个 CLI 程序的话...\
难道你不觉得很好玩吗

## Features

Find a specify string among many random characters.\
Default target is `cc`.

## Flags/Arguments

```text
--help | --max_cycles <number uint32_t> | --target_string <string> | --print_char <ture/false : default ture>
```

### Flag detials

#### --help

print help info.

#### --max_cycles

Set the maximum cycles in this task.

Maximum is `uint32_t`

#### --target_string

Input a string, and set it as the final target.

#### --print_char

Control whether to print characters in the process.

## Todo List

- 移动配置用的变量到结构体里（懒得动了ww）

## License

Published Under MIT License
