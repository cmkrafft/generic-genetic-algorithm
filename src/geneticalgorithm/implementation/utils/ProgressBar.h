//
// Created by Christopher Krafft on 08.11.20.
//

#ifndef GENETICALGORITHM_PROGRESSBAR_H
#define GENETICALGORITHM_PROGRESSBAR_H

/**
 * Helper class to plot progress bar to stdout
 */
class ProgressBar {
public:
    /**
     * Create ProgressBar object
     */
    ProgressBar();

    /**
     * Initialize ProgressBar with given size, which will be interpreted as 100%
     * @param n_size Total size
     */
    void init(long n_size);

    /**
     * Draw next n steps of progress
     * @param n_steps Steps to draw
     */
    void proceed(long n_steps);

private:
    const long max = 100;
    const int max_percentage_length = 6;

    long current_step = 0;
    long total_steps = -1;

    /**
     * Append current percentage to the end of the progress bar
     * @param percentage
     */
    void append_percentage(double percentage) const;

    /**
     * Fill progress bar with given amount of spaces
     * @param n_spaces Amount of spaces to insert
     */
    static void fill(long n_spaces);
};


#endif //GENETICALGORITHM_PROGRESSBAR_H
