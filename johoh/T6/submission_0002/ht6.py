class Kulkukortti:

    def __init__(self, tunniste, nimi):
        """
        Luokan rakentaja, eli metodi, joka antaa uuden olion
        luomisvaiheessa sille alkuarvon.

        :param tunniste: henkilön tunniste (str)
        :param nimi: henkilön nimi (str)
        """

        self.__tunniste = tunniste
        self.__nimi = nimi
        self.__alueet = []


    def tulosta_tiedot(self):
        """
        Tulostaa kulkukortin tiedot.
        """

        print(self.__tunniste, ", ", self.__nimi,", kulkualueet:",sep='',end='')
        if not len(self.__alueet) == 0:
            print(" ", ','.join(map(str,sorted(self.__alueet))), sep='',end='')
        print()


    def anna_nimi(self):
        """
        :return: Palauttaa kulkukortille talletetun henkilön nimen.
        """

        return self.__nimi


    def tarkista_pääsy(self, kulkualuekoodi):
        """
        Tarkastaa pääseeko kulkukortilla halutulle kulkualueelle.

        :param kulkualuekoodi: alue, jolle kortilla halutaan päästä
        :return: True: ovi avautuu kulkukortille tallennetuilla oikeuksilla.
                 False: ovi ei avaudu kulkukortin oikeuksilla
        """

        for alue in self.__alueet:
            tutkittava = kulkualuekoodi
            while len(tutkittava) > 0:
                if tutkittava == alue:
                    return True
                tutkittava = tutkittava[:-1]
        return False


    def lisää_kulkualue(self, uusi_alue):
        """
        Funktio lisää uuden alueen kulkukortin oikeuksiin.

        :param uusi_alue: Lisättävä kulkualue
        """

        if self.tarkista_pääsy(uusi_alue):
            return
        self.__alueet = sievennä_kulkuoikeuslista(uusi_alue, self.__alueet)


    def yhdistä_kulkukortti(self, toinen_kortti):
        """
        Yhdistää toinen_kortti-parametrin sisältämät kulkuoikeudet
        käsiteltävänä olevalle kortille.

        :param toinen_kortti: Kulkukortti, jonka kanssa oikeudet yhdistetään
        """

        for alue in toinen_kortti.__alueet:
            self.lisää_kulkualue(alue)


def pääsytesti(kulkuoikeus, tutkittava_alue):
    """
    Funktio tutkii oikeuttaako tietty kulkuoikeus pääsyn
    tutkittavana olevaan huoneeseen/alueelle.

    :param kulkuoikeus: Kulkuoikeus, jonka perusteella halutaan testata,
                       onko tutkittavalle_alueelle pääsyä.
    :param tutkittava_alue: Oikeuttaako parametri kulkuoikeus
                       pääsyyn tutkittavalle alueelle.
    :return: True, jos pääsy on sallittu, False muussa tapauksessa.
    """

    kulkuoikeus_laajuus = len(kulkuoikeus)
    tutkittava_laajuus = len(tutkittava_alue)

    if kulkuoikeus_laajuus <= tutkittava_laajuus:
        for i in range(kulkuoikeus_laajuus):
            if kulkuoikeus[i] != tutkittava_alue[i]:
                return False
    else:
        return False
    return True


def sievennä_kulkuoikeuslista(lisättävä_kulkualue, vanha_kulkuoikeuslista):
    """
    Poistaa lisättävää kulkualuetta suppeammat alueet listalta

    :param lisättävä_kulkualue: Lisättäväksi haluttu kulkualue.
    :param vanha_kulkuoikeuslista: Tämänhetkiset kulkuoikeudet.
    :return: Kulkualuelista, joka saadaan kun vanhasta kulkukoikeuslistasta
             on poistettu kaikki lisättävää kulkualuetta suppeammat (ja saman-
             laajuiset kulkualueet), minkä jälkeen lisättävä_kulkualue on
             liitetty saadun supistetun listan loppuun.
    """

    suodatetut = []
    kulku = vanha_kulkuoikeuslista
    kulku.append(lisättävä_kulkualue)

    for alue in vanha_kulkuoikeuslista:
        if not pääsytesti(lisättävä_kulkualue, alue):
            suodatetut.append(alue)

    suodatetut.append(lisättävä_kulkualue)

    return suodatetut


def main():
    kulkutiedot = {}

    try:
        with open("kulkutiedot.txt", mode="r", encoding='utf-8') as tiedosto:
            for rivi in tiedosto:
                tunniste, nimi, alueet = rivi.strip().split(";")
                kulkutiedot[tunniste] = Kulkukortti(tunniste, nimi)
                if alueet != "":
                    alueet = alueet.split(",")
                    for alue in alueet:
                        kulkutiedot[tunniste].lisää_kulkualue(alue)

        while True:
            rivi = input("komento> ")

            if rivi == "":
                break

            osat = rivi.split()
            käsky = osat[0]

            if käsky == "lista" and len(osat) == 1:
                for tunniste in sorted(kulkutiedot):
                    kulkutiedot[tunniste].tulosta_tiedot()

            elif käsky == "tiedot" and len(osat) == 2:
                tunniste = osat[1]
                if tunniste in kulkutiedot:
                    kulkutiedot[tunniste].tulosta_tiedot()
                else:
                    print("Virhe: tuntematon tunniste.")

            elif käsky == "kulku" and len(osat) == 3:
                tunniste = osat[1]
                alue = osat[2]
                if tunniste in kulkutiedot:
                    if kulkutiedot[tunniste].tarkista_pääsy(alue):
                        print("Kortilla ", tunniste, " ( ",
                        kulkutiedot[tunniste].anna_nimi(),
                        " ) on kulkuoikeus huoneeseen ", alue, sep='')
                    else:
                        print("Kortilla ", tunniste, " ( ",
                        kulkutiedot[tunniste].anna_nimi(),
                        " ) ei kulkuoikeutta huoneeseen ", alue, sep='')
                else:
                    print("Virhe: tuntematon tunniste.")

            elif käsky == "lisää" and len(osat) == 3:
                tunniste = osat[1]
                alue = osat[2]
                if tunniste in kulkutiedot:
                    kulkutiedot[tunniste].lisää_kulkualue(alue)
                else:
                    print("Virhe: tuntematon tunniste.")

            elif käsky == "yhdistä" and len(osat) == 3:
                kohdekortti = osat[1]
                lähdekortti = osat[2]
                if lähdekortti in kulkutiedot and kohdekortti in kulkutiedot:
                    kulkutiedot[kohdekortti].yhdistä_kulkukortti(kulkutiedot[lähdekortti])
                else:
                    print("Virhe: tuntematon tunniste.")
            else:
                print("Virhe: Väärä syöte, yritä uudelleen")
    except:
        print("Virhe: tiedostoa ei saa luettua.")


main()