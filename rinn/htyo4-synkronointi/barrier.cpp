#include "barrier.h"

Barrier::Barrier() {
    saikeidenMaara_ = 0;
    laskuri_ = 0;
    lippu_ = false;
    lopetus_ = std::function<void()>();
}

Barrier::Barrier(int saikeidenMaara, std::function<void()> lopetus)
{
    saikeidenMaara_ = saikeidenMaara;
    laskuri_ = 0;
    lippu_ = false;
    lopetus_ = lopetus;
}

void Barrier::saavuJaOdota(bool* lokaaliLippu)
{
    (*lokaaliLippu) = !(*lokaaliLippu);
    std::unique_lock<std::mutex> lukko(muutosOikeus_);
    if (++laskuri_ == saikeidenMaara_) {
        // kaikki säikeet joita odotetaan ovat saapuneet

        if (lopetus_) {
            // jos lopetusfunktio on asetettu kutsu sitä
            lopetus_();
        }

        // vaihda lippu
        lippu_ = (*lokaaliLippu);

        // nollaa laskuri
        laskuri_ = 0;

        //vapauta lukitus, koska sitä ei enää tarvita ja heräävät säikeet haluavat sen
        lukko.unlock();

        // herätä nukkuvat säikeet
        jono_.notify_all();
    } else {
        // vapauta lukko ja jää nukkumaan kunnes kaikki säikeet ovat saapuneet barrierille
        jono_.wait(lukko, [this, lokaaliLippu] {return !(lippu_^(*lokaaliLippu));});
    }
}

void Barrier::alusta(int saikeidenMaara, std::function<void()> lopetus) {
    saikeidenMaara_ = saikeidenMaara;
    laskuri_ = 0;
    lippu_ = false;
    lopetus_ = lopetus;
}
