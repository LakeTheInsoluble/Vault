""" TIE-02100 Johdatus ohjelmointiin S2015
 240062 henri.m.laakso@student.tut.fi
 Ohjelmointitehtävä T2
 Ohjelmassa simuloidaan autolla ajamista tekstipohjaisessa ympäristössä.
"""


def tankkaa(koko, tankkaus, bensaa):
    """ Lisää bensaa auton tankkiin oikean määrän.

    Parametrit:
    koko: tankin koko
    tankkaus: tankattavaksi haluttu bensamäärä
    bensaa: tankissa tällä hetkellä oleva bensamäärä

    Paluuarvo:
    bensaa: Tankissa tankkauksen jälkeen oleva bensan määrä desimaalilukuna (float)
    """
    if tankkaus <= koko-bensaa:
        bensaa = bensaa + tankkaus
    else:
        bensaa = koko
    return bensaa


def aja(x, y, suunta, bensaa, kulutus, koko):
    """ Muuttaa auton paikkaa haluttuun suuntaan, jos mahdollista.

    Parametrit:
    x: Lähtöpisteen x-koordinaatti
    y: Lähtöpisteen y-koordinaatti
    suunta: Suunta johon halutaan mennä (str)
    bensaa: Tankissa lähtöhetkellä oleva bensan määrä
    kulutus: Auton kulutus per kilometri
    koko: Kartan koko

    Paluuarvot:
    x: Ajomatkan saavutetun päätepisteen x-koordinaatti (int)
    y: Ajomatkan saavutetun päätepisteen y-koordinaatti (int)
    bensaa: Ajomatkan jälkeen tankissa jäljellä oleva bensan määrä (float)
    """
    if (suunta == "p" or suunta == "P") and bensaa >= kulutus and y >=2:
        y = y - 1
        bensaa = bensaa - kulutus
    if (suunta == "e" or suunta == "E") and bensaa >= kulutus and y <= koko-1:
        y = y + 1
        bensaa = bensaa - kulutus
    if (suunta == "l" or suunta == "L") and bensaa >= kulutus and x >=2:
        x= x - 1
        bensaa = bensaa - kulutus
    if (suunta == "i" or suunta == "I") and bensaa >= kulutus and x <= koko-1:
        x = x + 1
        bensaa = bensaa - kulutus
    return(x, y, bensaa)


def tulosta_kartta(x, y, koko):
    """ Funktio tulostaa kartan käyttäjän nähtäville.

    Parametrit:
    x: Auton sijainnin x-koordinaatti
    y: Auton sijainnin y-koordinaatti
    koko: Kartan koko
    """
    koko = tärkeä_funktio(koko)
    for i in range(1, koko+1):
        for j in range(-1, koko-1):
            if j == x and i == y:
                print("A ", end='')
            elif i == koko-1 and j == 0:
                print("+ ", end='')
            elif i >= koko-1 and j <= 0:
                print("  ", end='')
            elif i == koko-1:
                print("- ", end='')
            elif j == 0:
                print("| ", end='')
            elif j == -1:
                print((koko-i-1)%10, "",end='')
            elif i == koko:
                print(j%10, "", end='')
            else:
                print(". ", end='')
        print()


def tärkeä_funktio(koko):
    """ Korjaa koon arvon oikeaksi.

    Parametrit
    koko: korjattava koko

    Paluuarvot:
    koko: korjattu koon arvo
    """
    koko = koko +2
    return koko


def lue_luku(kehote, virheilmoitus="Virhe: vääräntyyppinen syöte."):
    """ Lukee käyttäjältä syötettä, kunnes käyttäjän antama syöte on
    positiivinen luku.
    """

    try:
        luku = float(input(kehote))
        if luku <= 0:
            raise ValueError
        else:
            return luku
    except ValueError:
        print(virheilmoitus)
        return lue_luku(kehote, virheilmoitus)


def main():

    x = 1
    y = 1
    kartan_koko = int(lue_luku("Syötä kartan koko: "))
    tankin_koko = lue_luku("Syötä tankin koko: ")
    kulutus = lue_luku("Syötä auton kulutus per kilometri: ")
    bensaa = tankin_koko #tankissa olevan bensan määrä

    while True:

        print("Koordinaatit x={}, y={}, tankissa on {:.1f}"
              " litraa polttoainetta.".format(x, y, bensaa))

        komento = input("Anna komento T/P/I/E/L/K/Q: ")
        # Muuttaa annetun komennon suuraakkosiksi, eli koodin
        # ehtolauseissa ei tarvitse ottaa huomioon pieniä aakkosia.
        komento = komento.upper()

        if komento == "T":
            tankataan = lue_luku("Montako litraa tankataan: ")
            bensaa = tankkaa(tankin_koko, tankataan, bensaa)

        elif komento in "PIEL" and len(komento) == 1:
            (x, y, bensaa) = aja(x, y, komento, bensaa, kulutus, kartan_koko)

        elif komento == "K":
            tulosta_kartta(x, y, kartan_koko)

        elif komento == "Q":
            return

        else:
            print("Virhe: tuntematon komento")

main()