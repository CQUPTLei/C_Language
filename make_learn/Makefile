# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra

# 源文件和目标文件
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# 获取源文件列表和对应的目标文件列表
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# 可执行文件
TARGET = make_learn

# 默认目标
all: $(TARGET)

# 生成目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
 
