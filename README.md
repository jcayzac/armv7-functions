ARMv7 Functions
===============

This is a collection of various functions optimized for __armv7__ and __neon__.

Compilation flags
-----------------

For best performance I usually use the following CFLAGS: <code>-mthumb -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -mvectorize-with-neon-quad -O3 -ffast-math -fomit-frame-pointer -fstrict-aliasing -fgcse-las -funsafe-loop-optimizations -fsee -ftree-vectorize</code>, with <code>-arch armv7</code> if it's _gcc for iOS_ or <code>-march=armv7-a</code> if it's _eabi-none-gcc_.


