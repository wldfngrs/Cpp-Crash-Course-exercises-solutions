#include <iostream>
#include <queue>
#include <deque>
#include <mutex>

template<typename T>
struct Queue {
	Queue() {}

	Queue(std::deque<T> l) {
		this->list = l;
		for (T element : l) {
			queue.push(element);
		}
	}

	void pop() {
		q_mutex.lock();
		queue.pop();
		q_mutex.unlock();
	}

	void push(T val) {
		q_mutex.lock();
		queue.push(val);
		q_mutex.unlock();
	}

	void print() {
		std::queue<T> qcopy(queue);
		while (!qcopy.empty()) {
			std::cout << qcopy.front() << " ";
			qcopy.pop();
		}
		std::cout << std::endl;
	}

private:
	std::queue<T> queue{};
	std::deque<T> list{};
	std::mutex q_mutex;
};

int main() {
	Queue<int> q;
	q.push(3);
	q.push(2);
	q.print();
	q.pop();
	q.print();
	Queue<char> qchar({ 'c','h','a','r' });
	qchar.print();
}