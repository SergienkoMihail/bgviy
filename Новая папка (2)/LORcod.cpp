#include <iostream>
#include <chrono>
#include <random>

// Генератор случайных чисел Парка-Миллера с перетасовкой
class ParkMillerShuffle {
private:
    unsigned long long seed;
    unsigned long long a;
    unsigned long long m;
public:
    ParkMillerShuffle(unsigned long long seed = 1) : seed(seed), a(16807), m(2147483647) {}
    double operator()() {
        // Вычисляем новое значение seed
        seed = (a * seed) % m;
        // Перетасовываем биты
        seed = (seed << 32) | (seed >> 32);
        return static_cast<double>(seed) / m;
    }
};

// Генератор случайных чисел Парка-Миллера без перетасовки
class ParkMiller {
private:
    unsigned long long seed;
    unsigned long long a;
    unsigned long long m;
public:
    ParkMiller(unsigned long long seed = 1) : seed(seed), a(16807), m(2147483647) {}
    double operator()() {
        // Вычисляем новое значение seed
        seed = (a * seed) % m;
        return static_cast<double>(seed) / m;
    }
};

int main() {
    setlocale(0, "rus");
    // Инициализируем генератор случайных чисел с помощью текущего времени
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    // Создаем экземпляры генераторов случайных чисел Парка-Миллера с перетасовкой и без
    ParkMillerShuffle pm_shuffle(gen());
    ParkMiller pm(gen());

    // Генерируем 10 случайных чисел с помощью каждого генератора и выводим их на экран
    std::cout << "Случайные числа с помощью генератора Парка-Миллера с перетасовкой:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << pm_shuffle() << '\n';
    }

    std::cout << "\nСлучайные числа с помощью генератора Парка-Миллера без перетасовки:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << pm() << '\n';
    }

    return 0;
}