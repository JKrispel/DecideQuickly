#include "utils/calculate_stats.h"

std::vector<std::string> split_filenames(const std::string& filenames) {
    std::vector<std::string> result;
    std::stringstream ss(filenames);
    std::string token;

    while (std::getline(ss, token, ';')) {  // pliki oddzielone średnikiem
        result.push_back(token);
    }
    return result;
}

double calculate_average_time(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Blad przy otwieraniu pliku: " << filename << std::endl;
        return -1.0;
    }

    std::vector<double> times;
    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double time;
        if (!(iss >> time)) {
            std::cerr << "Pomijam nieprawidlowa linijke " << filename << ": " << line << std::endl;
            continue;
        }

        times.push_back(time);
        count++;
        if (count == 3600) break;  // 3600 próbek == 1 minuta gry w 60FPS
    }
    file.close();

    if (times.size() < 3600) {
        std::cerr << "Not enough samples in " << filename << " (only " << times.size() << " found)" << std::endl;
        return -1.0;
    }

    double sum = 0.0;
    for (double t : times) {
        sum += t;
    }

    return sum / times.size();
}

void calculate_stats(const std::string& filenames) {
    std::vector<std::string> file_list = split_filenames(filenames);

    for (const auto& filename : file_list) {
        double avg_time = calculate_average_time(filename);
        if (avg_time >= 0.0) {
            std::cout << "Sredni czas wykonania dla " << filename << ": "
                << std::fixed << std::setprecision(6) << avg_time << " ms" << std::endl;
        }
        else {
            std::cout << "Nie udalo sie obliczyc dla " << filename << std::endl;
        }
    }
}
