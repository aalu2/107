#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double real = 0.0, double imaginary = 0.0) : real(real), imaginary(imaginary) {}

    double getReal() const {
        return real;
    }

    double getImaginary() const {
        return imaginary;
    }

    Complex operator+(const Complex& other) const {
        double sumReal = real + other.real;
        double sumImaginary = imaginary + other.imaginary;
        return Complex(sumReal, sumImaginary);
    }

    Complex operator-(const Complex& other) const {
        double diffReal = real - other.real;
        double diffImaginary = imaginary - other.imaginary;
        return Complex(diffReal, diffImaginary);
    }

    Complex operator*(const Complex& other) const {
        double prodReal = real * other.real - imaginary * other.imaginary;
        double prodImaginary = real * other.imaginary + imaginary * other.real;
        return Complex(prodReal, prodImaginary);
    }

    Complex operator/(const Complex& other) const {
        double divider = other.real * other.real + other.imaginary * other.imaginary;
        double divReal = (real * other.real + imaginary * other.imaginary) / divider;
        double divImaginary = (imaginary * other.real - real * other.imaginary) / divider;
        return Complex(divReal, divImaginary);
    }

    double magnitude() const {
        return std::sqrt(real * real + imaginary * imaginary);
    }

    double angle() const {
        return std::atan2(imaginary, real);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex) {
        os << "(" << complex.real << ", " << complex.imaginary << ")";
        return os;
    }
};

int main() {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    Complex sum = c1 + c2;
    std::cout << "Sum: " << sum << std::endl;

    Complex diff = c1 - c2;
    std::cout << "Difference: " << diff << std::endl;

    Complex prod = c1 * c2;
    std::cout << "Product: " << prod << std::endl;

    Complex div = c1 / c2;
    std::cout << "Division: " << div << std::endl;

    double magnitude = c1.magnitude();
    std::cout << "Magnitude of c1: " << magnitude << std::endl;

    double angle = c1.angle();
    std::cout << "Angle of c1: " << angle << " radians" << std::endl;

    return 0;
}
