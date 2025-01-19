#import <Metal/Metal.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

#define THREADS 256  // Number of GPU threads per threadgroup

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout("metal_poly_mult.txt");

    int n, m;
    fin >> n;  
    vector<int> a(n + 2);
    a[0] = n;
    for (int i = 1; i <= n + 1; i++) fin >> a[i];

    fin >> m;  
    vector<int> b(m + 2);
    b[0] = m;
    for (int i = 1; i <= m + 1; i++) fin >> b[i];

    vector<int> c(n + m + 1, 0);

    // Metal initialization
    @autoreleasepool {
        id<MTLDevice> device = MTLCreateSystemDefaultDevice();
        if (!device) {
            std::cerr << "Metal is not supported on this device.\n";
            return 1;
        }

        id<MTLCommandQueue> commandQueue = [device newCommandQueue];
        NSString *path = @"./poly_mult.metallib"; // Path to compiled .metallib
        NSError *error = nil;
        NSURL *url = [NSURL fileURLWithPath:path];
        id<MTLLibrary> library = [device newLibraryWithURL:url error:&error];
        if (!library) {
            std::cerr << "Failed to load Metal library from file." << std::endl;
            if (error) {
                std::cerr << "Error: " << [error.localizedDescription UTF8String] << std::endl;
            }
            return 1;
        }

        id<MTLFunction> function = [library newFunctionWithName:@"poly_multiply"];
        if (!function) {
            std::cerr << "Failed to load compute function 'poly_multiply'. Ensure the shader is compiled and linked correctly." << std::endl;
            return 1;
        }

        id<MTLComputePipelineState> pipelineState = [device newComputePipelineStateWithFunction:function error:&error];
        if (error) {
            std::cerr << "Error creating pipeline state.\n";
            return 1;
        }

        // Create Metal buffers
        id<MTLBuffer> bufferA = [device newBufferWithBytes:a.data() length:sizeof(int) * a.size() options:MTLResourceStorageModeShared];
        id<MTLBuffer> bufferB = [device newBufferWithBytes:b.data() length:sizeof(int) * b.size() options:MTLResourceStorageModeShared];
        id<MTLBuffer> bufferC = [device newBufferWithLength:sizeof(int) * c.size() options:MTLResourceStorageModeShared];

        // Command buffer and encoder
        auto start = high_resolution_clock::now();
        id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
        id<MTLComputeCommandEncoder> encoder = [commandBuffer computeCommandEncoder];
        [encoder setComputePipelineState:pipelineState];
        [encoder setBuffer:bufferA offset:0 atIndex:0];
        [encoder setBuffer:bufferB offset:0 atIndex:1];
        [encoder setBuffer:bufferC offset:0 atIndex:2];

        MTLSize gridSize = MTLSizeMake(n + m + 1, 1, 1); 
        MTLSize threadGroupSize = MTLSizeMake(THREADS, 1, 1); 
        [encoder dispatchThreads:gridSize threadsPerThreadgroup:threadGroupSize];
        [encoder endEncoding];

        [commandBuffer commit];
        [commandBuffer waitUntilCompleted];
        auto end = high_resolution_clock::now();

        // Read back result
        int *resultPtr = static_cast<int *>([bufferC contents]);
        c.assign(resultPtr, resultPtr + c.size());

        auto duration = duration_cast<microseconds>(end - start);
        cout << "Time taken by Metal: " << duration.count() << " microseconds" << endl;

        for (int val : c) fout << val << " ";
        return 0;
    }
}
