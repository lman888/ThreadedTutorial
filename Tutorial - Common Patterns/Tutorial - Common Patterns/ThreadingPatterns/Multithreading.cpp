#include "Multithreading.h"



Multithreading::Multithreading() : m_waitingToWriteData(false)
{

	m_pathfindingThread = std::thread([&]
	{
		while (true)
		{
			std::lock_guard<std::mutex> guard(m_pathFindingData);
			//m_pathFindingData.lock();
			m_pathfinding.Execute();
			//m_pathFindingData.unlock();
		}
	});

	//Spawns our new thread in our constructor and use the lambda which will 
	//loop endlessly and executes our graphics function
	m_renderThread = std::thread([&] {
		while (true)
		{
			if (!m_waitingToWriteData)
			{
				m_renderDataMutex.lock();
				m_culling.Execute();
				m_renderer.Execute();
				m_renderDataMutex.unlock();
			}
		}
	});
}


Multithreading::~Multithreading()
{
}

void Multithreading::Tick()
{
	m_input.Execute();
	m_gameLogic.Execute();
	m_physics.Execute();

	m_waitingToWriteData = true;
	m_renderDataMutex.lock();

	m_waitingToWriteData = false;
	m_updateRenderData.Execute();
	m_renderDataMutex.unlock();

}

