#ifndef LISTA_HH
#define LISTA_HH

#include <string>

using namespace std;

class Lista {
public:
  Lista();

  void lisaa_alkio_loppuun(const string& lisattava_tehtava);
  bool poista_alkio_alusta(string& poistettu_tehtava);
  bool poista_alkio(string poistettava_tehtava);
  bool onko_tyhja() const;
  void tulosta() const;

 ~Lista();

private:
  struct Listan_alkio {
     string tehtava;
     Listan_alkio *seuraavan_osoite;
  };

  Listan_alkio *ensimmaisen_osoite_;
  Listan_alkio *viimeisen_osoite_;
};

#endif
