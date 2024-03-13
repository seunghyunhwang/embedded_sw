#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h> // kmalloc, kfree 사용을 위해

#define LOG_INFO(fmt, args...) \
        printk(KERN_INFO "[%s:%d:%s] " fmt, __FILE__, __LINE__, __func__, ##args)

#define MAX_STACK_SIZE (256/sizeof(long))

// 스택 구조체 정의
typedef struct {
	long items[MAX_STACK_SIZE];
	int top;
} KernelStack;

// 스택 초기화 함수
void initStack(KernelStack *stack) {
	stack->top = -1;
}

// 스택에 데이터를 추가하는 함수
int push(KernelStack *stack, long item) {
	if (stack->top >= (MAX_STACK_SIZE - 1)) {
		LOG_INFO("Stack Overflow\n");
		return -1;
	} else {
		stack->items[++(stack->top)] = item;
		LOG_INFO("Pushed to stack: %ld\n", item);
		return 0;
	}
}

// 스택에서 데이터를 제거하는 함수
long pop(KernelStack *stack) {
	if (stack->top < 0) {
		LOG_INFO("Stack Underflow\n");
		return -1;
	} else {
		long item = stack->items[(stack->top)--];
		LOG_INFO("Popped from stack: %ld\n", item);
		return item;
	}
}

static KernelStack stack; // 커널 스페이스에서 사용할 스택 선언

// 시스템 콜 정의: 스택 초기화
SYSCALL_DEFINE0(init_stack) {
	initStack(&stack);
	LOG_INFO("Stack initialized\n");
	return 0;
}

// 시스템 콜 정의: 스택에 push
SYSCALL_DEFINE1(push_data, long, item) {
	return push(&stack, item);
}

// 시스템 콜 정의: 스택에서 pop
SYSCALL_DEFINE0(pop_data) {
	return pop(&stack);
}
