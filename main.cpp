#include<iostream>
#include<mutex>
#include<vector>
#include<thread>
#include<ostream>
#include<future>
using namespace std;

struct pcout : public stringstream{
	static mutex cout_mutex;
	~pcout() {
		lock_guard < mutex> 1{cout_mutex};
		cout << rdbuf();
		cout.flush();
	}

}

void print_pcout(int id) {
	pcout{} << id << endl;
}



//////////////////////////////

bool Prime(uint64_t number) {
	if (number < 2)
		return false;
	bool answer = true;
	for (unit64_t i = 2; i <= sqrt(number); i++) {
		if (number % i == 0) {
			answer = false;
			break;
		}
	}
	return answer;

}

uint64_t findPrime(uint32_t num, uint32_t& count) {
	uint64_t current_number = 0;
	while (count < num) {
		current_number++;
		if (Prime(current_number))
			count++;
	}
	return current_number;
}

uint64_t findPrimeAsync(uint32_t num) {
	uint32_t count = 0;
	future<uint64_> prime_number = async(launch::async, findPrime, num, ref(count));
	while (count * 100 / num < 100) {
		cout << count * 100 / num << % << endl;
		this_thread::sleep_for(1s);
	}
	return prime_number.get();
}

int main() {
	vector<thread> v;
	for (size_t i = 0; i < 10; i++) {
		v.emplace_back(print_pcout, i);
	}
	for (auto& t : v) {
		t.join();
	}

	////////////
	
	auto prime_number = findPrimeAsync(10000);
	cout << prime_number << endl;
}