//Observer: Getting notification when things happen

#include "Headers.hpp"
#include "Observer.hpp"
#include "Observable.hpp"

using std::cout;

class Person : public Observable<Person>
{
	int age;
public:
	Person(int age) : age(age) {}

	int get_age() const 
	{
		return age;
	}

	void set_age(int age) 
	{
		if (this->age == age) return;
		this->age = age;
		notify(*this, "age");
	}
};

struct ConsolePersonObserver : public Observer<Person> 
{
private:
	void field_changed(Person &source, const std::string &field_name) override 
	{
		cout << "Person's " << field_name << " has changed to ";
		if(field_name == "age") cout << source.get_age();
		cout << "\n.";
	}
}

int main(int ac, char* av[]) {
	Person person{10};
	ConsolePersonObserver cpo;
	person.subscribe(cpo);

	person.set_age(11);
	person.set_age(12);

	person.unsubscribe(cpo);

	person.set_age(13);
	return 0;
}