#include "math.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "zlib.h"

namespace Modules {

bool math::load() {
	setRandomSeed((int)time(0));
	return true;
}

double math::random() {
	int num = rand();
	return (double)num / (double)(RAND_MAX);
}

int math::random(int max) {
	int num = rand();
	return num % max + 1;
}

int math::random(int min, int max) {
	int num = rand();
    if (min > max) {
        min ^= max;
        max ^= min;
        min ^= max;
    }
    num = num % (max-min+1);
    num += min;
    return num;
}

void math::setRandomSeed(int seed) {
	m_seed = seed;
	srand(seed);
}

void math::setRandomSeed(int low, int high) {
	setRandomSeed(low + high);
}

int math::getRandomSeed() {
	return m_seed;
}

std::string math::compress(const std::string& str) {
	return compress(str, Z_BEST_SPEED);
}

std::string math::compress(const std::string& str, int compressionlevel) {
	if (compressionlevel < 0 || compressionlevel > 9) {
		compressionlevel = Z_BEST_SPEED;
	}
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionlevel) != Z_OK) {
        std::cout << "[ChaiLove] [math] deflateInit failed while compressing." << std::endl;
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
        std::cout << "[ChaiLove] [math] Exception during zlib compression: (" << ret << ") " << zs.msg << std::endl;
        return str;
    }

    return outstring;
}

std::string math::decompress(const std::string& str) {
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

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
            << zs.msg;
        throw(std::runtime_error(oss.str()));
    }

    return outstring;
}

}  // namespace Modules
