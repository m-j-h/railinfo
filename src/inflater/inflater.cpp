#include "inflater.h"

#include <stdexcept>
#include <zlib.h>

#include <algorithm>
#include <iostream>

Inflater::Inflater()
{}

Inflater::~Inflater()
{}
    
std::string Inflater::Process( const std::string& source )
{
    const size_t CHUNK = 4096;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];
    std::string result;

    z_stream zs;
    zs.zalloc   = Z_NULL;
    zs.zfree    = Z_NULL;
    zs.opaque   = Z_NULL;
    zs.avail_in = 0;
    zs.next_in  = Z_NULL;

    int rc = inflateInit2(&zs, 15 | 32 );
    if( rc != Z_OK )
    {
        throw std::runtime_error("zlib.inflateInit2() failed");
    }
    zs.avail_in = source.length();
    zs.next_in  = (unsigned char*)(source.data());

    do
    {
        zs.avail_out = CHUNK;
        zs.next_out  = out;
        rc = inflate(&zs, Z_NO_FLUSH);
        switch( rc )
        {
            case Z_NEED_DICT:
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&zs);
                const std::string msg = "zlib.inflate() failed";
                throw std::runtime_error(msg);
                break;
        }
        unsigned have = CHUNK - zs.avail_out;
        result += std::string( (const char*)out, have );
    } while( zs.avail_out == 0 );

    inflateEnd(&zs);
    return result;
}

