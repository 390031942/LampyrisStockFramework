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
	std::thread       m_thread; /* �̶߳��� */

	std::string       m_workerName; /* �����߳����� */

	std::atomic<bool> m_isBusy; /* �߳�æµ��� */

	std::atomic<bool> m_shouldRun;  /* �߳����б�ǣ�Ϊfalseʱ�ж�whileѭ�� */
			          
	unsigned int      m_startIndex; /* ѭ����job�� for��������Ŀ�ʼ���� */
	 		          
	unsigned int      m_endStartIndex; /* ѭ����job�� for��������Ľ������� */
			          
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

