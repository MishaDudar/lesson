#include <cstddef>
#include <cstdio>
#include <vector>
#include <random>
#include <numeric>
#include <cmath>

#if defined(__has_include)
#if __has_include(<simd>)
#include <simd>
namespace sx = std;
#define HAS_STD_SIMD 1
#elif __has_include(<experimental/simd>)
#include <experimental/simd>
namespace sx = std::experimental;
#define HAS_STD_SIMD 1
#else
#define HAS_STD_SIMD 0
#endif
#else
#define HAS_STD_SIMD 0
#endif

void axpy(float a, const float* x, const float* y, float* out, std::size_t n) {
#if HAS_STD_SIMD
    using v_t = sx::native_simd<float>;
    constexpr std::size_t W = v_t::size();

    std::size_t i = 0;
    for (; i + W <= n; i += W) {
        v_t vx(x + i, sx::element_aligned_tag{});
        v_t vy(y + i, sx::element_aligned_tag{});
        v_t vout = a * vx + vy;
        vout.copy_to(out + i, sx::element_aligned_tag{});
    }
    for (; i < n; ++i) {
        out[i] = a * x[i] + y[i];
    }
#else
    for (std::size_t i = 0; i < n; ++i) {
        out[i] = a * x[i] + y[i];
    }
#endif
}

int main() {
    constexpr std::size_t N = 1'000'0000000;
    std::vector<float> x(N), y(N), out(N);

    std::mt19937 rng(0);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (std::size_t i = 0; i < N; ++i) {
        x[i] = dist(rng);
        y[i] = dist(rng);
    }

    const float a = 2.5f;
    axpy(a, x.data(), y.data(), out.data(), N);

    double sum = std::accumulate(out.begin(), out.end(), 0.0);
    double l2 = 0.0;
    for (float v : out) l2 += double(v) * double(v);
    l2 = std::sqrt(l2);

#if HAS_STD_SIMD
    std::puts("OK: ran with std::simd");
#else
    std::puts("OK: ran with scalar fallback (no std::simd available)");
#endif
    std::printf("sum(out)=%.6f, ||out||2=%.6f\n", sum, l2);
    return 0;
}
