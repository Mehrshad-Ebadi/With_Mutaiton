#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

using namespace std;

int main() {
    // Given coefficients
    double a = 433.4;
    double b = 0.013;
    double local_max = 497.0;
    double c = 20.7;

    // Generate and save 10,000 random numbers to output.txt
    ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        // Seed for random number generation
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < 100000; ++i) {
            // Generate a uniform random variable between 0 and 1
            double U = dis(gen);

            // Calculate x using the corrected equation
            double x = local_max - (1 / b) * log(1 - U);

            // Calculate y using the given function with coefficients a, b, c, and local_max
            double randomNumber = local_max - log(a * U + c) / b;

            // Write the random number to the output file
            outputFile << randomNumber << endl;
        }

        // Close the output file
        outputFile.close();
        cout << "Random numbers saved in output.txt." << endl;
    } else {
        cout << "Error opening output file." << endl;
    }

    return 0;
}
