This directory contains a subset of the Independent JPEG Group's (IJG)
libjpeg version 6b.  We only include enough of distribution to build
libjpeg.  We do not include the standard executables that come with
libjpeg (cjpeg, djpeg, etc.). Furthermore, the standard libjpeg build
process is replaced with a CMake build process.

We'd like to thank the IJG for distributing a public JPEG IO library.

Modifications
-------------

jconfig.h is usually generated by the build process. For this distribution, 
we ship a version of jconfig.h to be used across several platforms.

jmorecfg.h was altered to support Windows DLL generation. We also
changed the typedef INT32 to be an "int" instead of a "long". 






