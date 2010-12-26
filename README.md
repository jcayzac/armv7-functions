ARMv7 Functions
===============

This is a collection of various functions optimized for __armv7__ and __neon__.

The five holy laws
------------------

1. __Never return floating point values by value__. It would work fine if <code>-mfloat-abi=hard</code> was supported everywhere, but sadly it's not. With the more common <code>-mfloat-abi=softfp</code>, every time you do a <code>return my_float_value</code>, it does either a <code>fmrs</code> or a <code>vstr</code>, followed by a load operation in order to read the result back! __Instead, use a non-const reference as first parameter__. It allows super smooth inlining of your intermediate results without unnecessary loads and stores, just like it would do if hard floats were available (works for vector types too) !
2. __Try to minimize loads and stores__. Though GCC doesn't support evolved <code>vldmia</code>/<code>vstmia</code> and will generate poor code for operations on <code>float32x4x4_t</code>, so handcoding them make sense in that case.
3. __Use vector types everywhere it makes sense__. Functions prefixed with <code>vec3_</code> and <code>vec4_</code> directly work on <code>float32x4_t</code>. Those prefixed with <code>mat44_</code> directly work with <code>float32x4x4_t</code>. Parameters are passed as references, so the compiler doesn't perform unnecessary ARM register transfers.
4. __Don't hard-code registers__, but use dummy values instead for clobber, and let the compiler allocate registers as needed.
5. __A good clobber list is an empty clobber list__. If you let the compiler handle loads for you, "_memory_" shouldn't even show up in your clobber list. The only item that might is "_cc_".

Compilation flags
-----------------

For best performance I usually use the following CFLAGS: <code>-mthumb -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -mvectorize-with-neon-quad -O3 -ffast-math -fomit-frame-pointer -fstrict-aliasing -fgcse-las -funsafe-loop-optimizations -fsee -ftree-vectorize</code>, with <code>-arch armv7</code> if it's _gcc for iOS_ or <code>-march=armv7-a</code> if it's _eabi-none-gcc_.

Preprocessor macros
-------------------

Several preprocessor macros, when defined, change the behaviour of the code. See <code>config.h</code> and <code>config-defaults.h</code> for details…

