#pragma once

#include <cassert>
#include <cstdint>

#include "hsv2rgb.h"

namespace colorado
{
#if 0
struct RGBPixel {
	union {
		struct {
            union {
                uint8_t r;
                uint8_t red;
            };
            union {
                uint8_t g;
                uint8_t green;
            };
            union {
                uint8_t b;
                uint8_t blue;
            };
        };
		uint8_t raw[3];
	};
};
#else
    using RGBPixel = CRGB;
#endif

    template <typename T>
    class PixelArray
    {
    public:
        PixelArray(size_t count) :
            count_{count},
            v_{new T[count]}
        {
        }

        PixelArray(PixelArray& other) :
            count_{other.count_},
            v_{new T[other.count_]}
        {
            std::copy(other.v_, &other.v_[count_], v_);
        }

        PixelArray(PixelArray&& other) :
            count_{other.count_}
        {
            delete[] v_;
            v_ = other.v_;
            other.v_ = nullptr;
        }

        ~PixelArray()
        {
            if (v_ != nullptr)
            {
                delete[] v_;
            }
        }

        size_t count() const { return count_; }

        const T& operator[](size_t n) const
        {
            assert(n < count_);
            return v_[n];
        }

        T& operator[](size_t n)
        {
            assert(n < count_);
            return v_[n];
        }

        PixelArray& operator=(PixelArray& other)
        {
            if (this != &other)
            {
                assert(count_ == other.count_);
                std::copy(other.v_, &other.v_[count_], v_);
            }

            return *this;
        }

        PixelArray& operator=(PixelArray&& other)
        {
            assert(count_ == other.count_);

            if (this != &other)
            {
                delete[] v_;
                v_ = other.v_;
                other.v_ = nullptr;
            }

            return *this;
        }

    private:
        const size_t count_;
        T* v_;
    };

    using HSVPixelArray = PixelArray<CHSV>;
    using RGBPixelArray = PixelArray<CRGB>;

} // namespace colorado