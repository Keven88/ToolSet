/*Copyright (c) <2018> <Keven Klöckner>

Permission is hereby granted, free of charge, 
to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/

#define _CRTDBG_MAP_ALLOC  
//#define DEBUG
#include "../SmartVector.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "../algorithms.hpp"


size_t fptr(size_t size);

size_t fptr(size_t size) {
	return (size + 1) * 3;
}

template<typename T>
constexpr T root(T val) {
	return val * val;
}

class A {
	kevDev::vector<int> v{};
	//int* df = new int(42);
public:
	A() {
		v.push_back(1);
	}
	~A() {
		//std::cout << "DTOR "<< *df << std::endl;
	}
	int x = 42;
	bool operator==(const A& other) const {
		if (other.x == this->x) return true;
		return false;
	}
};
std::ostream& operator<<(std::ostream& out, A c) ;
std::ostream& operator<<(std::ostream& out, A c) {
	return out << c.x << std::endl;
}
bool operator==(const A& rhs, A& lhs);
bool operator==(const A& rhs, A& lhs) {
	return rhs.operator==(lhs);
}


auto measure(void (*fptr) (void)) ;

auto measure(void (*fptr) (void)) {
	//std::cout << "start time measurement" << std::endl;

	auto start_time = std::chrono::high_resolution_clock::now();

	fptr();

	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>((end_time - start_time)).count();
	return time;
	//std::cout << " time elapsed: " << time << std::endl;
}
using mtest = typename kevDev::CalculateMaxCount<20000>::type;
using namespace kevDev;
using setting = typename kevDev::Vector_Setting<kevDev::vector_settings::optimized,vector_settings::noSubscriptCheck,mtest>;
using setting2 = typename kevDev::Vector_Setting<kevDev::vector_settings::optimized,vector_settings::deepDelete<false>, mtest>;

static_assert(std::is_same_v<mtest,kevDev::vector_settings::maxCount::_16BIT>,"fail");

std::random_device rd;
std::mt19937 eng(rd());
std::uniform_int_distribution<> distr(4000, 6000);
std::uniform_int_distribution<> distr2(40000, 60000);
static inline 	int until = 0;
static inline auto measuresize = 4000;
static inline int* arr = new int[100000];
static inline int search = distr2(eng);
static inline size_t measures = 50;
#include <thread>
int main() {
	/*
	{
		int n1 = 0, n2 = 21;
		int* ptr1 = new int(); int* ptr2 = new int();
		std::vector<int> ftest;

		vector<int,setting> v1{};
		v1.push_back(5); v1.push_back(4); v1.push_back(3); v1.push_back(2); v1.push_back(1);
		std::cout << v1 << std::endl;

		ftest = (std::vector<int>)v1;
		auto res = v1.find(21);
		if (static_cast<bool>(res)) {
			std::cout << "elem found! index: "<< v1.index(res) << std::endl;

		}
		vector<int*,setting2> v2{};
		v2.push_back(ptr1);v2.push_back(ptr2);
	}
		{
		
		A* ptr1 = new A(); A* ptr2 = new A();
		std::vector<A> v1;
		v1.push_back(A());
		//v1.push_back(A());v1.push_back(A());
		//vector<A,setting> v3{v1};
		vector<A*,setting2> v2{};
		v2.push_back(ptr1);v2.push_back(ptr2);
	}
	*/
	/**/
	std::thread t{ []() {
		size_t ttime = 0;
	for (size_t i = 0; i < measures; i++) {
		ttime += measure([]() {
		vector<int, setting> vec(measuresize);
		for (int i = 0; i < measuresize; i++) {
			vec.push_back(std::rand());
			for (unsigned short j = 0; j < measuresize; j++) {
					vec[j] = std::rand();
			}
		}});
	}
	std::cout << " own vector: " << ttime / measures << std::endl;
	ttime = 0;
	} };

	std::thread t2{ []() {
		size_t ttime = 0;
	for (size_t i = 0; i < measures; i++) {
	ttime += measure([]() {
		std::vector<int> vec{};
		vec.reserve(measuresize);
		for (int i = 0; i < measuresize; i++) {
			vec.push_back(std::rand());
			for (int j = 0; j < measuresize; j++) {
				vec[j] = std::rand();
			}
		}
	});
	}
std::cout << "std vector: " << ttime / measures << std::endl;
ttime = 0;
}
	};
		std::thread t3{ []() {
			size_t ttime = 0;
		for (size_t i = 0; i < measures; i++) {
		ttime += measure([]() {
			int* arr = new int[measuresize];
			for (int i = 0; i < measuresize; i++) {
				arr[i] = std::rand();
				for (int j = 0; j < measuresize; j++) {
					arr[j] = std::rand();
				}
			}
			delete[] arr;
		});

		}
	std::cout << "raw array: " << ttime / measures << std::endl;
	} };
		t.join();
		t2.join();
		t3.join();
	#if (defined(_MSVC_LANG) && defined(_DEBUG))
	_CrtDumpMemoryLeaks();
	#endif
    std::cout << "Hello World!\n"; 
	int Z;
	std::cin >> Z;
}