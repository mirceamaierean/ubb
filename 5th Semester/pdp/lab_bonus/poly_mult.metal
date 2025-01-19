#include <metal_stdlib>
using namespace metal;

kernel void poly_multiply(device const int *a [[buffer(0)]],
                          device const int *b [[buffer(1)]],
                          device int *c [[buffer(2)]],
                          uint index [[thread_position_in_grid]]) {
    uint n = a[0];
    uint m = b[0];

    if (index >= n + m + 1) return;  // bounds check

    int sum = 0;
    for (uint j = 0; j <= index; ++j) {
        if (j <= n && (index - j) <= m) {
            sum += a[j + 1] * b[index - j + 1];  // coefficients stored after degrees
        }
    }
    c[index] = sum;  // store the computed coefficient
}
