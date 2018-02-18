import math

def lue_biometriikkarekisteri(tiedoston_nimi):
    """ Funktio lukee biometrisen informaation tehtävänannon määrämässä
    muodossa olevasta tiedostosta. Luettu informaatio jäsennellään ja
    talletetaan tietorakenteeseen, jonka harjoitustyön tekijä saa valita itse
    (ohjelmakoodissa tämä rakenne on nimetty muuttujaksi «tulos»).

    :param tiedoston_nimi: tiedoston nimi, josta biometrinen
             informaatio luetaan.
    :return: Palauttaa tietorakenteen, johon koko tiedosto on  luettu
             ja tallennettu. Virhetilanteessa palauttaa arvon None.
    """
    tulos = []

    aiemmin_käsitellyt_passit = []

    try:
        with open(tiedoston_nimi, mode="r") as tiedosto_olio:
            for rivi in tiedosto_olio:
                rivi = rivi.rstrip()

                kentät = rivi.split(';')

                if len(kentät) != 8:
                    print("Virhe: syötetiedoston rivillä väärä määrä kenttiä:")
                    print("'", rivi, "'", sep="")
                    return None

                # Muutetaan listan lopussa viisi biometrista
                # arvoa merkkijonosta desimaaliluvuiksi.
                for indeksi in range(3, 8):
                    kentät[indeksi] = float(kentät[indeksi])
                    if not (0 <= kentät[indeksi] <= 3.0):
                        print("Virhe: tiedostossa virheellinen arvo rivillä:")
                        print("'", rivi, "'", sep="")
                        return None

                nimi = kentät[0] + ", " + kentät[1]
                passi = kentät[2]
                biometriikka = [nimi, passi, kentät[3:]]

                if passi in aiemmin_käsitellyt_passit:
                    print("Virhe: passi nro.", passi, "toistuu.")
                    return None
                else:
                    aiemmin_käsitellyt_passit.append(passi)

                tulos.append(biometriikka)

        return tulos

    except FileNotFoundError:
        print("Virhe: tiedostoa", tiedoston_nimi, "ei saa avattua.")

    except ValueError:
        print("Virhe: tiedostossa ei-numeerinen biomeriikka-arvo rivillä:")
        print("'", rivi, "'", sep="")

    return None

def samat(a, b):
    """Funktio tutkii ovatko annetut vektorit tarpeeksi lähellä toisiaan.

    :param a: ensimmäinen vektori
    :param b: toinen vektori
    :return: tosi jos olivat, muuten epätosi
    """
    d=math.sqrt(math.pow((a[0]-b[0]),2)
                +math.pow((a[1]-b[1]),2)
                +math.pow((a[2]-b[2]),2)
                +math.pow((a[3]-b[3]),2)
                +math.pow((a[4]-b[4]),2))
    if d < 0.1:
        return True
    else:
        return False


def suorita_samat(biorekisteri):
    """Funktio etsii tietorakenteesta tarpeeksi lähellä toisiaan olevat
    henkilöt ja tulostaa heidän nimensä ja tietonsa.

    :param biorekisteri: tietorakenne, joka sisältää henkilöiden tiedot
    """
    tulostetut = []
    for i in range(0, len(biorekisteri)-1):
        if i not in tulostetut:
            samoja = [i]
            for j in range(i+1, len(biorekisteri)-1):
                if samat(biorekisteri[i][2], biorekisteri[j][2]):
                    samoja.append(j)
            if len(samoja) > 1:
                print("Mahdollisesti samat henkilöt:")
                for i in samoja:
                    print(biorekisteri[i][0], ";", biorekisteri[i][1],
                    ";{:.2f};{:.2f};{:.2f};{:.2f};{:.2f}".format(
                    biorekisteri[i][2][0],
                    biorekisteri[i][2][1],
                    biorekisteri[i][2][2],
                    biorekisteri[i][2][3],
                    biorekisteri[i][2][4]), sep="")
                    tulostetut.append(i)
                print()
    if len(tulostetut) == 0:
        print("Ei samoja henkilöitä.")



def suorita_haku(biorekisteri):
    """Funktio etsii tietorakenteesta tarpeeksi lähellä haettua olevat
    henkilöt ja tulostaa heidän tietonsa.

    :param biorekisteri: tietorakenne, joka sisältää henkilöiden tiedot
    """
    while True:
        syöte = input("Syötä 5 mittausarvoa puolipisteellä eroteltuna: ")
        if len(syöte.split(";")) == 5:
            haettava = syöte.split(";")
            try:
                for i in range(0,5):
                    haettava[i] = float(haettava[i])
                break
            except ValueError:
                print("Virhe: syötä vain desimaalilukuja: yritä uudelleen.")

        else:
            print("Virhe: väärä määrä syötteitä: yritä uudelleen.")
    löydetyt = []
    for i in range(0,len(biorekisteri)-1):
        if samat(haettava,biorekisteri[i][2]):
            löydetyt.append(i)
    if len(löydetyt) > 0:
        print("Löytyi epäiltyjä:")
        for i in löydetyt:
            print(biorekisteri[i][0], ";", biorekisteri[i][1],
                  ";{:.2f};{:.2f};{:.2f};{:.2f};{:.2f}".format(
                  biorekisteri[i][2][0],
                  biorekisteri[i][2][1],
                  biorekisteri[i][2][2],
                  biorekisteri[i][2][3],
                  biorekisteri[i][2][4]), sep="")
    else:
        print("Ei löytynyt epäiltyjä.")
    print()


def main():

    rekisteritiedosto = input("Syötä rekisteritiedoston nimi: ")

    biometriikkarekisteri = lue_biometriikkarekisteri(rekisteritiedosto)

    if biometriikkarekisteri is not None:
        while True:
            komento = input("komento [haku/samat/<enter>] ")
            if komento == "":
                return
            elif komento == "samat":
                suorita_samat(biometriikkarekisteri)
            elif komento == "haku":
                suorita_haku(biometriikkarekisteri)
            else:
                print("Virhe: tuntematon komento '", komento,
                      "': yritä uudelleen.", sep="")

main()