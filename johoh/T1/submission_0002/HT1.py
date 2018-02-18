def Main():
    mittausten_lukumäärä = -1
    while mittausten_lukumäärä <= 0:
        mittausten_lukumäärä = int(input("Syötä mittausten lukumäärä: "))
        if mittausten_lukumäärä <=0:
            print("Virhe: mittausten lukumäärän tulee olla positiivinen kokonaisluku.")

    edellinen = 7.0
    summa = 0
    i = 1
    while i <= mittausten_lukumäärä:
        mittaustulos = float(input("Syötä " + str(i) + ". mittaustulos: "))
        if 6. <= mittaustulos <= 8.0 and abs(mittaustulos - edellinen) <= 1:
            summa = summa + mittaustulos
            edellinen = mittaustulos
        else:
            print("Olosuhteet eivät ole seeprakalalle sopivat.")
            break
        i = i + 1
    else:
        keskiarvo = round(summa / mittausten_lukumäärä, 2)
        print("Olosuhteet ovat seeprakalalle sopivat. Mittausten keskiarvo on {:.2f}.".format(keskiarvo))

Main()