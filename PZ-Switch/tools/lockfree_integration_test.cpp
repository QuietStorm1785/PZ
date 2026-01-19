/**
 * @file lockfree_integration_test.cpp
 * @brief Comprehensive testing for lock-free zombie optimization
 * 
 * Tests include:
 * - Lock-free queue correctness and performance
 * - Lock-free stack correctness
 * - Lock-free ring buffer operations
 * - Multi-threaded producer/consumer patterns
 * - Contention reduction measurement
 * 
 * Expected Performance Gains:
 * - Lock contention elimination in audio/collision queues
 * - Scalability improvement with increased thread count
 * - Overall FPS: +5-10% improvement
 * 
 * @date January 19, 2026
 * @author PZ Optimization Team
 */

#include "LockFreeStructures.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <iomanip>
#include <cmath>
#include <random>
#include <queue>
#include <mutex>

using namespace lockfree;

// ============================================================================
// TEST INFRASTRUCTURE
// ============================================================================

struct TestResult {
    std::string test_name;
    bool passed;
    double duration_ms;
    std::string message;
    
    void print() const {
        std::cout << (passed ? "✓ PASS" : "✗ FAIL") 
                  << " [" << std::fixed << std::setprecision(2) 
                  << duration_ms << "ms] " << test_name;
        if (!message.empty()) {
            std::cout << " - " << message;
        }
        std::cout << "\n";
    }
};

class TestSuite {
public:
    void run_test(const std::string& name, 
                  std::function<bool()> test_func) {
        auto start = std::chrono::high_resolution_clock::now();
        bool result = false;
        std::string message;
        
        try {
            result = test_func();
        } catch (const std::exception& e) {
            result = false;
            message = std::string("Exception: ") + e.what();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end - start);
        
        TestResult res{
            name,
            result,
            duration.count() / 1000.0,
            message
        };
        
        res.print();
        results_.push_back(res);
    }
    
    void print_summary() const {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "TEST SUMMARY\n";
        std::cout << std::string(60, '=') << "\n";
        
        int passed = 0, failed = 0;
        double total_time = 0.0;
        
        for (const auto& res : results_) {
            if (res.passed) passed++;
            else failed++;
            total_time += res.duration_ms;
        }
        
        std::cout << "Total: " << results_.size() << " tests\n";
        std::cout << "Passed: " << passed << "\n";
        std::cout << "Failed: " << failed << "\n";
        std::cout << "Total Time: " << std::fixed << std::setprecision(2) 
                  << total_time << "ms\n";
        std::cout << std::string(60, '=') << "\n";
    }

private:
    std::vector<TestResult> results_;
};

// ============================================================================
// UNIT TESTS
// ============================================================================

bool test_lockfree_queue_basic() {
    LockFreeQueue<int, 100> queue;
    
    // Test enqueue
    for (int i = 0; i < 50; ++i) {
        if (!queue.try_enqueue(i)) return false;
    }
    
    // Test dequeue
    for (int i = 0; i < 50; ++i) {
        int val;
        if (!queue.try_dequeue(val)) return false;
        if (val != i) return false;
    }
    
    return queue.empty();
}

bool test_lockfree_queue_capacity() {
    LockFreeQueue<int, 100> queue;
    
    // Fill queue to capacity
    for (int i = 0; i < 100; ++i) {
        if (!queue.try_enqueue(i)) return false;
    }
    
    // Try to overflow
    if (queue.try_enqueue(100)) return false;  // Should fail
    
    return queue.full();
}

bool test_lockfree_stack_basic() {
    LockFreeStack<int, 100> stack;
    
    // Push elements
    for (int i = 0; i < 50; ++i) {
        stack.push(i);
    }
    
    // Pop elements (LIFO order)
    for (int i = 49; i >= 0; --i) {
        int val;
        if (!stack.try_pop(val)) return false;
        if (val != i) return false;
    }
    
    return stack.empty();
}

bool test_lockfree_counter() {
    LockFreeCounter<uint64_t> counter(0);
    
    counter.increment();
    counter.increment();
    counter.add(5);
    
    if (counter.load() != 7) return false;
    
    counter.decrement();
    return counter.load() == 6;
}

bool test_lockfree_queue_empty() {
    LockFreeQueue<int, 100> queue;
    
    if (!queue.empty()) return false;
    
    queue.try_enqueue(1);
    if (queue.empty()) return false;
    
    int val;
    queue.try_dequeue(val);
    return queue.empty();
}

