#pragma once

#include <vector>
#include <unordered_map>

template <typename Key, typename Value>
struct Pair {
	Key key;
	Value value;
};

struct LinearProber {
	int operator() (int index, int size) const {
		return (index + 1) % size;
	}
};

template <typename K, typename V, typename Hash = std::hash<K>, typename IndexProbe = LinearProber>
class OOHashTable {
public:
	typedef K key_t;
	typedef V value_t;

	typedef Pair<key_t, value_t> pair_t;

	typedef value_t& reference;

	inline static const float MAX_FACTOR = 0.7;

private:
	struct Bucket {
		pair_t data;
		bool empty = true;
		bool deleted = false;
	};

	typedef std::vector<Bucket> table_t;
	typedef typename table_t::iterator bucket_iter;

public:
	OOHashTable(Hash hash = Hash(), IndexProbe probe = IndexProbe())
		: table(41), count(0),
			hasher(hash), nextIndex(probe) {}

	class iterator {
	private:
		friend class OOHashTable;
		
	public:
		typedef Pair<const key_t, value_t> const_pair;

		const_pair& operator*() {
			return reinterpret_cast<const_pair&>(*element);
		}

		const_pair* operator->() {
			return &(operator*());
		}

		iterator& operator++() {
			++element;
			validateIterator();
			return *this;
		}

		iterator operator++(int) {
			iterator copy(*this);
			++element;
			validateIterator();
			return copy();
		}

		bool operator==(const iterator& other) const {
			return table == other.table && element == other.element;
		}

		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

	private:
		iterator(table_t& table, bucket_iter el)
			: table(&table)
			, element(el) {
			validateIterator();
		}

		void validateIterator() {
			while (element != table->end() && element->empty) {
				++element;
			}
		}

	private:
		table_t* table;
		bucket_iter element;
	};

	iterator begin() {
		return iterator(table, table.begin());
	}

	iterator end() {
		return iterator(table, table.end());
	}

	iterator insert(const key_t& key, const value_t& value) {
		if (needsResize())
			resize();

		bucket_iter bucket = findBucket(key, false);
		if (bucket->empty)
			++count;

		bucket->deleted = false;
		bucket->empty = false;

		Pair<key_t, value_t> newElem;
		newElem.key = key;
		newElem.value = value;

		bucket->data = newElem;

		return iterator(table, bucket);
	}

	iterator erase(iterator it) {
		if (it == end()) {
			return it;
		}

		if (!it.element->empty) {
			--count;
			it.element->deleted = it.element->empty = true;
		}

		it.validateIterator();
		return it;
	}

	iterator erase(const key_t& key) {
		return erase(find(key));
	}

	iterator find(const key_t& key) {
		bucket_iter bucket = findBucket(key, true);
		
		if (bucket->empty)
			return end();

		return iterator(table, bucket);
	}

	value_t& operator[](const key_t& key) {
		if (float(count) / table.size() > 0.7) {
			resize();
		}

		iterator element = find(key);
		if (element != end()) {
			assert(!element.element->empty || element.element->empty ^ element.element->deleted);
			return element->value;
		}

		return insert(key, value_t())->value;
	}

	int size() const {
		return count;
	}
	
private:
	int getIndex(const key_t& key) const {
		return hasher(key) % table.size();
	}

	bool needsResize() const {
		const float currentFactor = float(count) / table.size();
		return currentFactor >= MAX_FACTOR;
	}

	void resize() {
		table_t newTable(table.size() * 2 + 1);
		newTable.swap(table);

		count = 0;
		for (Bucket& el : newTable) {
			if (!el.empty && !el.deleted)
				insert(el.data.key, el.data.value);
		}
	}

	int getNextIndex(int index) {
		return nextIndex(index, table.size());
	}

	bucket_iter findBucket(const key_t& key, bool checkDeleted) {
		int idx = getIndex(key);

		while (true) {
			if (table[idx].empty && (!checkDeleted || checkDeleted && !table[idx].deleted))
				break;

			if (table[idx].data.key == key && (!checkDeleted || checkDeleted && !table[idx].deleted))
				break;
	
			idx = getNextIndex(idx);
		}

		return table.begin() + idx;
	}

private:
	table_t table;
	int count;
	Hash hasher;
	IndexProbe nextIndex;
};