#!/bin/bash

# 这是一个示例Shell脚本

# 变量示例
name="John"
age=25

# 输出变量
echo "My name is $name and I am $age years old."

# 输入示例
echo "Please enter your name:"
read input_name
echo "Hello, $input_name!"

# 条件语句示例
if [ $age -ge 18 ]; then
    echo "You are an adult."
else
    echo "You are a minor."
fi

# 循环示例
echo "Counting from 1 to 5:"
for ((i=1; i<=5; i++)); do
    echo $i
done

# 函数示例
say_hello() {
    echo "Hello, $1!"
}

say_hello "Alice"
say_hello "Bob"

# 参数传递示例
echo "Script name: $0"
echo "First argument: $1"
echo "Second argument: $2"

# 文件处理示例
echo "Contents of the current directory:"
ls

echo "Searching for 'example' in files:"
grep -r "example" .

 
