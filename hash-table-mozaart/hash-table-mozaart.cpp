#include <iostream>
#include <cmath>
#include <string>
#include <clocale>
#include <limits>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

const int m = 23;

template<typename K, typename V>
struct HashNode {
	K key;
	V value;
	HashNode() : key(), value() {} // Конструктор по умолчанию (без него жалуется)
	HashNode(K k, V v) : key(k), value(v) {}
};


template<typename K, typename V>
class HashMap {
private:
	vector<HashNode<K, V>> table;
	int capacity;
	int size;

	// Хеш-функция для вычисления индекса в таблице
	int h(const K& key) {
		ostringstream oss;
		oss << key;
		string strKey = oss.str(); // Преобразуем ключ в строку

		const double phi = (sqrt(5) - 1) / 2; // Золотое сечение
		int hashValue = 0;

		for (char c : strKey) {
			hashValue += static_cast<int>(c); // Добавляем байтовое представление каждого символа
		}

		// Применяем формулу хеширования
		hashValue = static_cast<int>(capacity * (fmod(hashValue * phi, 1)));
		/*
			Здесь используется метод умножения. Построение хэш-функций методом умножения выполняется в четыре этапа:
			1) умножение ключа k на константу 0 < A < 1;
			2) взятие дробной части от результата;
			3) умножение полученного значения на m;
			4) взятие целой части от результата
			За константу я взял число фи - золотое сечение.
		*/
		return hashValue;
	}
	int linearProbe(int index) {
		return (index + 1) % capacity;
	}

public:
	HashMap(int initialCapacity = m) : capacity(initialCapacity), size(0) {
		table.resize(capacity);
	}

	// Метод добавления элемента в таблицу
	void ins(const K& key, const V& value) {
		if (size >= capacity) {
			cout << "Table is full" << endl;
			return;
		}
		int i = h(key);
		while (table[i].key != key && !(table[i].key == K())) {
			i = linearProbe(i);
		}
		if ((table[i].key == K())) ++size;
		table[i] = HashNode<K, V>(key, value);
	}

	// Метод поиска элемента по ключу
	bool find(const K& key, V& value) {
		int i = h(key);
		int startI = i;
		while (!(table[i].key == K())) {
			if (table[i].key == key) {
				value = table[i].value;
				return true;
			}
			i = linearProbe(i);
			if (i == startI) // Проверка на циклический проход
				break;
		}
		return false; // Элемент не найден
	}


	void rm(const K& key) {
		int i = h(key);
		int startI = i;
		while (!(table[i].key == K())) {
			if (table[i].key == key) {
				break;
			}
			i = linearProbe(i);
			if (i == startI)
				return;
		}
		if ((table[i].key == K())) return;
		if (table[linearProbe(i)].key == K()) {
			table[i].key = K();
			table[i].value = V();
			--size;
			return;
		}
		int j = linearProbe(i);
		int startJ = j;
		bool l = !(table[j].key == K()) && !(h(table[j].key) != j && h(table[j].key) <= i);
		l;
		while (!(table[j].key == K()) && !(h(table[j].key) != j && h(table[j].key) <= i)) {
			j = linearProbe(j);
			if (j == startJ) {
				table[i].key = K();
				table[i].value = V();
				return;
			}
		}
		bool k = h(table[j].key) != j && h(table[j].key) <= i;
		k;
		if (h(table[j].key) != j && h(table[j].key) <= i) {
			K newKey = table[j].key;
			V newValue = table[j].value;
			rm(table[j].key);
			table[i].key = newKey;
			table[i].value = newValue;
		}
		else {
			if (table[i].key == key) {
				--size;
				table[i].key = K();
				table[i].value = V();
			}
		}
	}




	void display() {
		for (int i = 0; i < capacity; ++i) {
			if (!(table[i].key == K())) {
				cout << "[" << i << "]: " << "(" << table[i].key << ", " << table[i].value << ")\t{" << h(table[i].key) << "}" << endl;
			}
		}
	}
	void display(const K& key) {
		int i = h(key);
		int startI = i;
		while (!(table[i].key == K())) {
			if (table[i].key == key) {
				break;
			}
			i = linearProbe(i);
			if (i == startI)
			{
				cout << "Node not found" << endl;
				return;
			}
		}
		cout << "[" << i << "]: " << "(" << table[i].key << ", " << table[i].value << ")\t{" << h(table[i].key) << "}" << endl;


	}
};


int main() {


	setlocale(LC_CTYPE, "rus");
	HashMap<string, string> table;
	cout << "\n[Fruits]\n" << endl;
	table.ins("40000", "Apple");
	table.ins("15", "Orange");
	table.ins("31", "Coco");
	table.ins("13", "Nuts");
	table.ins("4", "Lime");
	table.ins("40", "Pine");
	table.ins("10", "Banana");

	string fruit;

	if (table.find("13", fruit)) {
		cout << "Found: " << fruit << endl;

	}
	else {
		cout << "Not found" << endl;
	}
	if (table.find("31", fruit)) {
		cout << "Found: " << fruit << endl;

	}
	else {
		cout << "Not found" << endl;
	}
	if (table.find("13", fruit)) {
		cout << "Found: " << fruit << endl;

	}
	else {
		cout << "Not found" << endl;
	}

	table.display();
	cout << "Removing: ";
	table.display("31");
	table.rm("31");
	table.display();

	cout << "Removing: ";
	table.display("40");
	table.rm("40");
	table.display();

	if (table.find("40", fruit)) {
		cout << "Found: " << fruit << endl;
	}
	else {
		cout << "Not found" << endl;
	}
	/////////////////////////////////////////////////////////////////
	cout << "\n\n---------------\n[Veggie]\n" << endl;
	HashMap<int, string> table_t;

	table_t.ins(40000, "Potato");
	table_t.ins(15, "Tomato");
	table_t.ins(31, "Bean");
	table_t.ins(13, "Onion");
	table_t.ins(4, "Garlic");
	table_t.ins(10, "Cabage");
	table_t.ins(40, "Eggplant");

	//for (int i = 0; i < m+5; i++)
	//{
	//    table_t.ins(i, "RICK");
	//}

	string vegs;
	if (table_t.find(13, vegs)) {
		cout << "Found: " << vegs << endl;
	}

	if (table_t.find(31, vegs)) {
		cout << "Found: " << vegs << endl;
	}
	if (table_t.find(13, vegs)) {
		cout << "Found: " << vegs << endl;
	}
	else {
		cout << "Not found" << endl;
	}
	table_t.display();
	cout << "Removing: ";
	table_t.display(31);
	table_t.rm(31);
	table_t.display();
	if (table_t.find(13, vegs)) {
		cout << "Found: " << vegs << endl;
	}
	else {
		cout << "Not found" << endl;
	}
	return 0;
}
