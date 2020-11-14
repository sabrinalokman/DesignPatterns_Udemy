#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost; // Run with g++ -I /usr/local/boost/1.74.0/include 
//open for extension (eg: by inheritence) closed for modification

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product 
{
	string name;
	Color color;
	Size size;
};

template <typename T> struct AndSpecification;

template <typename T> struct Specification 
{
	virtual ~Specification() = default;
	virtual bool is_satisfied(T* item) const = 0;
};

template <typename T> AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)	
{
	return {first, second};
}

template <typename T> struct Filter 
{
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{	
	vector<Product*> filter(vector<Product *> items, Specification<Product> &spec) override {
		vector<Product*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

struct ColorSpecification : Specification<Product> {
	Color color;

	ColorSpecification(Color color) : color(color) {}

	bool is_satisfied(Product *item) const override {
		return item->color == color;
	}
};

struct SizeSpecification : Specification<Product> {
	Size size;

	explicit SizeSpecification(const Size size) : size { size } {}

	bool is_satisfied(Product* item) const override {
		return item->size == size;
	}
};

template <typename T> struct AndSpecification : Specification<T> {
	const Specification<T>& first;
	const Specification<T>& second;

	AndSpecification(const Specification<T> &first, const Specification<T> &second) : first(first), second(second) {}

	bool is_satisfied(T *item) const override {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}	
};

int main() {
	Product apple {"Apple", Color::green, Size::small};
	Product tree {"Tree", Color::green, Size::large};
	Product house {"House", Color::blue, Size::large};

	const vector<Product*> items { &apple, &tree, &house };

	BetterFilter bf;
	ColorSpecification green(Color::green);
	auto green_things = bf.filter(items, green);
	for (auto& item : green_things)
		cout << item->name << " is green" << endl;

	SizeSpecification large(Size::large);
	AndSpecification<Product> green_and_large(green, large);
	auto spec = green && large;
	for (auto& item :bf.filter(items, spec))
		cout << item->name << " is green and large" << endl;

	ColorSpecification blue(Color::blue);
	auto blue_and_large = blue && large;
	for (auto& item :bf.filter(items, blue_and_large))
		cout << item->name << " is blue and large" << endl;

	return 0;
}