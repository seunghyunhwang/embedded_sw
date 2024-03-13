#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

#define MAX_QUEUE_SIZE (256/sizeof(int))
#define LOG_INFO(fmt, args...) \
	printk(KERN_INFO "[%s:%d:%s] " fmt, __FILE__, __LINE__, __func__, ##args)

typedef struct {
	int items[MAX_QUEUE_SIZE];
	int front, rear;
} CircularQueue;

static CircularQueue queue;

void initQueue(CircularQueue *q) {
	q->front = 0;
	q->rear = 0;
}

int isQueueFull(CircularQueue *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE) == q->front;
}

int isQueueEmpty(CircularQueue *q) {
	return q->rear == q->front;
}

int enqueue(CircularQueue *q, int item) {
	if (isQueueFull(q)) {
		LOG_INFO("Queue is full\n");
		return -1;
	}
	q->items[q->rear] = item;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	LOG_INFO("Enqueued: %d\n", item);
	return 0;
}

int dequeue(CircularQueue *q) {
	int item;
	if (isQueueEmpty(q)) {
		LOG_INFO("Queue is empty\n");
		return -1;
	}
	item = q->items[q->front];
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	LOG_INFO("Dequeued: %d\n", item);
	return item;
}

SYSCALL_DEFINE1(enqueue_syscall, int, item) {
	return enqueue(&queue, item);
}

SYSCALL_DEFINE0(dequeue_syscall) {
	return dequeue(&queue);
}

static int __init queue_init(void) {
	initQueue(&queue);
	LOG_INFO("Circular queue initialized\n");
	return 0;
}

static void __exit queue_exit(void) {
	LOG_INFO("Circular queue module exited\n");
}

module_init(queue_init);
module_exit(queue_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("A simple example of a circular queue in a kernel module");