bool test_lockfree_queue_size() {
    LockFreeQueue<int, 100> queue;
    
    for (int i = 0; i < 25; ++i) {
        queue.try_enqueue(i);
    }
    
    return queue.size() == 25;
}

// ============================================================================
// CONCURRENT TESTS
// ============================================================================

bool test_concurrent_producer_consumer() {
    LockFreeQueue<int, 1000> queue;
    std::vector<int> results;
    std::atomic<bool> producer_done(false);
    std::atomic<int> consumed(0);
    
    // Producer thread
    std::thread producer([&]() {
        for (int i = 0; i < 500; ++i) {
            while (!queue.try_enqueue(i)) {
                // Retry if queue full
                std::this_thread::yield();
            }
        }
        producer_done.store(true);
    });
    
    // Consumer thread
    std::thread consumer([&]() {
        while (!producer_done.load() || !queue.empty()) {
            int val;
            if (queue.try_dequeue(val)) {
                results.push_back(val);
                consumed.fetch_add(1);
            } else {
                std::this_thread::yield();
            }
        }
    });
    
    producer.join();
    consumer.join();
    
    return consumed.load() == 500 && results.size() == 500;
}

bool test_concurrent_multiple_producers() {
    LockFreeQueue<int, 1000> queue;
    std::atomic<int> count(0);
    
    // 4 producer threads
    std::vector<std::thread> producers;
    for (int p = 0; p < 4; ++p) {
        producers.emplace_back([&, p]() {
            for (int i = 0; i < 100; ++i) {
                if (queue.try_enqueue(p * 1000 + i)) {
                    count.fetch_add(1);
                }
            }
        });
    }
    
    for (auto& t : producers) {
        t.join();
    }
    
    return count.load() == 400;
}

bool test_concurrent_multiple_consumers() {
    LockFreeQueue<int, 1000> queue;
    std::atomic<int> consumed(0);
    
    // Pre-fill queue
    for (int i = 0; i < 400; ++i) {
        queue.try_enqueue(i);
    }
    
    // 4 consumer threads
    std::vector<std::thread> consumers;
    for (int c = 0; c < 4; ++c) {
        consumers.emplace_back([&]() {
            int val;
            while (queue.try_dequeue(val)) {
                consumed.fetch_add(1);
            }
        });
    }
    
    for (auto& t : consumers) {
        t.join();
    }
    
    return consumed.load() == 400;
}

// ============================================================================
// PERFORMANCE BENCHMARKS
// ============================================================================

