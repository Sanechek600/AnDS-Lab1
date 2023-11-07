#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class UniqueSet {
private:
	T* _elements;
	int _size;
	int _capacity;

public:
	// Конструктор по умолчанию пустое мно-во
	UniqueSet() : _elements(nullptr), _size(0), _capacity(0) {}

	// Конструктор с параметрами из другого мн-ва
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

	// Оператор присваивания
	UniqueSet<T>& operator=(const UniqueSet<T>& other) {
		if (this != &other) {
			delete[] _elements;
			_elements = nullptr;
			_size = 0;
			_capacity = 0;
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
		for (int i = 0; i < other._size; ++i) {
			result.insert(other._elements[i]);
		}
		return result;
	}

	// Оператор разности множеств
	UniqueSet<T> operator-(const UniqueSet<T>& other) const {
		UniqueSet<T> result;
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

	// Вспомогательная функция для увеличения размера массива
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

template <typename T>
bool allElementsIn(const UniqueSet<T>& sbj, const UniqueSet<T>& obj) {
	for (int i = 0; i < sbj._size; ++i) {
		if (!obj.contains(sbj[i])) {
			return false;
		}
	}
	return true;
}

int main() {
	int intValues1[] = { 1, 2, 3, 4, 5 };
	int intValues2[] = { 1, 2, 3, 4, 5, 6, 7 };
	float floatValues1[] = { 1.5, 1.7, 2.5, 0.9, 5.7, 9.3 };
	float floatValues2[] = { 1.5, 1.7, 2.5, 0.9 };

	UniqueSet<int> intSet1(intValues1, sizeof(intValues1) / sizeof(intValues1[0]));
	UniqueSet<int> intSet2(intValues2, sizeof(intValues2) / sizeof(intValues2[0]));
	UniqueSet<float> floatSet1()

	std::cout << "intSet1: ";
	intSet1.display();
	std::cout << "intSet2: ";
	intSet2.display();

	UniqueSet<int> unionSet = intSet1 + intSet2;
	std::cout << "Union: ";
	unionSet.display();

	UniqueSet<int> differenceSet = intSet1 - intSet2;
	std::cout << "Difference: ";
	differenceSet.display();

	UniqueSet<int> intersectionSet = intSet1.intersection(intSet2);
	std::cout << "Intersection: ";
	intersectionSet.display();

	return 0;
}
	