#ifndef SRC_CHAILOVEDOCS_H_
#define SRC_CHAILOVEDOCS_H_

/**
 * Provides a Linked List data structure.
 *
 * @code
 * var list = List()
 * list.push_back(3)
 * for (listItem : list) {
 *   print("Item: " + to_string(listItem))
 * }
 * @endcode
 */
class List {
	public:
	/**
	 * Construct a list.
	 */
	List();

	/**
	 * Insert element at beginning.
	 */
	void push_front(void* val);

	/**
	 * Add element at the end.
	 */
	void push_back(void* val);

	/**
	 * Retrieves the size of the list.
	 */
	void size();

	/**
	 * Change size.
	 */
	void resize(int size);

	/**
	 * Delete first element.
	 */
	void pop_front();

	/**
	 * Delete last element.
	 */
	void pop_back();
};

#endif  // SRC_CHAILOVEDOCS_H_
