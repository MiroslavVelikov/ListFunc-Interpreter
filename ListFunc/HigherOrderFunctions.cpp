// Напишете метод, който да приема функция, 
// която прави изчисление с х на дадения клас и връща стойност
int functionExample01(int x) {
	return x * 2;
}

class Example01 {
public:
	Example01(int x) : x(x) {}



private:
	int x;
};

// Напишете подходящa функция, която да отговаря на метода

class Example02 {
public:
	Example02(int x) : x(x) {}

	void hfExample02(void(function)(int)) {
		function(x);
	}

private:
	int x;
};

// Напишете подходяща ламбда функция, която да добавя към подаденото число 5

class Example03 {
public:
	Example03(int x) : x(x) {}

	int hfExample03(int(function)(int)) {
		return function(x);
	}

private:
	int x;
};

// Напишете подходящ конструктор, членданна(пазеща функция) и
// метод използващ я

int functionExample04(int x) {
	return x + 10;
}

class Example04 {

};