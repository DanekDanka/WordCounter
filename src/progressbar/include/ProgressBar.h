#pragma once
#include <atomic>


namespace wordCounter {
    class ProgressBar {
    public:
        ProgressBar() = default;
        ~ProgressBar() = default;

        void setProgress(float newPersentage);
        float getProgress() const;
        std::atomic<float> *getPersentagePtr();

    private:
        std::atomic<float> persentage;

    };
}
