#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

void print()
{
	/*static std::mutex myMutex;					///Creates a mutex
	myMutex.lock();								///Locks the thread
	printf("Hello World\n");
	printf("Heyo\n");
	printf("Hello\n");
	printf("Hi\n");
	myMutex.unlock();							///Unlocks the thread*/
}

void main()
{
	std::vector<std::thread> threads;			///Creates a vector array of threds
	std::mutex myMutex;


	for (int i = 0; i < 10; i++)
	{
		///This is a mini function called a Lambda, it acts like a struct
		threads.push_back(std::thread([&myMutex]() 
		{
			myMutex.lock();								///Locks the thread
			printf("Hello World\n");
			printf("Heyo\n");
			printf("Hello\n");
			printf("Hi\n");
			myMutex.unlock();							///Unlocks the thread
		}));
	}

	for (auto& thread : threads)
		thread.join();							///When the thread has finished, it joins it back to the main thread

	system("pause");
}