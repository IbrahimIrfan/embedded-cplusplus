/**
 * @file OpenSet.h
 * @brief Hash set implementation.
 *
 * Set implementation using an open addressed
 * hash map as the backing structure.
 *
 * @author Jeff Niu
 * @date November 4, 2017
 * @bug No known bugs
 */

#ifndef EMBEDDEDCPLUSPLUS_OPENSET_H
#define EMBEDDEDCPLUSPLUS_OPENSET_H

#include "Equal.h"
#include "Hash.h"
#include "OpenMap.h"

namespace wlp {

    /**
     * An open hash set is created using a backing hash map,
     * and all available functions are a subset of the functions
     * of the hash map. The set contains unique elements.
     * @tparam Key   the unique element type
     * @tparam Hash  the hash function of the stored elements
     * @tparam Equal test for equality function of the stored elements
     */
    template<class Key,
            class Hash = Hash<Key, uint16_t>,
            class Equal = Equal<Key>>
    class OpenHashSet {
    public:
        typedef OpenHashSet<Key, Hash, Equal> set_type;
        typedef OpenHashMap<Key, Key, Hash, Equal> table_type;
        typedef typename OpenHashMap<Key, Key, Hash, Equal>::iterator iterator;
        typedef typename OpenHashMap<Key, Key, Hash, Equal>::const_iterator const_iterator;
        typedef typename table_type::size_type size_type;
        typedef typename table_type::percent_type percent_type;
        typedef typename table_type::key_type key_type;

    private:
        /**
         * The backing hash map.
         */
        table_type m_hash_map;

    public:
        /**
         * Constructor creates a new hash map, and instantiates
         * the backing hash map.
         *
         * @see OpenHashMap
         * @param n        the initial size of the backing array
         * @param max_load the maximum load factor before rehash
         */
        explicit OpenHashSet(
                size_type n = 12,
                percent_type max_load = 75) :
                m_hash_map(n, max_load) {
        }

        /**
         * Disable copy constructor.
         */
        OpenHashSet(const set_type &) = delete;

        /**
         * Move constructor.
         *
         * @param set hash set to move
         */
        OpenHashSet(set_type &&set)
                : m_hash_map(move(set.m_hash_map)) {
        }

        /**
         * @return the current number of elements in the set
         */
        size_type size() const {
            return m_hash_map.size();
        }

        /**
         * @return the size of the backing array
         */
        size_type capacity() const {
            return m_hash_map.capacity();
        }

        /**
         * @return the maximum load factor
         */
        percent_type max_load() const {
            return m_hash_map.max_load();
        }

        /**
         * @return whether the hash map is empty
         */
        bool empty() const {
            return m_hash_map.empty();
        }

        /**
         * @return a pointer to the backing hash map
         */
        const table_type *get_backing_hash_map() const {
            return &m_hash_map;
        }

        /**
         * An iterator instance to the beginning of the hash set.
         * The iterator order of the set is not guaranteed to
         * be in any particular order.
         * @return iterator to the first element, or @code end @endcode
         * if the set is empty
         */
        iterator begin() {
            return m_hash_map.begin();
        }

        /**
         * A pass-the-end iterator instance. This iterator means
         * that an iterator has read past the end of the set
         * and has become invalid.
         * @return a pass-the-end iterator
         */
        iterator end() {
            return m_hash_map.end();
        }

        /**
         * @return a constant iterator to the first element
         */
        const_iterator begin() const {
            return m_hash_map.begin();
        }

        /**
         * @return a constant pass-the-end iterator
         */
        const_iterator end() const {
            return m_hash_map.end();
        }

        /**
         * Empty the elements in the set, such that its
         * size is now zero.
         */
        void clear() noexcept {
            m_hash_map.clear();
        }

        /**
         * Insert an element into the set. This function
         * returns a pair consistent of the iterator to the
         * element that was inserted or to the element that
         * prevented insertion. The second boolean value indicates
         * whether insertion took place.
         * @param key the element to insert
         * @return a pair of an iterator and boolean
         */
        template<typename K>
        Pair<iterator, bool> insert(K &&key) {
            return m_hash_map.insert(forward<K>(key), forward<K>(key));
        };

        /**
         * Check if an element is in the set.
         * @param key element whose existence to check
         * @return true if the element is contained in the set
         */
        bool contains(const key_type &key) const {
            return m_hash_map.contains(key);
        }

        /**
         * Obtain an iterator to an element in the set.
         * @param key the element to find
         * @return iterator to the element or pass-the-end
         * if the element is not in the set
         */
        iterator find(const key_type &key) {
            return m_hash_map.find(key);
        }

        /**
         * Obtain a const iterator to an element in the set
         * @param key the element to find
         * @return const iterator to the element or pass-the-end
         * if the element is not in the set
         */
        const_iterator find(const key_type &key) const {
            return m_hash_map.find(key);
        }

        /**
         * Erase the element in the set pointed to by
         * the iterator.
         *
         * @param pos iterator whose element to erase
         * @return iterator to the next element in the set
         */
        iterator erase(const iterator &pos) {
            return m_hash_map.erase(pos);
        }

        /**
         * Remove an element from the set.
         *
         * @param key the element to remove
         * @return true if removal occured
         */
        bool erase(const key_type &key) {
            return m_hash_map.erase(key);
        }

        /**
         * Disable copy assignment.
         *
         * @return reference to this set
         */
        set_type &operator=(const set_type &) = delete;

        /**
         * Move assignment operator.
         *
         * @param set hash set to move
         * @return reference to this set
         */
        set_type &operator=(set_type &&set) {
            m_hash_map = move(set.m_hash_map);
            return *this;
        }
    };

}


#endif //EMBEDDEDCPLUSPLUS_OPENSET_H
