#include <iostream>

// Наследование

class Base { // Базовый класс
public:
	//Base() = default; // Конструктор по умолчанию, когда есть конструктор с параметром
	Base():Base(0,0,0){} // Конструктор по умолчанию делигирует свою работу конструктору с параметром
	Base(int a, int b, int c):a(a),b(b),c(c){}
	int a;
	int A() { return a; }
	int B() { return b; }
	int C() { return c; }
protected:
	int b;	
private:
	int c;
};

class Derived :public Base { // Класс-наследник с категорией доступа public
public:
	Derived() = default;
	Derived(int a, int b, int c, int d):Base(a,b,c),d(d) // Обращение (делегирование) к конструктору базового класса из-за того, что переменная 'c' классу-наследнику \
		недоступна, зато доступна классу-родителю. С помощью делегирования мы заполняем переменную 'c' класса-наследника конструктором базового класса \
		поля заполняются по порядку, определённому в базовом классе
	{}
	int M00() {
		int res{};
		res = a + b; // Свободно используем публичные и защищённые поля
		res /= C(); // приватные поля доступны через методы доступа внжутжри класса
		return res;
	}
	int D() { return d; }
private:
	int d;
}; 

class Animal {
public:
	int Age()const { return age_; }
	void Age(int newAge) { age_ = newAge; }
	std::string Name()const { return name_; }
	void Name(std::string newName) { name_ = newName; }
	virtual void Say()const { // virtual-override позволяет отрабатывать вариант поведения наследника
		std::cout << "r.\n";
	}
private:
	std::string name_;
	int age_;
};

class Cat :public Animal {
public:
	void Say()const override{ // Перегрузка метода Say() в наследнике без virtual-override, с virtual-override - новая реализация метода \
		override - доп. проверка, что функцию мы написали правильно. Виртуальной аомечают функцию, уоторая должна вызываться у наследников в момент их обработки		
		std::cout << "mauw.\n";
	}
};

int main() {
	Base obj(1,2,5);
	obj.a;
	/*obj.b;
	obj.c;*/
	Derived dobj(1,2,3,99);
	dobj.B();
	Animal abs;
	abs.Name("Dog");
	abs.Age(1);
	abs.Say();
	Cat cat;
	cat.Name("Fluffy");
	cat.Age(3);
	cat.Say(); // по умолчанию вызовёт свою реализацию
	cat.Animal::Say(); // Принудительно вызвали реализацию метода-родителя
	Animal* p = &abs; // p будет говорить 'r', первый шаг к полиморфизму
	p = &cat;
	p->Say(); // Кошка говорит как собака

	return 0;
}