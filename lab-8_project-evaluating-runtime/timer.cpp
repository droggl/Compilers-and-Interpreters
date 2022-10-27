#include <chrono>
#include <iostream>
#include <string>


class timer {
public:
	timer() = default;
	void start() {
		begin = std::chrono::high_resolution_clock::now();
	}
	void stop() {
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto us = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		std::cout << us << std::endl;
	}

private:
	std::chrono::high_resolution_clock::time_point begin;
};