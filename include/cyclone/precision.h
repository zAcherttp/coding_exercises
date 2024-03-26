#include <cmath>
namespace cyclone
{
    /*
    Defines a real number precision. Cyclone can be compiled in
    single- or double-precision versions. By default single precision
    is provided.
    */
    typedef float real;

/* Defines the precision of the square root operator. */
#define real_sqrt sqrtf

/* Defines the precision of the power operator. */
#define real_pow powf

/* Defines the precision of the absolute magnitude operator. */
#define real_abs fabsf

}
