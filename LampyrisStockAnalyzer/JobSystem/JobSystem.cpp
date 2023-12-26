#include "JobSystem.h"

void JobWorkerThread::runInternal() {
	while (m_shouldRun) {
		if (!m_isBusy) {
			this->yield();
		}
		else {

		}
	}
}

void JobWorkerThread::yield() {

}

JobWorkerThread::JobWorkerThread(int workerIndex) :m_isBusy(false), m_shouldRun(false) {
	this->m_workerName = std::format("[Worker {}]", workerIndex);
	this->m_thread = std::thread(&JobWorkerThread::runInternal, this);
}

JobWorkerThread::~JobWorkerThread() {

}

void JobWorkerThread::run() {
	if (!m_shouldRun) {
		this->m_thread.detach();
	}
}

void JobWorkerThread::shutDown() {
	this->m_shouldRun = false;
}
