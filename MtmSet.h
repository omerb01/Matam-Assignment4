#ifndef MTM4_SET_H
#define MTM4_SET_H

#include "exceptions.h"

namespace mtm {

    /**
     * A set
     * @tparam Type The type of an element on the group.
     *      Required to implement:
     *                             - operator ==
     *                             - copy constructor
     */
    template<typename Type>
    class MtmSet {
        /**
         * A node in the set
         */
        class Node {
        public:
            Type element;
            Node *next;

            explicit Node(const Type &element) : element(element),
                                                 next(nullptr) {}
        };

        Node *head;

    public:
        //Forward declaration
        class const_iterator;

        /**
         * A iterator for Set
        */
        class iterator {
            Node *node;

        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            iterator() : node(nullptr) {}

            /**
             * Constructor of Set iterator
             * @param node The node the iterator points to
             */
            explicit iterator(Node *node) : node(node) {}

            /**
             * Copy constructor
             * @param it The iterator to copy
             */
            iterator(const iterator &it) = default;

            /**
             * Destructor
             */
            ~iterator() = default;

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this iterator.
             */
            iterator &operator=(const iterator &rhs) = default;

            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type &operator*() const {
                return *const_iterator(*this);
            }

            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the iterator
             *  points to.
             * C++ use the -> operator on the returned pointer,
             * this allows the user to treat the iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const {
                return const_iterator(*this).operator->();
            }

            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator &operator++() {
                if (node == nullptr) throw NodeIsEndException();
                node = node->next;
                return *this;
            }

            /**
             * Postfix increment operator (i++)
             * @return iterator that points to the same node as this before
             * the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator operator++(int) {
                iterator it(*this);
                ++(*this);
                return it;
            }

            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators point to the same node
             */
            bool operator==(const const_iterator &rhs) const {
                return const_iterator(*this) == rhs;
            }

            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators don't point to the same node
             */
            bool operator!=(const const_iterator &rhs) const {
                return const_iterator(*this) != rhs;
            }

            friend class const_iterator;
        };

        /**
         * A const_iterator for Set
        */
        class const_iterator {
            const Node *node;

        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            const_iterator() : node(nullptr) {}

            /**
             * Constructor of Set const_iterator
             * @param node The node the const_iterator points to
             */
            explicit const_iterator(Node *node) : node(node) {}

            /**
             * Copy constructor
             * @param it The const_iterator to copy
             */
            const_iterator(const const_iterator &it) = default;

            /**
             * Constructor from iterator (not const_iterator)
             * Allows casting from iterator to const_iterator
             * @param it The iterator to "copy" to a const_iterator
             */
            const_iterator(const iterator &it) : node(it.node) {}

            /**
             * Destructor
             */
            ~const_iterator() = default;

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this const_iterator.
             */
            const_iterator &
            operator=(const const_iterator &rhs) = default;

            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the const_iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type &operator*() const {
                if (node == nullptr) throw NodeIsEndException();
                return this->node->element;
            }

            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the const_iterator
             *  points to.
             *  C++ use the -> operator on the returned pointer,
             *  this allows the user to treat the const_iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const {
                if (node == nullptr) throw NodeIsEndException();
                return &(this->node->element);
            }

            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator &operator++() {
                if (node == nullptr) throw NodeIsEndException();
                node = node->next;
                return *this;
            }

            /**
             * Postfix increment operator (i++)
             * @return const_iterator that points to the same node as this
             * before the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator operator++(int) {
                const_iterator prev(*this);
                ++(*this);
                return prev;
            }

            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators point to the same node
             */
            bool operator==(const const_iterator &rhs) const {
                return this->node == rhs.node;
            }

            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators don't point to the same
             * node
             */
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }


        };

        /**
         * Empty constructor
         * Creates an empty set
         */
        MtmSet() : head(nullptr) {}

        /**
         * Copy constructor
         * @param set the Set to copy
         */
        MtmSet(const MtmSet &set) : head(nullptr) {
            if (set.head == nullptr) return;

            Node *new_head = new Node(*set.head);

            Node *node = set.head;
            Node *new_node = new_head;

            while (node->next != nullptr) {
                new_node->next = new Node(*node->next);
                new_node = new_node->next;
                node = node->next;
            }

            this->head = new_head;
        }

        /**
         * Destructor
         * Free all allocated memory in the set.
         */
        ~MtmSet() {
            this->clear();
        }

        /**
         * Insert a new element to the set, doesn't insert if there is already
         *  an equal element in the set.
         * If an element was't inserted, all iterators should stay valid.
         * @param elem The element to insert to the set
         * @return An iterator to the inserted element, or to the equal
         * element if the element wasn't inserted.
         */
        iterator insert(const Type &elem) {
            if (head == nullptr) {
                head = new Node(elem);
                return iterator(head);
            }

            iterator i = this->find(elem);
            if (i != this->end()) return i;

            Node *node = head;
            while (node->next != nullptr) {
                node = node->next;
            }

            node->next = new Node(elem);
            return iterator(node->next);
        }

        /**
         * Remove an element from the set. If there is no element equal to
         *  elem in the set, does nothing.
         * If an element wasn't removed, all iterators should stay valid.
         * @param elem the element to remove.
         */
        void erase(const Type &elem) {
            if (!this->contains(elem)) return;

            Node *prev = head;
            Node *current = prev->next;

            if (prev->element == elem) {
                head = head->next;
                delete prev;
                return;
            }

            Node *next = current->next;
            while (next != nullptr) {
                if (current->element == elem) break;
                prev = current;
                current = next;
                next = next->next;
            }

            if (next == nullptr) {
                prev->next = nullptr;
            } else {
                prev->next = next;
            }
            delete current;
        }

