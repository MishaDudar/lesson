
#if __has_include(<simd>)
#include <simd>
namespace sx = std;
#elif __has_include(<experimental/simd>)
#include <experimental/simd>
namespace sx = std::experimental;
#else
#error "Немає <simd> і <experimental/simd> у вашій стандартній бібліотеці."
#endif