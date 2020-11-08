//
// Created by Christopher Krafft on 08.11.20.
//

#ifndef GENETICALGORITHM_PROGRESSBAR_H
#define GENETICALGORITHM_PROGRESSBAR_H


#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

class ProgressBar {
public:
    ProgressBar();

    void init(long n_size) {
        this->current_step = 0;
        this->total_steps = n_size;

        std::cout << "[";

        for (int i = 0; i < this->max; i++) {
            std::cout << " ";
        }

        std::cout << "]";

        append_percentage(0L);
    }

    void proceed(long n_steps) {
        std::cout << "\r";

        std::cout << std::flush;

        this->current_step += n_steps;

        auto share = (double) this->current_step / (double) this->total_steps * (double) max;

        std::cout << "[";

        for (int i = 0; i < share - 1; i++) {
            std::cout << "=";
        }

        std::cout << ">";

        fill(std::floor(this->max) - share);

        append_percentage(share);

        std::cout << std::flush;

        if (this->current_step == this->total_steps) {
            std::cout << std::endl;
        }
    }

private:
    const long max = 100;
    const int max_percentage_length = 6;

    long current_step = 0;
    long total_steps;

    void append_percentage(double percentage) const {
        std::ostringstream s;
        s << std::fixed;
        s << std::setprecision(2);
        s << percentage;
        std::string p = s.str();

        std::cout << " | ";

        for (int i = 0; i < this->max_percentage_length - p.length(); i++) {
            std::cout << " ";
        }

        std::cout << p << " %";
    }

    static void fill(long n_spaces) {
        for (int i = 0; i < n_spaces; i++) {
            std::cout << " ";
        }

        std::cout << "]";
    }
};


#endif //GENETICALGORITHM_PROGRESSBAR_H
