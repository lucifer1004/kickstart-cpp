# Notes

This problem requires some observation.

- N is odd
    - N is prime: {1, N}, {}, OK
    - N is non-prime: {1, ..., N}, {}, NOT_OK
- N is even
    - N = 4k+2: {1, ..., 2k+1}, {2, ..., 4k+2}, OK
    - N = 4k
        - k is prime (1 will be considered a prime here)
            - k = 1: {1}, {2, 4}, OK
            - k = 2: {1}, {2, 4, 8}, OK
            - k > 2: {1, k}, {2, 4, 2k, 4k}, OK
        - k is not prime
            - k is odd: {1, ..., k}, {2, 4, ..., 2k, 4k}, NOT_OK
            - k is even: NOT_OK