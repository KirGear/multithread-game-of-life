#pragma once
#include <chrono>

std::chrono::milliseconds time_elapsed(std::chrono::steady_clock::time_point& last_measurement, std::chrono::steady_clock::time_point& time_buffer);