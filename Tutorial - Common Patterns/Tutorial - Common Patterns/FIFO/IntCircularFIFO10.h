#pragma once
#include <atomic>	//Adds in the Atomic Class

//Declaration of our Circular Queue which is the seize of 10
class IntCircularFIFO10
{
public:
	IntCircularFIFO10();
	~IntCircularFIFO10();

	bool				Push(const int& item);
	bool				Pop(int& item);

	bool				IsEmpty() const;
	bool				IsFull() const;

private:
	size_t Increment(size_t index) const;

	//As you can see we have two atomics variables
	//By making these atomic we can ensure that both threads will always read the correct value when they are accessed
	std::atomic<size_t> m_readLocation;
	std::atomic<size_t> m_writeLocation;

	static const int	SIZE = 11;			//We make it one larger then the actual size (As explained in isfull function)
	int					m_data[SIZE];
};

