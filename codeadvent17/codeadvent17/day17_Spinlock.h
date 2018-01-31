#pragma once

class Spinlock
{
public:
    static unsigned compute(unsigned stepSize);
    static size_t compute_pt2(unsigned stepSize);
};
