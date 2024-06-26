#ifndef WARC2TEXT_WARCREADER_HH
#define WARC2TEXT_WARCREADER_HH

#include "util/file.hh"
#include "zlib-ng.h"
#include <array>
#include <string>
#include <cstdint>

namespace warc2text {
    class WARCReader {
        public:
            WARCReader();
            explicit WARCReader(const std::string& filename);
            std::size_t getRecord(std::string& out, std::size_t max_size = 1024*1024*20); //20MB
            std::size_t tell() const;
            ~WARCReader();
        private:
            util::scoped_FILE file;
            std::string warc_filename;
            zng_stream s{};
            static const std::size_t BUFFER_SIZE = 4096;
            std::array<uint8_t, BUFFER_SIZE> buf;
            std::array<uint8_t, BUFFER_SIZE> scratch;

            void openFile(const std::string& filename);
            void closeFile();
            std::size_t readChunk();
    };
}

#endif
