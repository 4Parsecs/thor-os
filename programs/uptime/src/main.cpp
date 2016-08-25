//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <tlib/file.hpp>
#include <tlib/system.hpp>
#include <tlib/errors.hpp>
#include <tlib/print.hpp>

int main(int, char*[]){
    auto fd = tlib::open("/sys/uptime");

    if(fd.valid()){
        auto buffer = new char[64];

        auto content_result = tlib::read(*fd, buffer, 64);

        if(content_result.valid()){
            auto chars = *content_result;

            std::string value_str;
            value_str.reserve(chars);

            for(size_t i = 0; i < chars; ++i){
                value_str += buffer[i];
            }

            auto value = std::parse(value_str);

            tlib::printf("Uptime: %u:%u:%u\n", value / 3600, (value % 3600) / 60, value % 60);
        } else {
            tlib::printf("uptime: error: %s\n", std::error_message(content_result.error()));
        }

        delete[] buffer;

        tlib::close(*fd);
    } else {
        tlib::printf("uptime: error: %s\n", std::error_message(fd.error()));
    }

    return 0;
}
