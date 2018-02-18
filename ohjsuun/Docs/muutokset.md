Ohjelmistojen suunnittelu TIE-20200


# Train Crash - Loppuraportti
### 9.12.2017

Pauli Jaakkola   218681

Henri Laakso     240062

Inkeri Välkki	   246800


## Ohjeet ohjelman kääntämiseen

Ohjelma on toteutettu C++:lla ja QML:llä. Helpoiten ohjelma kääntyy
QtCreatorilla, avaamalla TrainCrash.pro projektitiedosto. Peli toimii Qt:n
versiolla 5.9 ja vaatii Qt Positioning kirjaston, joka ilmeisestipuuttuu ainakin Linux-desktopilta, mutta tulee Qt:n oletusasennuksen mukana.

## Muutoksia suunnitteluvaiheesta

Mitaleiden ansaitsemista ei ole toteutettu.

StationsModel ja TracksModel luodaan joka pelin alussa kuten muutkin mallit.
Lisättiin kauppaa varten ostettavien junien katalogi. Lisättiin myös
pelaajamalli pelaajan valitsemista ja pelaajien (ja mitalien, jos/kun ne
toteutetaan) tallentamista ja lataamista varten. Myös nämä uudet mallit
periytyvät QAbstractListModelista.

Tilakone luotiinkin QML:ssä, jotta se pääsisi helpommin käsittelemään
käyttöliittymää tilasiirtymien yhteydessä. Osa kontrollerien metodeista
toteutettiinkin signaaleina ja kytkettiin sitten tilakoneen määrittelyssä.

Huoltojunan liikuttelu saatiin välinäyttöön vain puolivalmiiksi eli huoltojuna
teleporttaili raiteilla kulkemisen sijaan. (Nyt se toimii oikein). Huoltojunia
voi olla pelissä useita yhtä aikaa alun perin suunnitellun yhden sijaan.

Luokkien attribuutit ja rajapinnat eivät enimmäkseen vastaa alkuperäistä
luokkadiagrammia. Suunnitteluvaiheessa emme oikein osanneet ennustaa, mitä
niiden pitäisi olla.

## Suunniteltuja muutoksia ja havaittuja ongelmia

Mitaleiden ansaitseminen pitäisi toteuttaa.

StationsModelin ja TracksModelin voisi luoda alkuperäisen suunnitelman
mukaisesti jo ohjelman käynnistyessä. Tämä säästäisi hieman resursseja. Vielä
tehokkaampaa olisi ladata myös päivän aikataulut vain kerran eikä joka pelin
alussa. Sitten pitäisi tietenkin huolehtia siitä, että aikataulut ladataan jos
päivä ehtii vaihtua pelien välillä.

Peliin pitäisi ehkä lisätä latausnäyttö, koska hitaammilla internet-yhteyksillä
aikataulujen lataus saattaa kestää pitkäänkin ja tuona aikana pelaaja voi joko
ihmetellä missä matkustajajunat ovat tai siivoilla roskia pois kaikessa
rauhassa.

Pelin sopiva haasteellisuus ja pelattavuus vaativat vielä paljon säätöä. Myös
käyttöliittymän ulkonäköä olisi syytä parannella ja brändäystä miettiä.
Käyttäjätestausta ei ole tehty (eikä kannattaisikaan tällä pelattavuudella).

Myös automaattiset testit puuttuvat, yksikkötesteistä lähtien.

Refaktoroinnille olisi monin paikoin kysyntää. Esimerkiksi QML-tiedostojen
sisältö ja `TracksModel::getShortestPath` ovat kovin monoliittisia ja useissa
paikoissa käytetään `std::dynamic_pointer_cast`:ia, mikä on aika huonoa
olio-ohjelmointia.

## Liitteet:

Alkuperäinen suunnitelma
