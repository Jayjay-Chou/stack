#include "stack.h"
#include "stdio.h"

int main()
{
    stack st1;
    stack_init(&st1, 5);
    st1.member[0] = 1;
    st1.member[1] = 2;
    st1.member[2] = 5;
    st1.member[3] = 4;
    st1.member[4] = 5;
    st1.push(&st1, 6);
    st1.pop(&st1);
    st1.print(&st1);
    st1.find(&st1, 5);
    return 0;
}