        /**
         * Remove the element the iterator points to from the set.
         * Iterator to another set is undefined.
         * @param it The iterator to the element to the set.
         */
        void erase(const iterator &it) {
            if (it == this->end()) return;
            erase(*it);
        }

        /**
         * Get the amount of elements in the set.
         * @return The amount of elements in the set.
         */
        int size() const {
            int counter = 0;
            const_iterator i;
            i = this->begin();
            while (i != this->end()) {
                counter++;
                i++;
            }

            return counter;
        }

        /**
         * Check if the set is empty.
         * @return true is the set is empty.
         */
        bool empty() const {
            if (head == nullptr) return true;
            return false;
        }

        /**
         * Empty the set, free all allocated memory in the set.
         */
        void clear() {
            iterator prev = this->begin();
            iterator i = prev;
            while (prev != this->end()) {
                i++;
                this->erase(prev);
                prev = i;
            }

            head = nullptr;
        }

        /**
         * Get an iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        iterator begin() {
            if (head == nullptr) return iterator();
            return iterator(head);
        }

        /**
         * Get a const_iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        const_iterator begin() const {
            if (head == nullptr) return const_iterator();
            return const_iterator(head);
        }

        /**
         * Returns an iterator referring to the past-the-end element in the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return Iterator to past-the-end element.
         */
        iterator end() {
            return iterator();
        }

        /**
         * Returns a const_iterator referring to the past-the-end element in
         * the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return const_iterator to past-the-end element.
         */
        const_iterator end() const {
            return const_iterator();
        }

        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return An iterator that points to the elem.
         */
        iterator find(const Type &elem) {
            iterator i;

            for (i = this->begin(); i != this->end(); i++) {
                if (*i == elem) return i;
            }

            return i;
        }

        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return A const_iterator that points to the elem.
         */
        const_iterator find(const Type &elem) const {
            const_iterator i;

            for (i = this->begin(); i != this->end(); i++) {
                if (*i == elem) return i;
            }

            return i;
        }

        /**
         * Check if an element is in the set.
         * @param elem The element to check if it's in the set.
         * @return True if the element is in the set, false otherwise.
         */
        bool contains(const Type &elem) const {
            const_iterator i = this->find(elem);
            return i != this->end();
        }

        /**
         * Check if this set is a superset of a given set.
         * Superset: A superset of B if B is a subset of A, that mean's that
         *  A contains all the elements in B.
         * @param subset The set to check if it's a subset.
         * @return True if the given set is a subset of this set.
         */
        bool isSuperSetOf(const MtmSet &subset) const {
            for (const_iterator i = subset.begin(); i != subset.end(); i++) {
                if (!this->contains(*i)) return false;
            }
            return true;
        }

        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the == operator.
         * @return true if thw two set conatain the same elements, false
         *  otherwise.
         */
        bool operator==(const MtmSet &rhs) const {
            return this->isSuperSetOf(rhs) && this->size() == rhs.size();
        }

        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the != operator.
         * @return false if thw two set conatain the same elements, true
         *  otherwise.
         */
        bool operator!=(const MtmSet &rhs) const {
            return !(*this == rhs);
        }

        /**
         * Insert all the elements in the given set to this set (union).
         * @param set The set to insert all the elements from.
         * @return A reference to this set.
         */
        MtmSet &unite(const MtmSet &set) {
            for (const_iterator i = set.begin(); i != set.end(); i++) {
                this->insert(*i);
            }
            return *this;
        }

        /**
         * Returns a new set that is an union of this set, and a given set.
         * @param set The other set (other than this) to be in the union.
         * @return The new set.
         */
        MtmSet unite(const MtmSet &set) const {
            MtmSet<Type> new_set;
            new_set.unite(set);
            new_set.unite(*this);
            return new_set;
        }

        /**
         * Remove all the elements from this set, that are not in the given set
         * (intersection).
         * @param set The other set in the intersection.
         * @return A reference to this set.
         */
        MtmSet &intersect(const MtmSet &set) {
            iterator i = this->begin();
            while (i != this->end()) {
                if (!set.contains(*i)) {
                    this->erase(i);
                    i = this->begin();
                }
                else {
                    i++;
                }
            }
            return *this;
        }

        /**
         * Returns a new set that is an intersection of this set,
         *  and a given set.
         * @param set The other set (other than this) to be in the intersection.
         * @return The new set.
         */
        MtmSet intersect(const MtmSet &set) const {
            MtmSet new_set(*this);
            new_set.intersect(set);
            return new_set;
        }

        /**
         * Remove all the elements in the set, that doesn't meet a given
         *  condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A reference to this set.
         */
        template<typename func>
        MtmSet &getSubSet(func condition) {
            iterator i = this->begin();
            while(i != this->end()) {
                if(!condition(*i)) {
                    erase(i);
                    i = this->begin();
                }
                else {
                    i++;
                }
            }
            return *this;
        }

        /**
         * Get a subset of this set, that contains all the elements in the set,
         * that doesn't meet a given condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A the new set.
         */
        template<typename func>
        MtmSet getSubSet(func condition) const {
            MtmSet new_set(*this);
            new_set.getSubSet(condition);
            return new_set;
        }
    };
} // namespace mtm

#endif //MTM4_SET_H
