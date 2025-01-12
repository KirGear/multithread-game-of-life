#include "utils.h"

std::chrono::milliseconds time_elapsed(std::chrono::steady_clock::time_point& last_measurement, std::chrono::steady_clock::time_point& time_buffer)
{
    std::swap(last_measurement, time_buffer);
    last_measurement = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(last_measurement - time_buffer);
}
