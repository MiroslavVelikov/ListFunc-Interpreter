#pragma once
#include <vector>
#include "dataPair.h"
#include <stdexcept>

// Open Addressing Hash Table
template <typename K, typename V, typename Hasher>
class oaHashTable {
private:
	struct bucket {
		dataPair<K, V> data;
		bool empty = true;
		bool deleted = false;
	};

public:
	oaHashTable(Hasher hasher) 
		: values(DEFAULT_SIZE), count(0), hasher(hasher) {};
	
	void insert(const K& key, const V& value) {
		if (needsResize()) resize();

		size_t index = getIndex(key);

		while (!values[index].empty) {
			index = getNextIndex(index);
		}
		count++;

		bucket* bucket = &values[index];

		bucket->data.key = key;
		bucket->data.value = value;
		bucket->empty = false;
		bucket->deleted = false;
	}

	bool find(const K& key) const {
		size_t index = getIndex(key);
		size_t begIndex = index;
		bucket const* bucket = &values[index];

		do {
			if (!bucket->empty && bucket->data.key == key) return true;
			else if (bucket->empty && !bucket->deleted) break;

			index = getNextIndex(index);
			bucket = &values[index];
		} while (begIndex != index);

		return false;
	}

	V& get(const K& key) {
		size_t index = getIndex(key);
		size_t begIndex = index;
		bucket* bucket = &values[index];

		/// bucket->empty == true && bucket->deleted == true -> skip
		/// bucket->empty == true && bucket->deleted == false -> break
		/// bucket->empty == false -> check
		/// begIndex == index -> break
		
		do {
			if (!bucket->empty && bucket->data.key == key) return bucket->data.value;
			else if (bucket->empty && !bucket->deleted) break;

			index = getNextIndex(index);
			bucket = &values[index];
		} while (begIndex != index);

		throw std::invalid_argument("This key does not exist\n");
	}

	V& remove(const K& key) {
		size_t index = getIndex(key);
		size_t begIndex = index;
		bucket* bucket = &values[index];

		do {
			if (!bucket->empty && bucket->data.key == key) {
				--count;
				bucket->deleted = true;
				bucket->empty = true;
				return bucket->data.value;
			}
			else if (bucket->empty && !bucket->deleted) break;

			index = getNextIndex(index);
			bucket = &values[index];
		} while (begIndex != index);

		throw std::invalid_argument("This item does not exist\n");
	}

private:
	size_t getIndex(const K& key) const {
		return hasher(key) % values.size();
	}

	size_t getNextIndex(size_t index) const {
		return ++index % values.size();
	}

	bool needsResize() const {
		const double factor = double(count) / values.size();
		return factor >= 0.7;
	}

	void resize() {
		std::vector<bucket> newValues(values.size() * 2 + 1);
		std::swap(values, newValues);

		count = 0;
		for (bucket& elem : newValues) {
			insert(elem.data.key, elem.data.value);
		}
	}

private:
	std::vector<bucket> values;
	size_t count;
	const Hasher hasher;

	static const size_t DEFAULT_SIZE = 29;
};