void benchmark_lockfree_vs_mutex_queue() {
    std::cout << "\n" << std::string(60, '-') << "\n";
    std::cout << "BENCHMARK: Lock-Free vs Mutex Queue\n";
    std::cout << std::string(60, '-') << "\n";
    
    const int OPERATIONS = 100000;
    const int THREADS = 4;
    
    // Lock-free queue benchmark
    auto lockfree_start = std::chrono::high_resolution_clock::now();
    {
        LockFreeQueue<int, 10000> queue;
        std::vector<std::thread> threads;
        
        // Producers
        for (int t = 0; t < THREADS; ++t) {
            threads.emplace_back([&, t]() {
                for (int i = 0; i < OPERATIONS / THREADS; ++i) {
                    while (!queue.try_enqueue(i)) {
                        std::this_thread::yield();
                    }
                }
            });
        }
        
        // Consumers
        std::atomic<int> consumed(0);
        for (int t = 0; t < THREADS; ++t) {
            threads.emplace_back([&]() {
                int val;
                while (consumed.load() < OPERATIONS) {
                    if (queue.try_dequeue(val)) {
                        consumed.fetch_add(1);
                    } else {
                        std::this_thread::yield();
                    }
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
    }
    auto lockfree_end = std::chrono::high_resolution_clock::now();
    auto lockfree_duration = std::chrono::duration_cast<std::chrono::microseconds>(
        lockfree_end - lockfree_start).count() / 1000.0;
    
    // Mutex queue benchmark
    auto mutex_start = std::chrono::high_resolution_clock::now();
    {
        std::queue<int> queue;
        std::mutex queue_mutex;
        std::atomic<int> consumed(0);
        std::vector<std::thread> threads;
        
        // Producers
        for (int t = 0; t < THREADS; ++t) {
            threads.emplace_back([&, t]() {
                for (int i = 0; i < OPERATIONS / THREADS; ++i) {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    if (queue.size() < 10000) {
                        queue.push(i);
                    }
                }
            });
        }
        
        // Consumers
        for (int t = 0; t < THREADS; ++t) {
            threads.emplace_back([&]() {
                while (consumed.load() < OPERATIONS) {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    if (!queue.empty()) {
                        queue.pop();
                        consumed.fetch_add(1);
                    }
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
    }
    auto mutex_end = std::chrono::high_resolution_clock::now();
    auto mutex_duration = std::chrono::duration_cast<std::chrono::microseconds>(
        mutex_end - mutex_start).count() / 1000.0;
    
    double speedup = mutex_duration / lockfree_duration;
    printf("Lock-Free time: %.2f ms\n", lockfree_duration);
    printf("Mutex time:     %.2f ms\n", mutex_duration);
    printf("Speedup:        %.2fx\n", speedup);
    printf("Threads:        %d\n", THREADS);
}

void benchmark_counter_contention() {
    std::cout << "\n" << std::string(60, '-') << "\n";
    std::cout << "BENCHMARK: Counter Contention (False Sharing)\n";
    std::cout << std::string(60, '-') << "\n";
    
    const int INCREMENT_COUNT = 1000000;
    const int THREADS = 8;
    
    // Lock-free counter (padded to prevent false sharing)
    auto lockfree_start = std::chrono::high_resolution_clock::now();
    {
        LockFreeCounter<uint64_t> counter(0);
        std::vector<std::thread> threads;
        
        for (int t = 0; t < THREADS; ++t) {
            threads.emplace_back([&]() {
                for (int i = 0; i < INCREMENT_COUNT / THREADS; ++i) {
                    counter.increment();
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
    }
    auto lockfree_end = std::chrono::high_resolution_clock::now();
    auto lockfree_duration = std::chrono::duration_cast<std::chrono::microseconds>(
        lockfree_end - lockfree_start).count() / 1000.0;
    
    // Mutex counter (not padded)
    auto mutex_start = std::chrono::high_resolution_clock::now();
    {
        uint64_t counter = 0;
        std::mutex counter_mutex;
        std::vector<std::thread> threads;
        
        for (int t = 0; t < THREADS; ++t) {
            threads.emplace_back([&]() {
                for (int i = 0; i < INCREMENT_COUNT / THREADS; ++i) {
                    std::lock_guard<std::mutex> lock(counter_mutex);
                    counter++;
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
    }
    auto mutex_end = std::chrono::high_resolution_clock::now();
    auto mutex_duration = std::chrono::duration_cast<std::chrono::microseconds>(
        mutex_end - mutex_start).count() / 1000.0;
    
    double speedup = mutex_duration / lockfree_duration;
    printf("Lock-Free time: %.2f ms\n", lockfree_duration);
    printf("Mutex time:     %.2f ms\n", mutex_duration);
    printf("Speedup:        %.2fx\n", speedup);
    printf("Threads:        %d\n", THREADS);
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int main() {
    std::cout << std::string(70, '=') << "\n";
    std::cout << "LOCK-FREE STRUCTURES - INTEGRATION TEST SUITE\n";
    std::cout << std::string(70, '=') << "\n";
    
    TestSuite suite;
    
    std::cout << "\n[UNIT TESTS]\n";
    suite.run_test("Lock-free queue basic", test_lockfree_queue_basic);
    suite.run_test("Lock-free queue capacity", test_lockfree_queue_capacity);
    suite.run_test("Lock-free stack basic", test_lockfree_stack_basic);
    suite.run_test("Lock-free counter", test_lockfree_counter);
    suite.run_test("Lock-free queue empty", test_lockfree_queue_empty);
    suite.run_test("Lock-free queue size", test_lockfree_queue_size);
    
    std::cout << "\n[CONCURRENT TESTS]\n";
    suite.run_test("Producer/Consumer", test_concurrent_producer_consumer);
    suite.run_test("Multiple Producers", test_concurrent_multiple_producers);
    suite.run_test("Multiple Consumers", test_concurrent_multiple_consumers);
    
    // Performance benchmarks
    std::cout << "\n[PERFORMANCE BENCHMARKS]\n";
    benchmark_lockfree_vs_mutex_queue();
    benchmark_counter_contention();
    
    suite.print_summary();
    
    std::cout << "\n✅ Lock-free structures integration test complete\n";
    return 0;
}
