#include <iostream>
#include <random>

int main()
{
    // Seed the random number generator (optional for better randomness)
    std::random_device rd;  // Use system entropy to seed
    std::mt19937 gen(rd()); // Use Mersenne Twister engine

    // Define the range for the six-digit number (100000 to 999999)
    std::uniform_int_distribution<> dist(100000, 999999);

    int i{};
    while (i - 100)
    {
        std::cout << dist(gen) << '\n';
        i++;
    }
    return 0;
}
