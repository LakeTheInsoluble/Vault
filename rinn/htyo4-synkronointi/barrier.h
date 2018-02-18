#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>
#include <functional>


class Barrier
{
private:
    int saikeidenMaara_;
    int laskuri_;
    bool lippu_;
    std::function<void()> lopetus_;

    std::mutex muutosOikeus_;
    std::condition_variable jono_;


public:
    Barrier();

    Barrier(int saikeidenMaara, std::function<void()> lopetus);

    //mutex ja condition_variable eivät ole kopioitavia joten luokan kopiointi
    //on myös estetty
    Barrier(Barrier const&) = delete;
    Barrier& operator=(Barrier const&) = delete;

    void saavuJaOdota(bool* lokaaliLippu);

    void alusta(int saikeidenMaara, std::function<void()> lopetus);

    void alustaLaskuri();

};

#endif // BARRIER_H
