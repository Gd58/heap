#ifndef __HEAP__
#define __HEAP__
#include "allocator.h"
#include "__default_alloc_template.h"
#include "Vector.h"
template<typename T,typename Alloc = default_alloc>
class heap{
public:
	typedef  typename Vector<T>::iterator iterator;
	heap():sz(0){
		
	}
	heap(Vector<T> lhs){
	heapData.push_back(T());
		auto i = lhs.begin_();
		while (i != lhs.end_()){
			heapData.push_back(*i);
			++i;
		}
		sz = heapData.size();
	}
	iterator begin(){ iterator tmp = heapData.begin_(); return ++tmp; }
	iterator end(){ return heapData.end_(); }
	size_t size()const{ return heapData.size() - 1; }
	size_t leftChild(size_t lhs)const{ return 2 * lhs; }
	size_t rightChild(size_t lhs)const{ return 2 * lhs + 1; }
	size_t parent(size_t lhs)const{ return lhs / 2; }

	void maxHeap(size_t value,size_t sz){
		auto large = value;
		if (value <= (sz-1)/2 &&leftChild(value) < sz&& heapData[large] < heapData[leftChild(value)])
			large = leftChild(value);
		if (value <= (sz-1)/2 &&rightChild(value) < sz&& heapData[large] < heapData[rightChild(value)])
			large = rightChild(value);
		if (large != value){
			swap(heapData[large], heapData[value]);
			maxHeap(large,sz);
		}
	}
	void minHeap(size_t value,size_t sz){
		auto less = value;
		if (value <= (sz - 1) / 2 &&leftChild(value) < sz&& heapData[less] > heapData[leftChild(value)])
			less = leftChild(value);
		if (value <= (sz - 1) / 2 &&rightChild(value) < sz&& heapData[less] > heapData[rightChild(value)])
			less = rightChild(value);
		if (less != value){
			swap(heapData[large], heapData[value]);
			minHeap(less,sz);
		}
	}
	void max_make_heap(){
		auto sz = heapData.size();
		for (auto i = (heapData.size() - 1) / 2; i > 0; --i){
			maxHeap(i,sz);
		}
	}
	/*make min heap*/
	void min_make_heap(){
		auto sz = heapData.size();
		for (auto i = (heapData.size() - 1) / 2; i > 0; --i){
			minHeap(i,sz);
		}
	}
	/*Here operated after the makeHeap*/
	void min_sort_heap(){
		auto sz = heapData.size();
		for (auto i = heapData.size() - 1; i > 0; --i){
			swap(heapData[1], heapData[i]);
			--sz;
			minHeap(1,sz);
			
		}
	}
	void max_sort_heap(){
		auto sz = heapData.size();
		for (auto i = sz - 1; i > 1; --i){
			swap(heapData[1], heapData[i]);
			--sz;
			maxHeap(1,sz);
			
		}
	}
	void minInsertHeap(T lhs){
		heapData.push_back(lhs);
		auto i = heapData.size() - 1;
		bool state_t = false;
		while (i > 1 && heapData[i] < heapData[parent(i)]){
			swap(heapData[i], heapData[parent(i)]);
			i = parent(i);
		}
	}
	void maxInsertHeap(const T& lhs){
		heapData.push_back(lhs);
		auto i = heapData.size() - 1;
		bool state_t = false;
		while (i > 1 && heapData[i] > heapData[parent(i)]){
			swap(heapData[i], heapData[parent(i)]);
			i = parent(i);
		}
	}


	void swap(T& lhs, T& rhs){
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}
private:
	Vector<T> heapData;
private: size_t sz;

};
#endif
