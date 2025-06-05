/**
 * @file rand.c
 * @brief Simple pseudo-random number generator implementation
 *
 * Implements a lightweight XOR-shift random number generator with:
 * - 32-bit internal state
 * - 15-bit output range (0-32767)
 * - Seed initialization capability
 */

#include "..\include\Lib_Clara.h"

#include "stdint.h"
#include "rand.h"

/** @brief Default seed value used when initializing with zero */
#define DEFAULT_SEED 0xDEADF00D

/** @brief Internal generator state (32-bit) */
static uint32_t seed = DEFAULT_SEED;

/**
 * @brief Generates a pseudo-random number
 *
 * Implements an XOR-shift algorithm that:
 * 1. Performs three bitwise XOR-shift operations on internal state
 * 2. Returns 15 bits from the modified state (range: 0-32767)
 *
 * @note The generator has a period of 2^32-1
 * @note Thread-unsafe (uses static internal state)
 *
 * @return uint32_t Pseudo-random number in range [0, 32767] (0x7FFF)
 *
 * @example
 * uint32_t r = rand(); // Get random number
 */
uint32_t rand() // =)
{
    seed ^= seed << 13;           // First XOR-shift (left 13 bits)
    seed ^= seed >> 17;           // Second XOR-shift (right 17 bits)
    seed ^= seed << 5;            // Third XOR-shift (left 5 bits)
    return (seed >> 16) & 0x7FFF; // Extract 15 bits
}

/**
 * @brief Seeds the random number generator
 *
 * Initializes the internal state with either:
 * - The provided seed value (if non-zero)
 * - DEFAULT_SEED (if zero is provided)
 *
 * @param s Seed value (0 results in DEFAULT_SEED being used)
 *
 * @example
 * srand(0x12345678); // Explicit seed
 * srand((dt.time);   // Time-based seed
 * srand(0);          // Default seed
 */
void srand(uint32_t s)
{
    seed = s ? s : DEFAULT_SEED; // Ensure non-zero state
}

/**
 * @brief Initializes the random number generator with a time-based seed
 * 
 * Generates a pseudo-random seed using the current system time and initializes
 * the RNG state. Combines hours, minutes, and seconds into a 24-bit seed value.
 * 
 * @note Uses REQUEST_DATEANDTIME_GET which may involve system calls
 * @note The seed is constructed as: (seconds << 16) | (minutes << 8) | hours
 * @note This provides different seeds across different times of day
 * 
 * @warning Not cryptographically secure - suitable for games/applications only
 * 
 * @example
 * randomize(); // Seed RNG with current time
 * int value = rand(); // Now get properly seeded random numbers
 */
void randomize(void)
{
    DATETIME dt;
    
    // Get current system time (synchronous request)
    REQUEST_DATEANDTIME_GET(SYNC, &dt);
    
    // Combine time components into 24-bit seed:
    // - Seconds in bits 16-23
    // - Minutes in bits 8-15
    // - Hours in bits 0-7
    srand((dt.time.sec << 16) | (dt.time.min << 8) | (dt.time.hour));
}
