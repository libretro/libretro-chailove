#ifndef SRC_CHAILOVEDOCS_H_
#define SRC_CHAILOVEDOCS_H_

#include <string>

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

/**
 * Load a module.
 *
 * @param module The name of the module to load, only once. "." will be replaced by "/".
 *
 * @return True if the module had been loaded.
 *
 * @code
 * The following will load lib/player.chai.
 * require("lib.player")
 * @endcode
 */
bool require(const std::string& module);

#endif  // SRC_CHAILOVEDOCS_H_
