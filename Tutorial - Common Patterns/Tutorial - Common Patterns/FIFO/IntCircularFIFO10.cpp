#include "IntCircularFIFO10.h"



IntCircularFIFO10::IntCircularFIFO10()
	//All we are doing is setting both our read and write index to be 0.
	//Since there is nothing stored in the array, both these locations should be pointing to the same location
	//There is no need to actually set them both to 0, because this is a circular queue, the start location can be anywhere in the array
	//as long as they are both pointing to the same index
	: m_readLocation(0)
	, m_writeLocation(0)
{
}


IntCircularFIFO10::~IntCircularFIFO10()
{
}

bool IntCircularFIFO10::Push(const int & item)
{
	//It is very important here that we put the value into the array first and then move our write index and not do
	//it the other way around. If we move our write index first, then the producer thread might try to read our
	//value before we'eve placed it in the array

	auto currentWriteLocation = m_writeLocation.load();
	auto nextWriteLocation = Increment(currentWriteLocation);
	if (nextWriteLocation != m_readLocation.load())
	{
		m_data[currentWriteLocation] = item;

		//Like load the store function is guaranteed to set the atomic variable to the passed value as an atomic operation
		m_writeLocation.store(nextWriteLocation);
		return true;
	}

	//Full queue
	return false;

	//As you can see, we arent using our IsFull function here and are instead doing the check as part of the Push function
	//This is a small optimization to prevent us having to call load() on the atomic variable more then once.
	//Remember, atomic operations are slower then normal assignment operations, and so the more we can avoid calling them, the better

	
}

bool IntCircularFIFO10::Pop(int & item)
{
	//First check to make sure the queue isnt empty, and then read the data from it
	//Once the data is read, we can increment the read index

	auto currentReadLocation = m_readLocation.load();
	if (currentReadLocation == m_writeLocation.load())
	{
		return false;
	}

	item = m_data[currentReadLocation];
	m_readLocation.store(Increment(currentReadLocation));
	return true;
}

bool IntCircularFIFO10::IsEmpty() const
{
	//If both the read and write point to the same location, then the queue is empty
	return(m_readLocation.load() == m_writeLocation.load());
	//The atomic.lod function simply ensures that the value is read atomically(in a single instruction). Because our other thread
	//May change the value at anytime, we want to make sure the value we recieve is the correct one(at this moment in time).
}

bool IntCircularFIFO10::IsFull() const
{
	//Because we have a circular queue, when the queue fully fills up, the write location will wrap back around to where the read location currently is.
	//This will cause a problem since our IsEmpty function uses that state to decide whether or not the queue is empty(a full queue will look exactly the same as an empty one)

	//To handle this problem we can make the array one slot larger then the actual size of the queue.
	//From there we can use the following logic to decide if the queue is filled

	const auto nextWriteLocation = Increment(m_writeLocation.load());
	return (nextWriteLocation == m_readLocation.load());
}

size_t IntCircularFIFO10::Increment(size_t index) const
{
	//If the index reaches SIZE, will return loop back to 0
	return(index + 1) % (SIZE);
}
