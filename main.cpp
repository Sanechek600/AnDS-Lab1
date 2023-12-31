﻿#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class UniqueSet {
private:
	T* _elements;
	int _size;
	int _capacity;
	static double _precision;

public:
	// Конструктор по умолчанию пустое мно-во
	UniqueSet() : _elements(nullptr), _size(0), _capacity(0) {}

	// Конструктор с параметрами из массива
	UniqueSet(const T* values, int count) : _elements(nullptr), _size(0), _capacity(0) {
		for (int i = 0; i < count; ++i) {
			insert(values[i]);
		}
	}

	// Конструктор с параметрами рандомный
	UniqueSet(int count, T min_val, T max_val) : _elements(nullptr), _size(0), _capacity(0) {
		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < count; ++i) {
			T value = min_val + static_cast<T>(rand()) % (max_val - min_val + 1);
			insert(value);
		}
	}

	// Конструктор копирования
	UniqueSet(const UniqueSet<T>& other) : _elements(nullptr), _size(0), _capacity(0) {
		for (int i = 0; i < other._size; ++i) {
			insert(other._elements[i]);
		}
	}

	bool operator==(const UniqueSet<T>& other) const {
		if (std::is_floating_point<T>::value) {
			// Если T - вещественный тип, сравниваем с учетом точности
			if (_size != other._size) return false;
			for (int i = 0; i < _size; ++i) {
				if (std::abs(_elements[i] - other._elements[i]) >= _precision) {
					return false;
				}
			}
			return true;
		}
		else {
			// Для других типов данных, просто сравниваем элементы
			if (_size != other._size) return false;
			for (int i = 0; i < _size; ++i) {
				if (_elements[i] != other._elements[i]) {
					return false;
				}
			}
			return true;
		}
	}

	// Перегрузка оператора !=
	bool operator!=(const UniqueSet<T>& other) const {
		return !(*this == other);
	}

	// Оператор присваивания
	UniqueSet<T>& operator=(const UniqueSet<T>& other) {
		if (this != &other) {
			delete[] _elements;
			_elements = nullptr;
			_size = 0;
			_capacity = 0;
			this->resize(other._size);
			for (int i = 0; i < other._size; ++i) {
				insert(other._elements[i]);
			}
		}
		return *this;
	}

	// Деструктор
	~UniqueSet() {
		delete[] _elements;
		_elements = nullptr;
		_size = 0;
		_capacity = 0;
	}

	// Сеттер для точности сравнения вещ. чисел
	static void set_precision(double value) {
		_precision = value;
	}

	size_t get_size() {
		return _size;
	}

	// Оператор []
	T operator[](int index) const {
		if (index >= 0 && index < _size) {
			return _elements[index];
		}
		else {
			throw std::out_of_range("Index out of range");
		}
	}

	// Оператор объединения множеств
	UniqueSet<T> operator+(const UniqueSet<T>& other) const {
		UniqueSet<T> result = *this;
		result.resize(abs(this->_size + other._size));
		for (int i = 0; i < other._size; ++i) {
			result.insert(other._elements[i]);
		}
		return result;
	}

	// Оператор разности множеств
	UniqueSet<T> operator-(const UniqueSet<T>& other) const {
		UniqueSet<T> result;
		result.resize(abs(this->_size - other._size));
		for (int i = 0; i < _size; ++i) {
			if (!other.contains(_elements[i])) {
				result.insert(_elements[i]);
			}
		}
		return result;
	}

	// Оператор сложения множества с числом
	UniqueSet<T> operator+(const T& value) const {
		UniqueSet<T> result = *this;
		result.resize(1);
		result.insert(value);
		return result;
	}

	// Оператор вычитания числа из множества
	UniqueSet<T> operator-(const T& value) const {
		UniqueSet<T> result = *this;
		result.remove(value);
		return result;
	}

	// Вычисление пересечения двух множеств
	UniqueSet<T> intersection(const UniqueSet<T>& other) const {
		UniqueSet<T> result;
		result.resize(abs(this->_size - other._size));
		for (int i = 0; i < _size; ++i) {
			if (other.contains(_elements[i])) {
				result.insert(_elements[i]);
			}
		}
		return result;
	}

	// Функция проверки наличия числа во множестве
	bool contains(const T& value) const {
		for (int i = 0; i < _size; ++i) {
			if (_elements[i] == value) {
				return true;
			}
		}
		return false;
	}

	// Вставка элемента в множество
	void insert(const T& value) {
		if (!contains(value)) {
			if (_size == _capacity) {
				resize(1);
			}
			_elements[_size++] = value;
		}
	}

	// Удаление элемента из множества
	void remove(const T& value) {
		for (int i = 0; i < _size; ++i) {
			if (_elements[i] == value) {
				for (int j = i; j < _size - 1; ++j) {
					_elements[j] = _elements[j + 1];
				}
				--_size;
				return;
			}
		}
	}

	// Вспомогательная функция для увеличения вместимости множества
	void resize(const int& add) {
		int newCapacity = _capacity + add;
		T* newElements = new T[newCapacity];
		for (int i = 0; i < _size; ++i) {
			newElements[i] = _elements[i];
		}
		delete[] _elements;
		_elements = newElements;
		_capacity = newCapacity;
	}

	// Вывод элементов множества
	void display() const {
		for (int i = 0; i < _size; ++i) {
			std::cout << _elements[i] << " ";
		}
		std::cout << std::endl;
	}
};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> p) {
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

//Returns 1 if all elements of sbj are in obj
template <typename T>
//Here sbj in not const becuase compiler cannot guarantee it is unchanged when using get_size
bool allElementsIn(UniqueSet<T>& sbj, const UniqueSet<T>& obj) {
	for (int i = 0; i < sbj.get_size(); ++i) {
		if (!obj.contains(sbj[i])) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool allElementsIn(const T* sbj, const size_t sbj_size, const T* obj, const size_t obj_size) {
	UniqueSet<T> u_sbj(sbj, sbj_size);
	UniqueSet<T> u_obj(obj, obj_size);

	return allElementsIn(u_sbj, u_obj);
}

template <typename T>
double UniqueSet<T>::_precision = 1e-6;

int main() {
	UniqueSet<double>::set_precision(1e-5);
	int intValues1[] = { 1, 2, 3, 4, 5 };
	int intValues2[] = { 1, 2, 3, 4, 5, 6, 7, 7 };
	double floatValues1[] = { 1.5, 1.7, 2.5, 0.9, 5.7, 9.3 };
	double floatValues2[] = { 1.5, 1.7, 2.5, 0.9 };
	std::string strValues1[] = { "str1", "str2", "str3" };
	std::string strValues2[] = { "str1", "str2", "str3", "str5" };
	std::pair<int, double> pairValues1[] = { std::make_pair(5, 5.5), std::make_pair(2, 2.25) };
	std::pair<int, double> pairValues2[] = { std::make_pair(2, 2.25), std::make_pair(3, 3.35), std::make_pair(5, 5.5) };

	UniqueSet<int> intSet1(intValues1, sizeof(intValues1) / sizeof(intValues1[0]));
	UniqueSet<int> intSet2(intValues2, sizeof(intValues2) / sizeof(intValues2[0]));
	UniqueSet<double> floatSet1(floatValues1, sizeof(floatValues1) / sizeof(floatValues1[0]));
	UniqueSet<double> floatSet2(floatValues2, sizeof(floatValues2) / sizeof(floatValues2[0]));
	UniqueSet<std::string> strSet1(strValues1, sizeof(strValues1) / sizeof(strValues1[0]));
	UniqueSet<std::string> strSet2(strValues2, sizeof(strValues2) / sizeof(strValues2[0]));
	UniqueSet<std::pair<int, double>> pairSet1(pairValues1, sizeof(pairValues1) / sizeof(pairValues1[0]));
	UniqueSet<std::pair<int, double>> pairSet2(pairValues2, sizeof(pairValues2) / sizeof(pairValues2[0]));

	std::cout << "intSet1: ";
	intSet1.display();
	std::cout << "intSet2: ";
	intSet2.display();
	std::cout << std::endl;
	UniqueSet<int> intUnionSet = intSet1 + intSet2;
	std::cout << "Union: ";
	intUnionSet.display();
	UniqueSet<int> intDifferenceSet = intSet2 - intSet1;
	std::cout << "Difference: ";
	intDifferenceSet.display();
	UniqueSet<int> intIntersectionSet = intSet1.intersection(intSet2);
	std::cout << "Intersection: ";
	intIntersectionSet.display();
	std::cout << "All elements of intSet1 are in intSet2: " << allElementsIn(intSet1, intSet2) << std::endl;
	std::cout << "All elements of intSet2 are in intSet1: " << allElementsIn(intSet2, intSet1) << std::endl;
	std::cout << "All elements of intValues1 are in intValues2: " << allElementsIn(intSet1, intSet2) << std::endl;
	std::cout << "All elements of intValues2 are in intValues1: " << allElementsIn(intSet2, intSet1) << std::endl;
	std::cout << std::endl << std::endl;


	std::cout << "floatSet1: ";
	floatSet1.display();
	std::cout << "floatSet2: ";
	floatSet2.display();
	std::cout << std::endl;
	std::cout << "floatSet1 != floatSet2: " << (floatSet1 != floatSet2) << std::endl;
	std::cout << "All elements of floatSet1 are in floatSet2: " << allElementsIn(floatSet1, floatSet2) << std::endl;
	std::cout << std::endl << std::endl;


	std::cout << "strSet1: ";
	strSet1.display();
	std::cout << "strSet2: ";
	strSet2.display();
	std::cout << std::endl;
	std::cout << "All elements of strSet1 are in strSet2: " << allElementsIn(strSet1, strSet2) << std::endl;
	std::cout << std::endl << std::endl;


	std::cout << "pairSet1: ";
	pairSet1.display();
	std::cout << "pairSet2: ";
	pairSet2.display();
	std::cout << std::endl;
	std::cout << "All elements of pairSet1 are in pairSet2: " << allElementsIn(pairSet1, pairSet2) << std::endl;
	std::cout << std::endl << std::endl;

	return 0;
}
	