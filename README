seeklib
=======

C++ library to go with ruby bindings (see dradetsky/ruby-seeklib) to
allow use of imgseek fingerprint algorithm outside of imgseek.

Based on code by some dude named Ricardo Niederberger Cabral
(https://about.me/rncabral). His repo which I extracted the code from
is here: https://github.com/ricardocabral/iskdaemon.

building
--------

The only dependency is CImg (and make, and a C++ compiler). Also, if
you have ImageMagick installed, CImg will call out to ImageMagick for
formats it can't handle on its own, but it's not required.

If you happen to be using ubuntu (and probably debian, mint, etc) you
should install cimg-dev. If you use some other platform, consult its
documentation or http://cimg.sourceforge.net/

The library is currently configured to build with clang (my tests
showed a slight performance boost), but you can always build with

make CXX=g++

or something similar.

no package
----------

I wanted to package this as a gem, as an alternative to
pHash/pHashion, but I don't know how to package a C++ library and ffi
bindings together (as opposed to C/C++ extensions), and couldn't find
instructions for doing it. If you know, please tell me or just fork it
and package it yourself.
