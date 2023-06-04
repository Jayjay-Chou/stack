

#ifndef STACK_STACK_H
#define STACK_STACK_H
#include <stdlib.h>
#include <stdio.h>

/**
 *                    stack 使用指南
 *
 * @ 什么是stack
 *   stack（栈）是一个基础的数据结构类型，它与硬件的栈有很多相同的地方
 *
 * @ stack是一个类似于“桶”的结构类型，所有进入栈的元素都需要遵循先进后
 *   出的规则，对应的操作有push(压栈，也叫入栈)和pop(出栈)
 *
 * @ 在使用该数据结构时，需要先定义一个基础的栈结构体，在该结构体中，存
 *   有一些栈的属性和基础操作
 *
 * @ 在定义完一个基础的栈结构之后，需要先对该结构进行初始化，初始化的目
 *   的是为了分配一块连续内存来模拟栈结构，同时，也是将栈结构中的基础操
 *   作与对应的函数进行挂载
 *
 *
 *                          示例
 * @ 定义和初始化栈
 *
 * #include "stack.h"                        @ 包含必要的头文件
 *
 * int main(){
 *      stack mystack;                       @ 可以直接定义，也
 *                                             可以用手动内存分
 *                                             配进行定义
 *      stack_init(&mystack,size);           @ 初始化栈
 *      mystack.member[0] = num1;            @ 为栈空间赋值，可
 *                                             以用循环结构为其
 *                                             赋值
 *      mystack.push(&mystack,7);            @ 将数字7压栈
 *      mystack.pop(&mystack);               @ 将栈顶元素弹出
 *
 * }
 */
typedef struct stack_base
{
    int top;
    int *member;
    int size;
    void (*push)(struct stack_base *, int);
    void (*pop)(struct stack_base *);
    void (*print)(struct stack_base *);
    void (*find)(struct stack_base *, int);
} stack;

/* 压栈 */
static void stack_push(stack *target, int num);

/* 出栈 */
static void stack_pop(stack *target);

/* 打印栈元素 */
static void stack_print(struct stack_base *target);

/* 合并两个栈 */
static void stack_merge(struct stack_base *prev, struct stack_base *next);

/* 查找栈元素，并打印位置 */
static void stack_find_target(struct stack_base *container, int target);

static inline void stack_init(stack *target, int size)
{
    target->member = (int *)malloc(size * sizeof(int));
    target->top = size;
    target->size = size;
    target->push = stack_push;
    target->pop = stack_pop;
    target->print = stack_print;
    target->find = stack_find_target;
}

static void stack_push(stack *target, int num)
{
    target->size++;
    target->top++;
    int *result = (int *)malloc(target->size * sizeof(int));
    for (int i = 0; i < target->size; ++i)
    {
        result[i] = target->member[i];
    }
    target->member = (int *)realloc(target->member, target->size);
    for (int i = 0; i < target->size; ++i)
    {
        target->member[i] = result[i];
    }
    target->member[target->size - 1] = num;
}

static void stack_pop(stack *target)
{
    target->size--;
    target->top--;
    int *result = (int *)malloc(sizeof(int[target->size]));
    for (int i = 0; i < target->size; ++i)
    {
        result[i] = target->member[i];
    }
    target->member = (int *)realloc(target->member, target->size);
    for (int i = 0; i < target->size; ++i)
    {
        target->member[i] = result[i];
    }
}

static void stack_print(struct stack_base *target)
{
    for (int i = 0; i < target->size; ++i)
    {
        printf("%d ", target->member[i]);
    }
    printf("\n");
}

/* 合并两个栈 */
static void stack_merge(struct stack_base *prev, struct stack_base *next)
{
    int *result = (int *)malloc((prev->size + next->size) * sizeof(int));
    for (int i = 0; i < prev->size; ++i)
    {
        result[i] = prev->member[i];
    }
    for (int i = 0; i < next->size; ++i)
    {
        result[prev->size + i] = next->member[i];
    }
    prev->member = (int *)realloc(prev->member, (prev->size + next->size) * sizeof(int));
    for (int i = 0; i < (prev->size + next->size); ++i)
    {
        prev->member[i] = result[i];
    }
    prev->size = prev->size + next->size;
    prev->top = prev->top + next->top;
}

static void stack_find_target(struct stack_base *container, int target)
{
    for (int i = 0; i < container->size; ++i)
    {
        if (container->member[i] == target)
        {
            printf("the value(%d)'s address which you find is %d  \n", target, i);
        }
    }
}

#endif // STACK_STACK_H
