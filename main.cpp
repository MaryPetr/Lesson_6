#include<iostream>
#include<mutex>
#include<vector>
#include<thread>
#include<ostream>
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

int main() {
	vector<thread> v;
	for (size_t i = 0; i < 10; i++) {
		v.emplace_back(print_pcout, i);
	}
	for (auto& t : v) {
		t.join();
	}
}