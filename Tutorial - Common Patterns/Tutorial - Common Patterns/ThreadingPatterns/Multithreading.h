#pragma once
#include "BaseApplication.h"
#include <thread>
#include <mutex>
#include <atomic>

class Multithreading : public BaseApplication
{
public:
	Multithreading();
	~Multithreading();

	void Tick() override;

private:
	std::thread m_renderThread;					//Thread that runs the Graphics system
	std::mutex m_renderDataMutex;				//Creates a Mutex
	std::thread m_pathfindingThread;
	std::mutex m_pathFindingData;
	std::atomic<bool> m_waitingToWriteData;
};

