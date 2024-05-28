gcd(A,B,X):- A=0,X=B. % base case
gcd(A,B,X):- B=0,X=A. % base case
gcd(A,B,X):- A>B, gcd(B, A, X).
gcd(A,B,X):- A<B, T is B mod A, gcd(A, T, X).


# This Prolog code defines a predicate `gcd/3` to calculate the greatest common divisor (GCD) of two numbers `A` and `B`. Here's how the code works:

# ### Rules:
# 1. **Base Cases**:
#    - If `A` is 0, then `X` (the GCD) is `B`.
#    - If `B` is 0, then `X` (the GCD) is `A`.

# 2. **Recursive Cases**:
#    - If `A` is greater than `B`, the GCD of `A` and `B` is the same as the GCD of `B` and `A`.
#    - If `A` is less than `B`, the GCD of `A` and `B` is the same as the GCD of `A` and the remainder of `B` divided by `A`.

# ### Explanation:
# - The base cases handle situations where one of the numbers is 0, making the GCD the non-zero number.
# - The recursive cases handle situations where both `A` and `B` are non-zero. If `A` is greater than `B`, it switches the order of `A` and `B` to ensure `A` is always the smaller number.
# - In the recursive case where `A` is less than `B`, it calculates the remainder `T` when `B` is divided by `A`, then recursively calls `gcd(A, T, X)` to find the GCD of `A` and `T`.

# This recursive approach continues until it reaches one of the base cases, ensuring termination. Overall, this code efficiently calculates the GCD of two numbers using the Euclidean algorithm in Prolog.