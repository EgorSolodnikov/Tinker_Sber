#ifndef CIRCULAR_BUFFER_SPI_HPP
#define CIRCULAR_BUFFER_SPI_HPP

#include <memory>
#include <mutex>
#include <numeric>
#include <stdexcept>
#include <vector>

#include <hardware_msg/msg/imu_state.hpp>
#include <hardware_msg/msg/motors_state.hpp>
#include <hardware_msg/msg/motors_telemetry.hpp>

using ImuState = hardware_msg::msg::ImuState;
using MotorState = hardware_msg::msg::MotorsState;
using MotorTelemetry = hardware_msg::msg::MotorsTelemetry;


template <class T>
class circular_buffer{
public:
    explicit circular_buffer(size_t size) :
	buf_(std::unique_ptr<T[]>(new T[size]))
	, max_size_(size)
{}

    void put(T item)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        buf_[head_] = item;

        if(full_)
        {
            tail_ = (tail_ + 1) % max_size_;
        }

        head_ = (head_ + 1) % max_size_;

        full_ = head_ == tail_;
    }

    T get()
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if(empty())
        {
            return T();
        }

        //Read data and advance the tail (we now have a free space)
        auto val = buf_[tail_];
        full_ = false;
        tail_ = (tail_ + 1) % max_size_;

        return val;
    }

    void reset()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        head_ = tail_;
        full_ = false;
    }

    bool empty() const
    {
        return (!full() && (head_ != tail_));
    } 

    bool full() const
    {
        return full_;
    }

    size_t capacity() const
    {
        return max_size_;
    }

    size_t size() const
    {
        size_t size = max_size_;

        if(!full())
        {
            if(head_ >= tail_)
            {
                size = head_ - tail_;
            }
            else
            {
                size = max_size_ - tail_ + head_;
            }
        }
        
        return size;
    }

    T get_avarage() const; 

private:
    mutable std::mutex mutex_;
    std::unique_ptr<T[]> buf_;
    size_t head_ = 0;
    size_t tail_ = 0;
    const size_t max_size_;
    float sum_;
    bool full_ = false;
};

template<>
inline ImuState circular_buffer<ImuState>::get_avarage() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (empty()) {
        return ImuState();
    }

    size_t n = size();
    std::vector<ImuState> all(n);
    size_t idx = tail_;
    for (size_t i = 0; i < n; ++i) {
        all[i] = buf_[idx];
        idx = (idx + 1) % max_size_;
    }

    ImuState avg;


    float sum_pitch = std::accumulate(all.begin(), all.end(), 0.0f, [](float s, const auto& i) { return s + i.pitch; });
    avg.set__pitch(sum_pitch / n);

    float sum_roll = std::accumulate(all.begin(), all.end(), 0.0f, [](float s, const auto& i) { return s + i.roll; });
    avg.set__roll(sum_roll / n);

    float sum_yaw = std::accumulate(all.begin(), all.end(), 0.0f, [](float s, const auto& i) { return s + i.yaw; });
    avg.set__yaw(sum_yaw / n);

    return avg;
}

template<>
inline MotorState circular_buffer<MotorState>::get_avarage() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (empty()) {
        return MotorState();  // Default
    }

    size_t n = size();
    std::vector<MotorState> all(n);
    size_t idx = tail_;
    for (size_t i = 0; i < n; ++i) {
        all[i] = buf_[idx];
        idx = (idx + 1) % max_size_;
    }


    MotorState avg;
    avg.position.resize(10);
    avg.velocity.resize(10);
    avg.torque.resize(10);

    for (size_t i = 0; i < 10; ++i) {
        // Position
        float sum_pos = std::accumulate(all.begin(), all.end(), 0.0f, [i](float s, const auto& st) { return s + st.position[i]; });
        avg.position[i] = sum_pos / n;

        // Velocity
        float sum_vel = std::accumulate(all.begin(), all.end(), 0.0f, [i](float s, const auto& st) { return s + st.velocity[i]; });
        avg.velocity[i] = sum_vel / n;

        // Torque
        float sum_tor = std::accumulate(all.begin(), all.end(), 0.0f, [i](float s, const auto& st) { return s + st.torque[i]; });
        avg.torque[i] = sum_tor / n;
    }

    return avg;
}

#endif