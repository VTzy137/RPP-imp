#include <iostream>
#include <math.h>
#include <xmmintrin.h>
using namespace std;
int num = 0;
float x = 500.0f, y = 34.0f;
float fastSqrt(float x) {
    __m128 a = _mm_set_ss(x);
    __m128 r = _mm_sqrt_ss(a);
    return _mm_cvtss_f32(r);
}

void benmark(float& result) {
    ++num;
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    result = atan2(y, x);
    // result = 500.0f*34.0f;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = x/y;
    // result = std::sqrt(500.0f);
    // result = fastSqrt(500.0f);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(x);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // result = std::sqrt(500.0f);
    // rand() % 100;
}

int main() {
    clock_t begin = clock();
    float a = 340955;
    float b = 443023, c = 234, d = 3;
    float result;
    for (int i = 0; i < 10000000; i++) {
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
        benmark(result);
    }
    cout << result << endl;
    clock_t end = clock();
    cout << begin << " " << end << endl;
    std::cout << "running time" << end - begin << endl;
    return 0;
}