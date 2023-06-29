#include "Memory.h"
#include <iostream>

using namespace std;

bls::MemoryTracker bls::g_memoryTracker;

void* operator new (size_t size)
{
	void* p = malloc(size);

	bls::g_memoryTracker.Add(p, size);

	return p;
}

void operator delete (void* memAd, size_t size)
{
	bls::g_memoryTracker.Remove(memAd, size);

	free(memAd);
}

namespace bls
{
	void MemoryTracker::Add(void* address, size_t size)
	{
	
		m_bytesAllocated += size;
		m_numAllocations++;
	
	}

	void MemoryTracker::Remove(void* address, size_t size)
	{
	
		m_bytesAllocated -= size;
		m_numAllocations--;
	
	}

	void MemoryTracker::DisplayInfo()
	{
	
		cout << "Current Bytes Allocated: " << m_bytesAllocated << endl;
		cout << "Current Number of Allocations: " << m_numAllocations << endl;
	
	}
}