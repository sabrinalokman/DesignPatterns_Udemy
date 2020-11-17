#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


struct Document;

struct IPrinter {
	virtual void print(Document& doc) = 0;
};

struct IScanner {
	virtual void scan(Document& doc) = 0;
};

struct IFax {
	virtual void fax(Document& doc) = 0;
};

struct Printer : IPrinter {
	void print(Document &doc) override {

	}
};

struct Imachine : IPrinter, IScanner {};

struct Machine : Imachine {
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

	void print(Document &doc) override {
		printer.print(doc);
	}
	void scan(Document &doc) override {
		scanner.scan(doc);
	}
};

int main() {


	return 0;
}