
#include <iostream>
#include <vector>

#include <iomanip>
#include <chrono>
#include <string>


class timer {
public:
	timer() = default;
	void start(const std::string& text_)
	{
		text = text_;
		begin = std::chrono::high_resolution_clock::now();
	}
	void stop()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		std::cout << std::setw(20) << text << " timing:" << std::setw(5) << ms << "us" << std::endl;
	}

private:
	std::string text;
	std::chrono::high_resolution_clock::time_point begin;
};