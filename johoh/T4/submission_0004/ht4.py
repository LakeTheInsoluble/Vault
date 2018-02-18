def nimidict():
    """Palauttaa nimi dictin jos kaikki kunnossa, muuten palauttaa None.

    :return: nimet dict sisältää osallistujnumerot tunnisteena ja nimet avaimena.
    """
    try:
        nimetnimi = input("Anna nimitiedoston nimi: ")
        nimitiedosto = open(nimetnimi)
        nimet = {}
        for r in nimitiedosto:
            tiedot = r.split(":")
            nimi = tiedot[0].rstrip()
            nro = tiedot[1]
            if nro == "":
                print("Virhe: kilpailunumeroiden on oltava kokonaislukuja.")
                return None
            nro = nro.rstrip()
            if nro in nimet:
                print("Virhe: tiedostossa samoja kilpailunumeroita.")
                return None
            else:
                nimet[nro] = nimi
        return nimet
    except FileNotFoundError:
        print("Virhe: tiedostoa", nimetnimi ,"ei voida lukea.")
        return None
    except IndexError:
        print("Virhe: nimitiedoston rivien oltava muotoa nimi:kilpailunumero.")
        return None
    except SyntaxError:
        print("Virhe: kilpailunumeroiden on oltava kokonaislukuja.")
        return None



def pisteetdict(nimet):
    """Palauttaa pisteet dictin jos kaikki kunnossa, muuten palauttaa None.
    Pisteet dict muodostetaan summaamalla tieostosta löytyvät pisteet yhteen.

    :param nimet: dicti joka sisältää jo olemassa olevat kilpailijanumerot
    :return: pisteet dict sisältää osallistujanumeron ja pisteiden summan
    """
    try:
        pisteetnimi = input("Anna pistetiedoston nimi: ")
        pistetiedosto = open(pisteetnimi)
        pisteet = {}
        for r in pistetiedosto:
            tiedot = r.split(":")
            nro = tiedot[0].rstrip()
            pst = int(tiedot[1].rstrip())
            if nro in nimet:
                if nro in pisteet.keys():
                    pst = pisteet[nro] + pst
                    pisteet[nro] = pst
                else:
                    pisteet[nro] = pst
            else:
                print("Virhe: tiedostossa tuntematon kilpailunumero.")
                return None
        return pisteet
    except FileNotFoundError:
        print("Virhe: tiedostoa", pisteetnimi ,"ei voida lukea.")
        return None
    except IndexError:
        print("Virhe: pistetiedoston rivien oltava muotoa kilpailunumero:pisteet.")
        return None
    except ValueError:
        print("Virhe: pisteiden on oltava kokonaislukuja.")
        return None



def main():
    try:
        nimet = nimidict()
        if not nimet == None:
            pisteet = pisteetdict(nimet)

        if not pisteet == None or nimet == None:
            print("Seitsenottelun tulokset ovat:")
            i = 1
        for nimi in sorted(pisteet, key = lambda x: pisteet[x], reverse = True):
            print(i,". ", nimet[nimi], ":", pisteet[nimi], sep='')
            i+=1
    except:
        pass

main()