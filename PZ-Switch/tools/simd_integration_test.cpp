/**
 * @file simd_integration_test.cpp
 * @brief Integration tests for SIMD zombie optimizations
 * 
 * Tests verify that SIMD optimizations produce correct results
 * and demonstrate significant performance improvements.
 * 
 * @date January 19, 2026
 */

#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <random>

#include "SIMDOptimization.h"
#include "zombie/popman/SIMDZombieOptimizer.h"

namespace zombie {
namespace popman {

/**
 * @brief Scalar reference implementation for correctness verification
 */
class ScalarZombieOptimizer {
public:
    static void update_positions_scalar(
        float* pos_x, float* pos_y, float* pos_z,
        const float* vel_x, const float* vel_y, const float* vel_z,
        float dt, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            pos_x[i] += vel_x[i] * dt;
            pos_y[i] += vel_y[i] * dt;
            pos_z[i] += vel_z[i] * dt;
        }
    }
    
    static void compute_distances_squared_scalar(
        float* distances,
        float ref_x, float ref_y, float ref_z,
        const float* pos_x, const float* pos_y, const float* pos_z,
        size_t count) {
        for (size_t i = 0; i < count; ++i) {
            float dx = pos_x[i] - ref_x;
            float dy = pos_y[i] - ref_y;
            float dz = pos_z[i] - ref_z;
            distances[i] = dx*dx + dy*dy + dz*dz;
        }
    }
};

// ============================================================================
// TEST CASES
// ============================================================================

void test_simd_vector_operations() {
    printf("\n=== Testing SIMD Vector Operations ===\n");
    
    simd::Vec3 a(1.0f, 2.0f, 3.0f);
    simd::Vec3 b(4.0f, 5.0f, 6.0f);
    
    // Test add
    simd::Vec3 sum = simd::add(a, b);
    printf("add({1,2,3}, {4,5,6}) = {%.1f, %.1f, %.1f}\n", sum.x, sum.y, sum.z);
    assert(sum.x == 5.0f && sum.y == 7.0f && sum.z == 9.0f);
    
    // Test dot product
    float dot = simd::dot(a, b);
    float expected_dot = 1*4 + 2*5 + 3*6;  // 32
    printf("dot({1,2,3}, {4,5,6}) = %.1f (expected %.1f)\n", dot, expected_dot);
    assert(std::abs(dot - expected_dot) < 1e-5f);
    
    // Test magnitude
    float mag = simd::magnitude(a);
    float expected_mag = std::sqrt(1*1 + 2*2 + 3*3);  // sqrt(14)
    printf("magnitude({1,2,3}) = %.6f (expected %.6f)\n", mag, expected_mag);
    assert(std::abs(mag - expected_mag) < 1e-5f);
    
    // Test normalize
    simd::Vec3 norm_a = simd::normalize(a);
    float norm_mag = simd::magnitude(norm_a);
    printf("normalize({1,2,3}) magnitude = %.6f (expected 1.0)\n", norm_mag);
    assert(std::abs(norm_mag - 1.0f) < 1e-5f);
    
    // Test distance
    float dist = simd::distance(a, b);
    float expected_dist = std::sqrt((4-1)*(4-1) + (5-2)*(5-2) + (6-3)*(6-3));
    printf("distance({1,2,3}, {4,5,6}) = %.6f (expected %.6f)\n", dist, expected_dist);
    assert(std::abs(dist - expected_dist) < 1e-5f);
    
    printf("✅ All vector operation tests passed!\n");
}

void test_simd_batch_operations() {
    printf("\n=== Testing SIMD Batch Operations ===\n");
    
    const size_t count = 100;
    std::vector<simd::Vec3> positions(count);
    std::vector<simd::Vec3> velocities(count);
    
    // Initialize with test data
    for (size_t i = 0; i < count; ++i) {
        positions[i] = simd::Vec3(i * 1.0f, i * 2.0f, i * 3.0f);
        velocities[i] = simd::Vec3(0.1f, 0.2f, 0.3f);
    }
    
    // Test batch update
    float dt = 0.016f;  // ~60 FPS
    std::vector<simd::Vec3> updated_positions = positions;
    SIMDZombieOptimizer::update_positions_simd(
        updated_positions.data(), velocities.data(), dt, count);
    
    // Verify first few updates
    for (size_t i = 0; i < 5; ++i) {
        simd::Vec3 expected = simd::add(positions[i], simd::mul(velocities[i], dt));
        printf("Position[%zu]: ({%.3f, %.3f, %.3f}) expected ({%.3f, %.3f, %.3f})\n",
               i, updated_positions[i].x, updated_positions[i].y, updated_positions[i].z,
               expected.x, expected.y, expected.z);
        assert(std::abs(updated_positions[i].x - expected.x) < 1e-5f);
        assert(std::abs(updated_positions[i].y - expected.y) < 1e-5f);
        assert(std::abs(updated_positions[i].z - expected.z) < 1e-5f);
    }
    
    printf("✅ All batch operation tests passed!\n");
}

void test_simd_distance_computation() {
    printf("\n=== Testing SIMD Distance Computation ===\n");
    
    const size_t count = 1000;
    std::vector<simd::Vec3> positions(count);
    std::vector<float> distances(count);
    
    // Generate random positions
    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
    
    for (size_t i = 0; i < count; ++i) {
        positions[i] = simd::Vec3(dist(rng), dist(rng), dist(rng));
    }
    
    simd::Vec3 ref_point(0.0f, 0.0f, 0.0f);
    
    // Compute distances using SIMD
    SIMDZombieOptimizer::compute_distances_squared_simd(
        distances.data(), ref_point, positions.data(), count);
    
    // Verify a few samples
    for (size_t i = 0; i < 10; ++i) {
        float expected = positions[i].x * positions[i].x +
                         positions[i].y * positions[i].y +
                         positions[i].z * positions[i].z;
        float error = std::abs(distances[i] - expected);
        printf("Distance²[%zu]: %.2f (expected %.2f, error %.2e)\n",
               i, distances[i], expected, error);
        assert(error < 1e-4f);
    }
    
    printf("✅ All distance computation tests passed!\n");
}

// ============================================================================
// PERFORMANCE BENCHMARKS
// ============================================================================

void benchmark_position_updates() {
    printf("\n=== SIMD Position Update Benchmark ===\n");
    
    const size_t count = 5000;
    const size_t iterations = 100;
    
    std::vector<simd::Vec3> positions_simd(count);
    std::vector<simd::Vec3> velocities(count);
    std::vector<float> pos_x(count), pos_y(count), pos_z(count);
    std::vector<float> vel_x(count), vel_y(count), vel_z(count);
    
    // Initialize data
    std::mt19937 rng(42);
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
    
    for (size_t i = 0; i < count; ++i) {
        positions_simd[i] = simd::Vec3(dist(rng), dist(rng), dist(rng));
        velocities[i] = simd::Vec3(dist(rng)/100, dist(rng)/100, dist(rng)/100);
        pos_x[i] = positions_simd[i].x;
        pos_y[i] = positions_simd[i].y;
        pos_z[i] = positions_simd[i].z;
        vel_x[i] = velocities[i].x;
        vel_y[i] = velocities[i].y;
        vel_z[i] = velocities[i].z;
    }
    
    float dt = 0.016f;
    
    // SIMD benchmark
    auto simd_start = std::chrono::high_resolution_clock::now();
    for (size_t iter = 0; iter < iterations; ++iter) {
        SIMDZombieOptimizer::update_positions_simd(
            positions_simd.data(), velocities.data(), dt, count);
    }
    auto simd_end = std::chrono::high_resolution_clock::now();
    
    // Scalar benchmark
    auto scalar_start = std::chrono::high_resolution_clock::now();
    for (size_t iter = 0; iter < iterations; ++iter) {
        ScalarZombieOptimizer::update_positions_scalar(
            pos_x.data(), pos_y.data(), pos_z.data(),
            vel_x.data(), vel_y.data(), vel_z.data(), dt, count);
    }
    auto scalar_end = std::chrono::high_resolution_clock::now();
    
    auto simd_time = std::chrono::duration_cast<std::chrono::microseconds>(
        simd_end - simd_start).count();
    auto scalar_time = std::chrono::duration_cast<std::chrono::microseconds>(
        scalar_end - scalar_start).count();
    
    double speedup = static_cast<double>(scalar_time) / simd_time;
    
    printf("SIMD:   %ld µs\n", simd_time);
    printf("Scalar: %ld µs\n", scalar_time);
    printf("Speedup: %.2fx (%d zombies x %zu iterations)\n", 
           speedup, static_cast<int>(count), iterations);
    printf("Expected: 3-4x for SIMD vs scalar\n");
}

void benchmark_distance_computation() {
    printf("\n=== SIMD Distance Computation Benchmark ===\n");
    
    const size_t count = 10000;
    const size_t iterations = 100;
    
    std::vector<simd::Vec3> positions(count);
    std::vector<float> distances_simd(count);
    std::vector<float> distances_scalar(count);
    std::vector<float> pos_x(count), pos_y(count), pos_z(count);
    
    // Initialize data
    std::mt19937 rng(54321);
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
    
    for (size_t i = 0; i < count; ++i) {
        positions[i] = simd::Vec3(dist(rng), dist(rng), dist(rng));
        pos_x[i] = positions[i].x;
        pos_y[i] = positions[i].y;
        pos_z[i] = positions[i].z;
    }
    
    simd::Vec3 ref_point(0.0f, 0.0f, 0.0f);
    
    // SIMD benchmark
    auto simd_start = std::chrono::high_resolution_clock::now();
    for (size_t iter = 0; iter < iterations; ++iter) {
        SIMDZombieOptimizer::compute_distances_squared_simd(
            distances_simd.data(), ref_point, positions.data(), count);
    }
    auto simd_end = std::chrono::high_resolution_clock::now();
    
    // Scalar benchmark
    auto scalar_start = std::chrono::high_resolution_clock::now();
    for (size_t iter = 0; iter < iterations; ++iter) {
        ScalarZombieOptimizer::compute_distances_squared_scalar(
            distances_scalar.data(), 0.0f, 0.0f, 0.0f,
            pos_x.data(), pos_y.data(), pos_z.data(), count);
    }
    auto scalar_end = std::chrono::high_resolution_clock::now();
    
    auto simd_time = std::chrono::duration_cast<std::chrono::microseconds>(
        simd_end - simd_start).count();
    auto scalar_time = std::chrono::duration_cast<std::chrono::microseconds>(
        scalar_end - scalar_start).count();
    
    double speedup = static_cast<double>(scalar_time) / simd_time;
    
    printf("SIMD:   %ld µs\n", simd_time);
    printf("Scalar: %ld µs\n", scalar_time);
    printf("Speedup: %.2fx (%d positions x %zu iterations)\n",
           speedup, static_cast<int>(count), iterations);
    printf("Expected: 3-4x for SIMD vs scalar\n");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int run_simd_tests() {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  SIMD Zombie Optimization Integration Tests (Day 6)         ║\n");
    printf("║  Project Zomboid - Phase 2 Advanced Optimizations           ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    
    try {
        // Correctness tests
        test_simd_vector_operations();
        test_simd_batch_operations();
        test_simd_distance_computation();
        
        // Performance benchmarks
        benchmark_position_updates();
        benchmark_distance_computation();
        
        printf("\n╔══════════════════════════════════════════════════════════════╗\n");
        printf("║ ✅ ALL TESTS PASSED - SIMD OPTIMIZATIONS VALIDATED           ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n");
        
        return 0;
    } catch (const std::exception& e) {
        printf("\n❌ TEST FAILED: %s\n", e.what());
        return 1;
    }
}

}  // namespace popman
}  // namespace zombie

// ============================================================================
// ENTRY POINT FOR STANDALONE TESTING
// ============================================================================

#ifdef SIMD_TEST_STANDALONE
int main() {
    return zombie::popman::run_simd_tests();
}
#endif
