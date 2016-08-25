//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include "tlib/print.hpp"
#include "tlib/system.hpp"

extern "C" {

#define STACK_CHK_GUARD 0x595e9fbd94fda766

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn)) void __stack_chk_fail(){
    tlib::printf("Stack smashing detected \n");
    //TODO printf("pid=%u\n", scheduler::get_pid());
    tlib::exit(1);
}

} // end of extern "C"
