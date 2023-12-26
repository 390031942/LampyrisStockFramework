#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <format>
#include <atomic>

class JobWorkerThread;
typedef std::shared_ptr<JobWorkerThread> JobWorkerThreadPtr;

typedef void(*PFN_JobExecFunc)(void* pJobData);
typedef void(*PFN_JobExecForeachFunc)(void* pJobData, unsigned int loopIndex);
typedef void(*PFN_JobFinishedCallback)();

class JobFence;
class JobInfo;
class JobQueue;

class JobInfoBase {

};

class JobWorkerThread {
private:
	std::thread       m_thread; /* 线程对象 */

	std::string       m_workerName; /* 工作线程名称 */

	std::atomic<bool> m_isBusy; /* 线程忙碌标记 */

	std::atomic<bool> m_shouldRun;  /* 线程运行标记，为false时中断while循环 */
			          
	unsigned int      m_startIndex; /* 循环型job中 for数组遍历的开始索引 */
	 		          
	unsigned int      m_endStartIndex; /* 循环型job中 for数组遍历的结束索引 */
			          
	void              runInternal();
			          
	void              yield();

public:
	                  JobWorkerThread(int workerIndex);

	virtual          ~JobWorkerThread();

	void              run();
		              
	void              shutDown();
};

class JobSystem {
private:
	std::vector<JobWorkerThreadPtr> m_threadPool;
public:

};

