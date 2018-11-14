#ifndef SRC_CHAILOVEDOCS_H_
#define SRC_CHAILOVEDOCS_H_

/**
 * @file Globals.h
 * @page globals Globals
 *
 * This provides documentation about globals available through ChaiLove.
 */

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
 * Loads the given module, only once.
 *
 * While love.filesystem.load will load and execute a module any number of times, the `require()` function will only load and execute any given module just one.
 *
 * @param module The name of the module to load. "." will be replaced by "/".
 *
 * @return True if the module was loaded.
 *
 * @see love.filesystem.load
 *
 * @code
 * // The following will load "lib/player.chai".
 * require("lib.player")
 *
 * // Calling require("lib.player") again will not re-load it.
 * require("lib.player")
 *
 * // Calling a directory name will attempt to load the directory's "init.chai"
 * // file. The following example will load "lib/init.chai" if "lib.chai"
 * // doesn't exist.
 * require("lib")
 * @endcode
 */
bool require(const std::string& module);

/**
 * Provides some additional functionality to the basic string object.
 */
class String {
	public:
	/**
	 * Replaces all instances of the search string with the given replace string.
	 *
	 * @param search The string to search for that should be replaced.
	 * @param replace The string that will replace the found string.
	 *
	 * @return The new string with the replaced strings.
	 *
	 * @code
	 * var hello = "Hello World!"
	 * var goodbye = hello.replace("Hello", "Goodbye")
	 * // => "Goodbye World!"
	 * @endcode
	 */
	std::string replace(const std::string& search, const std::string& replace);

	/**
	 * Returns a trimmed version of the given string.
	 *
	 * @return A new string with trimmed left and right.
	 *
	 * @code
	 * var hello = "    Hello World!    "
	 * var result = hello.trim()
	 * // => "Hello World!"
	 * @endcode
	 */
	std::string trim();

	/**
	 * Splits a string by the given token.
	 */
	std::string split(const std::string& token);
};

#endif  // SRC_CHAILOVEDOCS_H_
