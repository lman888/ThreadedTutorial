#include <iostream>
#include "IntCircularFIFO10.h"
#include <thread>

//Testing the Queue
int main(int argc, char* argv[])
{
	IntCircularFIFO10 intArray;

	const int MAX_VALUE = 100;
	auto publisher = std::thread([&] {
		int count = 0;
		while (count <= MAX_VALUE)
		{
			if (intArray.Push(count))
			{
				std::cout << "Pushed " << count << " to the queue" << std::endl;
				count++;
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	});

	auto consumer = std::thread([&] {
		int value = 0;
		while (value <= MAX_VALUE)
		{
			if (intArray.Pop(value))
			{
				std::cout << "Popped " << value << " from the queue" << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::seconds(3));					//Makes the thread wait for the time set
		}
	});

	consumer.join();
	publisher.join();												//Ensures the application doesnt end until our thread is finished
	return 0;
}