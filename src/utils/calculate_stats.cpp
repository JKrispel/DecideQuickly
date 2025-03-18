#include "utils/calculate_stats.h"

static std::vector<std::string> splitFilenames(const std::string& filenames) {
    std::vector<std::string> result;
    std::stringstream ss(filenames);
    std::string token;

    while (std::getline(ss, token, ';')) {  // pliki oddzielone średnikiem
        result.push_back(token);
    }
    return result;
}

static double calculateAverage(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Blad przy otwieraniu pliku: " << filename << std::endl;
        return -1.0;
    }

    std::vector<double> values;
    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double time;
        if (!(iss >> time)) {
            std::cerr << "Pomijam nieprawidlowa linijke " << filename << ": " << line << std::endl;
            continue;
        }

        values.push_back(time);
        count++;
        if (count == 3600) break;  // 3600 próbek == 1 minuta gry w 60FPS
    }
    file.close();

    if (values.size() < 3600) {
        std::cerr << "Not enough samples in " << filename << " (only " << values.size() << " found)" << std::endl;
        return -1.0;
    }

    double sum = 0.0;
    for (double t : values) {
        sum += t;
    }

    return sum / values.size();
}

void calculateStats(const std::string& filenames) {
    std::vector<std::string> file_list = splitFilenames(filenames);

    for (const auto& filename : file_list) {
        double avg_value = calculateAverage(filename);
        if (avg_value >= 0.0) {

            std::string unit = (filename.rfind("memory", 0) == 0) ? " MB" : " ms";  // czy dotyczy pamięci
            std::cout << "Sredni czas wykonania dla " << filename << ": "
                << std::fixed << std::setprecision(6) << avg_value << unit << std::endl;
        }
        else {
            std::cout << "Nie udalo sie obliczyc dla " << filename << std::endl;
        }
    }
}
