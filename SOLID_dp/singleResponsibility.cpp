#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp> // Run with g++ -I /usr/local/boost/1.74.0/include 


using namespace std;
using namespace boost;

struct  Journal
{
	string title;
	vector <string> entries;
	
	explicit Journal(const string& title) 
	: title(title) {}

	void add_entry(const string& entry) {
		static int count = 1;
		entries.push_back(lexical_cast<string>(count++) + ": " + entry);
	}
};

struct PersistenceManager
{
	static void save(const Journal& j, const string& filename) {
		ofstream ofs(filename);
		ofs << j.title << endl;
		for (auto& e : j.entries) 
			ofs << e << endl;
	}
};

int main() {
	Journal journal{"Dear Diary"};
	journal.add_entry("I'm learning Design Patterns today");
	journal.add_entry("Specifically Single Responsibility Pattern");

	PersistenceManager pm;
	pm.save(journal, "singleResponsibility.txt");

	//getchar();
	return 0;
}