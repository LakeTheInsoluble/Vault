#TIE-02100 Harjoitustyö 7
# Henri Laakso, 240062, 17.05.2016

# Tämä peli on perinteinen miinaharava.
# Voit valita kolmesta eri vaikeusasteesta sopivan tai customoida oman pelin.
# Peli alkaa klikkaamalla jotain pelin ruutua.
# Pelissä aukeaa alue, jossa on numeroita, jotka kertovat ympäröivien
# ruutujen miinojen määrän joko numeron vieressä sivuttain tai kulmittain.
# Peli etenee niin, että yrität avata ruutuja ja vältellä kyseisiä miinoja.
# Voit valita ylävalikosta myös Lippu-vaihtoehdon, jolla pystyt merkitsemään
# miinat pelin helpottamiseksi. Kun kaikki tyhjät ja numerolliset ruudut on
# avattu, voitat pelin. Mikäli kosketat miinaa, häviät pelin.
# Klikkaamalla numeroa, jonka kaikki viereiset miinat on merkitty lipulla, peli
# avaa automaattisesti kaikki sitä ympäröivät tyhjät ruudut.

# Protip: mielestäni peliä kannattaa pelata vain lippuja merkitsemällä ja
# numeroita klikkailemalla sekä avaamalla ruutuja vain pakon edessä.

# Huom!
# Suurella kentällä ja vähällä määrällä miinoja peli saavuttaa maksimi
# rekursion syvyyden. Tulostaa tällöin erroria.
# Päätin jättää tämän osaksi koodia, sillä tulokset olivat mielenkiintoisia.
# Virheen olisi voinut helposti välttää asettamalle custom kentälle maksimi
# suuruuden, mutta tämä olisi ollut ilonpilausta.

# Huom!
# Pienellä näytöllä tai suurella kentän koolla osa ikkunasta voi mennä näytön
# ulkopuolelle. Tkinter ei tarjonnut tähän järkevää ratkaisua tällä
# aikataululla ja osaamisella. Lisäksi kuvien ja tekstin koon määritteleminen
# eivät olleet kaikista helpoimpia esimerkiksi niiden fill ominaisuuden
# puuttuessa.

# Extra info:
# "" merkkaa avaamatonta ruutua
# " " merkkaa avattua ruutua, jonka numero on 0
# "  " merkkaa liputettua ruutua
# Nämä johtuvat siitä, että käytän tekstikenttää tunnisteena ja samalla käytän
# sitä myös näytettävänä tekstinä, kun mitään ei saa näkyä.
# Näytän tekstiä, jotta saisin nappulat samankokoisiksi, sillä tekstin
# height ja width eivät ole pikseleinä, toisin kuin kuvien height ja width.


from tkinter import *
from tkinter.messagebox import askyesno, showerror, showinfo
import random

