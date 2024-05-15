#pragma once
#include <vector>

template <typename Key, typename Value>
struct DataPair {
	Key key;
	Value value;
};

struct LinearProber {
	size_t operator()(size_t index, size_t size) const {
		return (index + 1) % size;
	}
};

// Open addressing hash table
template <typename K, typename V, typename Hash, typename IndexProbe = LinearProber>
class oaHashTable {
public:
	typedef K key_type;
	typedef V value_type;

	typedef DataPair<key_type, value_type> pair_type;

private:
	struct Bucket {
		pair_type data;
		bool empty = true;
		bool deleted = false;
	};

	typedef std::vector<Bucket> table_t;
	typedef typename table_t::iterator bucket_iterator;

public:
	oaHashTable(Hash hasher, IndexProbe probe = IndexProbe());

	class Iterator {
	private:
		friend class oaHashTable;

		Iterator(table_t& table, bucket_iterator el)
			: table(table), element(el){

		}

	public:
		typedef DataPair<const key_type, value_type> const_pair;

		const_pair& operator*() {

		}

	private:
		void validateIterator() {
			while (element != table->end() && element->empty()) {
				++element;
			}
		}

	private:
		table_t* table;
		bucket_iterator element;
	};

private:
	table_t table;
	size_t count;
	Hash hasher;
	IndexProbe nextIndex;
};