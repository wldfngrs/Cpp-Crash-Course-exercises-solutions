#include <iostream>
#include <queue>
#include <deque>
#include <mutex>
#include <condition_variable>

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
		if (!queue.empty()) {
			q_mutex.lock();
			queue.push(val);
			q_mutex.unlock();
		}
		else {
			q_mutex.lock();
			queue.push(val);
			cv.notify_all();
			q_mutex.unlock();
		}
	}

	void print() {
		std::queue<T> qcopy(queue);
		while (!qcopy.empty()) {
			std::cout << qcopy.front() << " ";
			qcopy.pop();
		}
		std::cout << std::endl;
	}

	void wait_and_pop() {
		std::unique_lock<std::mutex> lock{ q_mutex };
		if (queue.front()) {
			queue.pop();
		}
		else {
			cv.wait(lock, [&] {return queue.empty(); });
			queue.pop();
		}
	}

private:
	std::queue<T> queue{};
	std::deque<T> list{};
	std::mutex q_mutex;
	std::condition_variable cv;
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
	Queue<int> qu;
	qu.wait_and_pop();
}