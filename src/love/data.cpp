#include "data.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "zlib.h"

namespace love {

std::string data::compress(const std::string& str) {
	return compress(str, Z_BEST_SPEED);
}

std::string data::compress(const std::string& str, int compressionlevel) {
	if (compressionlevel < 0 || compressionlevel > 9) {
		compressionlevel = Z_BEST_SPEED;
	}
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionlevel) != Z_OK) {
        std::cout << "[ChaiLove] [data] deflateInit failed while compressing." << std::endl;
        return str;
    }

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();

    int ret;
    char outbuffer[32768];
    std::string outstring;

    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {
        std::cout << "[ChaiLove] [data] Exception during zlib compression: (" << ret << ") " << zs.msg << std::endl;
        return str;
    }

    return outstring;
}

std::string data::decompress(const std::string& str) {
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();

    int ret;
    char outbuffer[32768];
    std::string outstring;

    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) {
        std::ostringstream oss;
        oss << "[ChaiLove] [data] Exception during zlib decompression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }

    return outstring;
}

}  // namespace love
