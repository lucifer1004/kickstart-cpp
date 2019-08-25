# Notes

This problem is very similar to 2019/Round_B/Energy Stones.

First, we sort the slots in the ascending order by ci/ei.

Then, we start from (c_sum, 0), remove ci and add ei, until c == c_required. If e >= e_required at this time, the required (c, e) is possible. Otherwise, it is impossible.

To speed up, two techniques can be utilized:

- Pre-calculate accumulated sum of ci and ei.
- Binary-search for the critical point where c will drop below c_required. (The `upper_bound` function can be used here)