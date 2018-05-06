#ifndef SRC_CHAILOVEDOCS_HTTP_H_
#define SRC_CHAILOVEDOCS_HTTP_H_

/**
 * Allows downloading of files over HTTP (no https).
 *
 * @code
 * var request = Http("http://example.com/index.html")
 * while (request.process() == "pending") {
 *   print("Please Wait...")
 * }
 * if (request.getStatus() == "failed") {
 *   print("Failed: " + request.getReasonPhrase())
 * }
 * global response = request.getResponseString()
 * print(response)
 * @endcode
 */
class Http {
	public:
	/**
	 * Create a Http() object, to request the given URL.
	 */
	Http(const std::string& url);

	/**
	 * Retrieve the status code.
	 */
	int getStatusCode();
	~Http();
	std::string process();

	/**
	 * Retrieve the status code.
	 */
	std::string getStatus();

	/**
	 * Retrieve the content type.
	 */
	std::string getContentType();

	/**
	 * Reason why the request failed.
	 */
	std::string getReasonPhrase();

	/**
	 * Retrieve a string representation of the requested data.
	 */
	std::string getResponseString();

	/**
	 * Retrieve the size of the response data.
	 */
	int getResponseSize();
}

#endif
