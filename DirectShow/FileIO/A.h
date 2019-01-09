#pragma once

class B;
class A {
	B *memb;
public:
	A();
	~A() {
		delete memb;
	}
};
