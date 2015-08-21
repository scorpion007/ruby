/**********************************************************************

  initsext.c -

  $Author$

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#include "internal.h"
#include "vm_core.h"

#define CALL(n) {void Init_##n(void); Init_##n(); rb_provide(#n ".so");}

/* standard library extensions */
void
rb_call_inits_ext(void)
{
    VALUE load_path = GET_VM()->load_path;

    /* initialize the load paths for the build drop so nmake install succeeds */
	rb_ary_push(load_path, rb_str_new2(".ext/common"));
	rb_ary_push(load_path, rb_str_new2("lib"));
	rb_ary_push(load_path, rb_str_new2("."));

    /* initialize the standard search paths so that std libs can be found once
       deployed. */
    ruby_init_loadpath();
    
    CALL(enc);
    CALL(bigdecimal);
    CALL(continuation);
    CALL(coverage);
    CALL(date_core);
    CALL(digest);
    CALL(bubblebabble);
    CALL(md5);
    CALL(rmd160);
    CALL(sha1);
    CALL(sha2);
    CALL(etc);
    CALL(fcntl);
    CALL(fiber);
    CALL(console);
    CALL(nonblock);
    CALL(generator);
    CALL(parser);
    CALL(complex);
    CALL(rational);
    CALL(nkf);
    CALL(objspace);
    CALL(pathname);
    CALL(psych);
    CALL(cparse);
    CALL(sizeof);
    CALL(ripper);
    CALL(sdbm);
    CALL(socket);
    CALL(stringio);
    CALL(strscan);
    CALL(thread);
#ifndef _WIN32
    CALL(win32ole);
#endif
}
#undef CALL