class Valintaikkuna():
    """ Graafinen valintaikkuna miinaharavan vaikeustason valitsemiseksi. """

    def __init__(self):
        self.__custom = False
        self.__ikkuna = Tk()
        self.__ikkuna.title("Valintaikkuna")
        self.__helppo = Button(self.__ikkuna, command=lambda
                               x=6, y=10, m=10: self.aloita(x, y, m),
                               text="Helppo", font="Arial 10 bold",
                               pady=5, padx=70, borderwidth=5)
        self.__helppo.pack(fill=X)
        self.__keskiverto = Button(self.__ikkuna, command=lambda
                                   x=16, y=16, m=40: self.aloita(x, y, m),
                                   text="Keskiverto", font="Arial 10 bold",
                                   pady=5, borderwidth=5)
        self.__keskiverto.pack(fill=X)
        self.__vaikea = Button(self.__ikkuna,command=lambda
                               x=16, y=30, m=99: self.aloita(x,y,m),
                               text="Vaikea", font="Arial 10 bold",
                               pady=5, borderwidth=5)
        self.__vaikea.pack(fill=X)
        self.__oma = Button(self.__ikkuna, command=self.custom,
                            text="Custom", font="Arial 10 bold",
                            pady=5, borderwidth=5)
        self.__oma.pack(fill=X)
        self.__tyhjä = Label(self.__ikkuna)
        self.__tyhjä.pack(fill=X)
        self.__lopeta = Button(self.__ikkuna,command=self.__ikkuna.destroy,
                               text="Lopeta", font="Arial 10 bold",
                               pady=5, borderwidth=5)
        self.__lopeta.pack(fill=X)
        self.__korkeuslabel = Label(self.__ikkuna, text="Korkeus (min 8):",
                                    font="Arial 10 bold",
                                    pady=5, anchor=W, borderwidth=5)
        self.__leveyslabel = Label(self.__ikkuna,text="Leveys (min 8):",
                                   font="Arial 10 bold",
                                   pady=5, anchor=W, borderwidth=5)
        self.__miinojalabel = Label(self.__ikkuna,text="Miinoja:",
                                    font="Arial 10 bold",
                                    pady=5, anchor=W, borderwidth=5)
        self.__korkeus = Entry(font="Arial 10 bold")
        self.__leveys = Entry(font="Arial 10 bold")
        self.__miinoja = Entry(font="Arial 10 bold")
        self.__aloita = Button(self.__ikkuna, command=self.customaloita,
                               text="Aloita", font="Arial 10 bold",
                               pady=5, borderwidth=5)

        self.__ikkuna.mainloop()

    def custom(self):
        """ Avaa ja sulkee valikon omia asetuksia varten. """

        if self.__custom == False:
            self.__lopeta.forget()
            self.__tyhjä.forget()
            self.__korkeuslabel.pack(fill=X)
            self.__korkeus.pack(fill=X)
            self.__leveyslabel.pack(fill=X)
            self.__leveys.pack(fill=X)
            self.__miinojalabel.pack(fill=X)
            self.__miinoja.pack(fill=X)
            self.__aloita.pack(fill=X)
            self.__tyhjä.pack(fill=X)
            self.__lopeta.pack(fill=X)
            self.__custom = True
        else:
            self.__korkeuslabel.forget()
            self.__korkeus.forget()
            self.__leveyslabel.forget()
            self.__leveys.forget()
            self.__miinojalabel.forget()
            self.__miinoja.forget()
            self.__aloita.forget()
            self.__custom = False

    def aloita(self, x, y, m):
        """ Aloittaa miinaharavan halutuilla asetuksilla
        ja tuhoaa valintaikkunan.

         :param x, y: Miinaharavan tason korkeus ja leveys.
         :param m: Miinojen lukumäärä.
        """

        self.__ikkuna.destroy()
        Miinaharava(x,y,m)

    def customaloita(self):
        """ Aloittaa miinaharavan halutuilla asetuksilla
        ja tuhoaa valintaikkunan. Lisäksi tarkistaa syötteet virheiden varalta.
        """

        self.korkeus = self.__korkeus.get()
        self.leveys = self.__leveys.get()
        self.miinoja = self.__miinoja.get()
        try:
            k = int(self.korkeus)
            l = int(self.leveys)
            m = int(self.miinoja)
            if m > (l-1)*(k-1):
                showerror("Error", "Liikaa miinoja.\n"
                                   "Suurin määrä on (leveys-1)*(korkeus-1)")
            elif m < 0:
                showerror("Error", "Miinoja tulee olla positiivinen määrä")
            elif l < 8 or k < 8:
                showerror("Error", "Korkeus ja leveys oltava vähintään 8 x 8")
            elif l >= 8 and k >= 8 and m >= 0:
                if m == 0:
                    showinfo("Protip", "Olisit ny laittanu ees yhen miinan")
                self.aloita(k,l,m)
            else:
                showerror("Error", "Korkeus ja leveys oltava vähintään 8x8")
        except:
            showerror("Error","Virheellinen syöte")


