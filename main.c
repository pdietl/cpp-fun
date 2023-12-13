#include <stdio.h>
#include <metalang99.h>

#define ADD_COMMA(x) x,

#define CASE_ENUM_VARIANT(c) case c: return #c;

#define ENUM_CONSTANT_IMPL(prefix, name) v(k##prefix##_##name)
#define ENUM_CONSTANT_ARITY 2

#define ENUM_PRINTABLE(name, ...) \
    typedef enum { \
        ML99_EVAL(ML99_variadicsForEach( \
            ML99_compose(ML99_reify(v(ADD_COMMA)), ML99_appl(v(ENUM_CONSTANT), v(name))), \
            v(__VA_ARGS__))) \
    } name##_t; \
    \
    const char *name##ToString(name##_t val) \
    { \
        switch (val) \
        { \
        ML99_EVAL(ML99_variadicsForEach( \
            ML99_compose(ML99_reify(v(CASE_ENUM_VARIANT)), ML99_appl(v(ENUM_CONSTANT), v(name))), \
            v(__VA_ARGS__)) \
        ) \
            default: return "Unknown"; \
        } \
    }

ENUM_PRINTABLE(Color,
    Red,
    Green,
    Blue,
    Orange,
    Purple
)

int main()
{
    Color_t c = kColor_Red;
    printf("The color is %s\n", ColorToString(c));
    return 0;
}
