#include <iostream>
#include <cmath>

class Field {
protected:
    double* value;

public:
		Field() {
				value = new double[3];
				value[0] = value[1] = value[2] = 0.0;
				}

		Field(double x, double y, double z) {
				value = new double[3];
				value[0] = x;
				value[1] = y;
				value[2] = z;
				}

		virtual ~Field() { delete[] value; }

		void printMagnitude() const {
				std::cout << "Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")\n";
				}
};

class ElectricField : public Field {
private:
		double calculatedE;

public:
		ElectricField() : Field() {}
		ElectricField(double x, double y, double z) : Field(x, y, z) {}

void calculateElectricField(double Q, double r) {
		const double epsilon_0 = 8.854187817e-12; // permittivity of free space
		calculatedE = Q / (4 * M_PI * r * r * epsilon_0);
		}

		ElectricField operator+(const ElectricField& other) const {
				return ElectricField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
		}

		friend std::ostream& operator<<(std::ostream& os, const ElectricField& e) {
				os << "Electric Field Components: (" << e.value[0] << ", " << e.value[1] << ", " << e.value[2] << ")";
				return os;
				}
};

class MagneticField : public Field {
private:
		double calculatedB;

public:
		MagneticField() : Field() {}
		MagneticField(double x, double y, double z) : Field(x, y, z) {}

void calculateMagneticField(double I, double r) {
		const double mu_0 = 4 * M_PI * 1e-7; // permeability of free space
		calculatedB = I / (2 * M_PI * r * mu_0);
		}

MagneticField operator+(const MagneticField& other) const {
		return MagneticField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
		}

friend std::ostream& operator<<(std::ostream& os, const MagneticField& m) {
		os << "Magnetic Field Components: (" << m.value[0] << ", " << m.value[1] << ", " << m.value[2] << ")";
		return os;
		}
};

int main() {
		ElectricField e1(0, 1e5, 1e3), e2(1e4, 2e5, 3e3);
		MagneticField m1(0.1, 0.2, 0.3), m2(0.4, 0.5, 0.6);

		e1.printMagnitude();
		m1.printMagnitude();

		e1.calculateElectricField(1e-6, 0.05);
		m1.calculateMagneticField(10, 0.02);

		ElectricField e3 = e1 + e2;
		MagneticField m3 = m1 + m2;

		std::cout << e3 << std::endl;
		std::cout << m3 << std::endl;

return 0;
}

