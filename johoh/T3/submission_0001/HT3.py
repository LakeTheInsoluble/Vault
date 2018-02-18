def tulosta(sana,arvatut):
    """ Tulostaa arvatut kirjaimet oikeina ja loput tyhjinä.

    :param sana: Arvattava sana.
    :param arvatut: Arvatut kirjaimet.
    :return: none
    """
    for kirjain in sana:
        if kirjain in arvatut:
            print(kirjain,end='')
        else:
            print("_",end='')
    print()


def loppu(sana, arvatut):
    """ Tarkistaa onko koko sana arvattu.

    :param sana: Arvattava sana.
    :param arvatut: Arvatut kirjaimet
    :return: Tosi jos kaikki arvattu, muute epätosi.
    """
    for kirjain in sana:
        if kirjain not in arvatut:
            return False
    return True


def arvaa_kirjain(arvatut):
    """ Tarkastaa arvatun kirjaimen oikeellisuuden.

    :param arvatut: Jo arvatut kirjaimet
    :return: Joko arvattu kirjain tai tyhjä, jos kirjain epäoikeellinen.
    """
    sana = input("Arvaa kirjain: ").upper()
    if len(sana) > 1:
        print("Virhe: syötä yksi kirjain.")
        return ""
    elif sana in arvatut:
        print("Hölmö arvaus,", sana, "on jo arvattu.")
        return ""
    else:
        return sana


def Main():
    sana = list(input("Syötä arvuuteltava sana: ").upper())
    print("Putsataan näyttö...\n\n\n\n\n\n\n\n\n\n")
    print("Peli alkakoon! Saat arvata 10 kirjainta. Mikä sana on kyseessä?")
    arvatut = ""
    tulosta(sana, arvatut)
    i = 0
    while(i < 10):
        arvatut += arvaa_kirjain(arvatut)
        tulosta(sana, arvatut)
        i += 1
        if loppu(sana, arvatut):
            break
    else:
        print("Arvauskerrat loppuivat kesken. Sana olisi ollut", ''.join(sana))
        exit()
    print("Hyvä! Arvasit koko sanan!")


Main()