class Miinaharava():
    """ Perinteinen Miinaharava-peli graafista käyttöliittymää hyödyntäen. """

    def __init__(self, x, y, m):
        self.__tiedot = (y,x,m)
        self.__ikkuna = Tk()
        self.__ikkuna.title("Miinaharava")
        self.__lippukuva = PhotoImage(file="lippu.png")
        self.__miinakuva = PhotoImage(file="miina.png")
        self.__miinoja = m
        self.__jäljellä = m
        self.__lippu = False
        self.__buttonit = [[None for i in range(x)]for i in range(y)]
        for i in range(y):
            for j in range(x):
                uusi_button = Button(self.__ikkuna)
                uusi_button.grid(row=j+1, column=i)
                self.__buttonit[i][j] = uusi_button

        for sarake in self.__buttonit:
            for button in sarake:
                button.configure(width=2, height=1,
                                 text="",
                                 relief=RAISED,
                                 borderwidth=3,
                                 state=NORMAL,
                                 font="Arial 12 bold",
                                 command=lambda
                                 x=self.__buttonit.index(sarake),
                                 y=sarake.index(button): self.aloitus(x, y))
        self.__avaabutton = Button(self.__ikkuna,
                                    command=self.lippu,
                                    text="Avaa",
                                    bg="tan",
                                    relief=SUNKEN,
                                    state=DISABLED)
        self.__avaabutton.grid(row=0, column=0, columnspan=3, sticky=E+W)
        self.__lippubutton = Button(self.__ikkuna,
                                    text="Lippu",
                                    bg=self.__ikkuna.cget("bg"))
        self.__lippubutton.grid(row=0, column=3, columnspan=3, sticky=E+W)
        self.__uusipelibutton = Button(self.__ikkuna,
                                    command=self.uusi,
                                    text="Uusi peli")
        self.__uusipelibutton.grid(row=x+2, column=0, columnspan=3, sticky=E+W)
        self.__valikkobutton = Button(self.__ikkuna,
                                    command=self.valikko,
                                    text="Valikko")
        self.__valikkobutton.grid(row=x+2, column=3, columnspan=3, sticky=E+W)
        self.__lopetabutton = Button(self.__ikkuna,
                                    command=self.__ikkuna.destroy,
                                    text="Lopeta")
        self.__lopetabutton.grid(row=x+2, column=y-2 ,columnspan=2 ,sticky=E+W)
        self.__jäljellälabel = Label(text=self.__jäljellä,
                                    font="Arial 10 bold")
        self.__jäljellälabel.grid(row=0, column=y-2, columnspan=2, sticky=E)

        self.__ikkuna.mainloop()

    def aloitus(self, x, y):
        """ Aloituspainalluksella avataan aina ruutu, jossa on 0 ja asetetaan
        painallusnappulaan oikea kutsu loppupeliä varten.

        :param x, y: Painetun nappulan koordinaatit.
        """

        if self.__lippu == False:
            self.__lauta = self.luolauta(x, y)
            self.__lippubutton.configure(command=self.lippu)
            for sarake in self.__buttonit:
                for button in sarake:
                    button.configure(command=lambda
                                    x=self.__buttonit.index(sarake),
                                    y=sarake.index(button):
                                    self.oikeapainallus(x, y))
        self.oikeapainallus(x,y)

    def oikeapainallus(self, x, y):
        """ Tekee voiton tarkistuksen painalluksen jälkeen
        ja suorittaa tarvittavat toimenpiteet.

        :param x, y: Painetun nappulan koordinaatit.
        """

        self.painallus(x, y)
        miinat = 0
        for sarake in self.__buttonit:
            for button in sarake:
                if button.configure("text")[-1] == ""\
                        or button.configure("text")[-1] == "  ":
                    miinat += 1
        if miinat == self.__miinoja:
            if self.__tiedot == (30,16,99):
                if askyesno("Voitit pelin",
                            "Amazing! Voitit haastavimman vaikeustason!\n"
                            "Haluatko pelata uudelleen?"):
                    self.uusi()
                else:
                    self.__ikkuna.destroy()
            else:
                if askyesno("Voitit pelin",
                            "Jeee! Voitit pelin.\nHaluatko pelata uudelleen?"):
                    self.uusi()
                else:
                    self.__ikkuna.destroy()

    def painallus(self, x, y):
        """ Nappulaa painettaessa tutkii sen tiedot ja suorittaa
        tarvittavat toimenpiteet, kuten avaa kaikki ympäröivät
        tai vain avaa kyseisen nappulan.

        :param x, y: Painetun nappulan koordinaatit.
        """

        # Jos nappula avattu ja numero ympäröivien lippujen lukumäärä
        # tai numero on " " eli 0 eli ei ympäröiviä miinoja.
        if (self.__buttonit[x][y].configure("relief")[-1] == SUNKEN
            and (self.__buttonit[x][y].configure("text")[-1] == str(
                                                    self.laskemerkatut(x,y))
                or self.__buttonit[x][y].configure("text")[-1] == " ")):
            if x+2 <= len(self.__buttonit) and y+2 <= len(self.__buttonit[0]):
                if self.__buttonit[x+1][y+1].configure("text")[-1] == "":
                    self.avaa(x+1,y+1)
                    # Jos avatun nappulan numero 0 avataan sitä ympäröivät
                    # ja painetaan tätä nappulaa.
                    if self.__buttonit[x+1][y+1].configure("text")[-1] == " ":
                        self.painallus(x+1,y+1)
            if x+2 <= len(self.__buttonit):
                if self.__buttonit[x+1][y].configure("text")[-1] == "":
                    self.avaa(x+1,y)
                    if self.__buttonit[x+1][y].configure("text")[-1] == " ":
                        self.painallus(x+1,y)
            if y+2 <= len(self.__buttonit[0]):
                if self.__buttonit[x][y+1].configure("text")[-1] == "":
                    self.avaa(x,y+1)
                    if self.__buttonit[x][y+1].configure("text")[-1] == " ":
                        self.painallus(x,y+1)
            if x-1 >= 0 and y-1 >= 0:
                if self.__buttonit[x-1][y-1].configure("text")[-1] == "":
                    self.avaa(x-1,y-1)
                    if self.__buttonit[x-1][y-1].configure("text")[-1] == " ":
                        self.painallus(x-1,y-1)
            if x-1 >= 0:
                if self.__buttonit[x-1][y].configure("text")[-1] == "":
                    self.avaa(x-1,y)
                    if self.__buttonit[x-1][y].configure("text")[-1] == " ":
                        self.painallus(x-1,y)
            if y-1 >= 0:
                if self.__buttonit[x][y-1].configure("text")[-1] == "":
                    self.avaa(x,y-1)
                    if self.__buttonit[x][y-1].configure("text")[-1] == " ":
                        self.painallus(x,y-1)
            if x+2 <= len(self.__buttonit) and y-1 >= 0:
                if self.__buttonit[x+1][y-1].configure("text")[-1] == "":
                    self.avaa(x+1,y-1)
                    if self.__buttonit[x+1][y-1].configure("text")[-1] == " ":
                        self.painallus(x+1,y-1)
            if x-1 >= 0 and y+2 <= len(self.__buttonit[0]):
                if self.__buttonit[x-1][y+1].configure("text")[-1] == "":
                    self.avaa(x-1,y+1)
                    if self.__buttonit[x-1][y+1].configure("text")[-1] == " ":
                        self.painallus(x-1,y+1)
        elif self.__lippu is True:
            if self.__buttonit[x][y].configure("text")[-1] == "":
                # Käyttämällä tyhjää tekstiä ja compound asetusta teksti
                # menee kuvan päälle ja buttonin koko määräytyy tekstin mukaan.
                self.__buttonit[x][y].configure(text="  ", compound=CENTER)
                self.__buttonit[x][y].configure(image=self.__lippukuva,
                                                height=24, width=22)
                self.__jäljellä -= 1
            elif self.__buttonit[x][y].configure("text")[-1] == "  ":
                self.__buttonit[x][y].configure(text="", compound=None)
                self.__buttonit[x][y].configure(image="", height=1, width=2)
                self.__jäljellä += 1
            self.__jäljellälabel.configure(text=self.__jäljellä)
        elif self.__buttonit[x][y].configure("text")[-1] == "":
            self.avaa(x,y)

    def avaa(self, x, y):
        """ Avaa painetun nappulan ja määrittää sille numeron tai lopettaa
        pelin riippuen oliko nappulan alla miina vaiko ei.

        :param x, y: Painetun nappulan koordinaatit.
        """

        # Avatessa miina lukitetaan kaikki pelin nappulat ja näytetään
        # miinojen paikat.
        if self.__lauta[x][y] == "X":
            self.__buttonit[x][y].configure(image=self.__miinakuva,
                                            height=24, width=22,
                                            relief=SUNKEN, bg="#FF4040")
            for sarake in self.__buttonit:
                for button in sarake:
                    button.configure(state=DISABLED)
            for i in range(len(self.__buttonit)):
                for j in range(len(self.__buttonit[0])):
                    if self.__lauta[i][j] == "X":
                        if self.__buttonit[i][j].configure("text")[-1] == "  ":
                            pass
                        elif self.__buttonit[i][j].configure(
                                "bg")[-1] != "#FF4040":
                            self.__buttonit[i][j].configure(image=
                                                            self.__miinakuva,
                                                            height=24,
                                                            width=22,
                                                            relief=SUNKEN,
                                                            bg="lightgray")
                    elif self.__lauta[i][j] == "O" \
                            and self.__buttonit[i][j].configure(
                                "text")[-1] == "  ":
                        self.__buttonit[i][j].configure(text="X",
                                                        compound=CENTER)
            self.__avaabutton.configure(state=DISABLED)
            self.__lippubutton.configure(state=DISABLED)
        else:
            numero = self.laskenumero(x,y)
            if numero == 0:
                self.__buttonit[x][y].configure(text=" ", relief=SUNKEN)
                self.painallus(x,y)
            else:
                self.__buttonit[x][y].configure(text=str(numero),
                                                relief=SUNKEN)
                if numero == 1:
                    self.__buttonit[x][y].configure(fg="blue")
                elif numero == 2:
                    self.__buttonit[x][y].configure(fg="dark green")
                elif numero == 3:
                    self.__buttonit[x][y].configure(fg="red")
                elif numero == 4:
                    self.__buttonit[x][y].configure(fg="dark blue")
                elif numero == 5:
                    self.__buttonit[x][y].configure(fg="brown")
                elif numero == 6:
                    self.__buttonit[x][y].configure(fg="cyan")
                elif numero == 7:
                    self.__buttonit[x][y].configure(fg="black")
                elif numero == 8:
                    self.__buttonit[x][y].configure(fg="grey")
                else:
                    self.__buttonit[x][y].configure(fg="black")

    def lippu(self):
        """ Vaihtaa avaamisen ja liputtamisen välillä. """

        if self.__lippu is False:
            self.__lippu = True
            self.__avaabutton.configure(bg=self.__ikkuna.cget("bg"),
                                        relief=RAISED, state=NORMAL)
            self.__lippubutton.configure(bg="tan",
                                         relief=SUNKEN, state=DISABLED)
        else:
            self.__lippu = False
            self.__avaabutton.configure(bg="tan",
                                        relief=SUNKEN, state=DISABLED)
            self.__lippubutton.configure(bg=self.__ikkuna.cget("bg"),
                                         relief=RAISED, state=NORMAL)

    def uusi(self):
        """ Uuden pelin alkaessa asettaa kaikki asetukset aloitusvalmiiksi. """

        self.__jäljellä = self.__miinoja
        self.__jäljellälabel.configure(text=self.__jäljellä)
        self.__lippu = False
        self.__avaabutton.configure(state=DISABLED, relief=SUNKEN, bg="tan")
        self.__lippubutton.configure(state=NORMAL, relief=RAISED,
                                     bg=self.__ikkuna.cget("bg"), fg="black")
        self.__lippubutton.configure(command="")
        for sarake in self.__buttonit:
            for button in sarake:
                button.configure(text="",
                                 height=1, width=2,
                                 image="",
                                 compound=NONE,
                                 relief=RAISED,
                                 state=NORMAL,
                                 bg=self.__ikkuna.cget("bg"),
                                 fg="black",
                                 command=lambda
                                    x=self.__buttonit.index(sarake),
                                    y=sarake.index(button): self.aloitus(x, y))

    def valikko(self):
        """ Tuhoaa ikkunan ja avaa valikon. """

        self.__ikkuna.destroy()
        Valintaikkuna()

    def laskemerkatut(self, x, y):
        """ Laskee montako merkattua ruutua tietyn ruudun ympärilä on.

        :param x, y: Painetun nappulan koordinaatit.
        :return: Palauttaa lasketun numeron.
        """

        numero = 0
        if x+2 <= len(self.__buttonit) and y+2 <= len(self.__buttonit[0]):
            if self.__buttonit[x+1][y+1].configure("text")[-1] == "  ":
                numero += 1
        if x+2 <= len(self.__buttonit):
            if self.__buttonit[x+1][y].configure("text")[-1] == "  ":
                numero += 1
        if y+2 <= len(self.__buttonit[0]):
            if self.__buttonit[x][y+1].configure("text")[-1] == "  ":
                numero += 1
        if x-1 >= 0 and y-1 >= 0:
            if self.__buttonit[x-1][y-1].configure("text")[-1] == "  ":
                numero += 1
        if x-1 >= 0:
            if self.__buttonit[x-1][y].configure("text")[-1] == "  ":
                numero += 1
        if y-1 >= 0:
            if self.__buttonit[x][y-1].configure("text")[-1] == "  ":
                numero += 1
        if x+2 <= len(self.__lauta) and y-1 >= 0:
            if self.__buttonit[x+1][y-1].configure("text")[-1] == "  ":
                numero += 1
        if x-1 >= 0 and y+2 <= len(self.__lauta[0]):
            if self.__buttonit[x-1][y+1].configure("text")[-1] == "  ":
                numero += 1
        return numero

    def laskenumero(self, x, y):
        """ Laskee montako miinaa tietyn ruudun ympärillä on.

        :param x, y: Painetun nappulan koordinaatit.
        :return: Palauttaa lasketun numeron.
        """

        numero = 0
        if x+2 <= len(self.__lauta) and y+2 <= len(self.__lauta[0]):
            if self.__lauta[x+1][y+1] == "X":
                numero += 1
        if x+2 <= len(self.__lauta):
            if self.__lauta[x+1][y] == "X":
                numero += 1
        if y+2 <= len(self.__lauta[0]):
            if self.__lauta[x][y+1] == "X":
                numero += 1
        if x-1 >= 0 and y-1 >= 0:
            if self.__lauta[x-1][y-1] == "X":
                numero += 1
        if x-1 >= 0:
            if self.__lauta[x-1][y] == "X":
                numero += 1
        if y-1 >= 0:
            if self.__lauta[x][y-1] == "X":
                numero += 1
        if x+2 <= len(self.__lauta) and y-1 >= 0:
            if self.__lauta[x+1][y-1] == "X":
                numero += 1
        if x-1 >= 0 and y+2 <= len(self.__lauta[0]):
            if self.__lauta[x-1][y+1] == "X":
                numero += 1
        return numero


    def luolauta(self, x, y):
        """ Luo miinaharavan pelilaudan ja arpoo sille miinoja,
        poislukien aloituspainalluksen ympäristön.

        :param x, y: Painetun nappulan koordinaatit.
        :return: Palauttaa valmiin pelilaudan.
        """

        l, k, m = self.__tiedot
        lauta = [["O" for i in range(k)]for j in range(l)]
        for i in range(m):
            while True:
                mx = random.randint(0, l-1)
                my = random.randint(0, k-1)
                if lauta[mx][my] == "O"\
                        and ((mx > x+1 or mx < x-1) or (my > y+1 or my < y-1)):
                    lauta[mx][my] = "X"
                    break
        return lauta


def main():
    Valintaikkuna()

main()
