#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import random

# 120 random czech names
full_names_str = '''Roman Půta
Josef Kynčl
Miroslav Bednarski
Luboš Brádle
Miloš Tauš
Zdeněk Kajš
Milan Preisler
Jan Hranáč
Karel Voznička
Jiří Bogdan
Michal Šlosárek
Martin Kuchař
Mirko Novotný
Tomáš Dovala
Petr Nikrmajer
Kamil Hornych
Pavel Vondřich
Jaroslav Kirschner
Rudolf Škopek
Bohumil Paukert
David Buriánek
František Vacek
Eduard Drábek
Aleš Vodička
Dalibor Peřina
Patrik Boček
Oldřich Havlíček
Vladan Bezecný
Zbyněk Pouzar
Luděk Pazdera
Václav Rous
Vladimír Raisigl
Jakub Kaplánek
Zdenek Plucha
Miloslav Vedral
Lukáš Najvar
Vojtěch Majer
Ladislav Urban
Daniel Šůstek
Matěj Navrátil
Radek Ridzák
Filip Hrabánek
Svyatoslav Čarný
Stanislav März
Marek Vladík
René Schejbal
Drahoslav Matýs
Ondřej Janáč
Adam Veselý
Vladislav Švaříček
Hubert Aberle
Antonín Houška
Marcel Šulc
Jaromír Fabík
Ivan Neumann
Dominik Šádek
Günter Kvapil
Rostislav Vajda
Jindřich Šmarda
Oto Takáč
Radim Vraštil
Lien Urbánek
Vítek Varmuža
Ivo Štercl
Imrich Eder
Dušan Mai Van
Alexander Dovolil
Alois Bernad
Libor Štibich
Denis Novák
Lubomír Bříza
Viktor Souček
Vítězslav Dvořák
Štěpán Kolář
Vasyl Babka
Vlastimil Měsíček
Tibor Pospěch
Robert Strapko
Vladimir Stavěla
Evžen Doležal
Otokar Postl
Róbert Beránek
Djemailj Franc
Ludvík Reiter
Mariano Lokajíček
Eric Holek
Mykhaylo Doktor
Ota Trávníček
Vít Trajkovski
Arnošt Čvančara
Richard Růžička
Květoslav Košan
Bohuslav Linek
Bohumír Trtík
Emil Dargaj
Ján Pavelka
Otakar Krumel
Ľubomír Krupička
Štefan Matuszek
Marian Hojka
Eva Průchová
Helena Kroupová
Jitka Porcalová
Jana Skopalová
Šárka Zarabská
Lucie Vavřičková
Milada Ondrová
Aneta Pivoňková
Martina Turečková
Marta Pekárková
Petra Spurná
Miluše Susová
Marie Marková
Markéta Kalíšková
Patricie Grimmová
Anna Doležalová
Andrea Šafářová
Františka Roubalová
Michaela Kučerová
Pavla Ungrová'''

full_names_lst = full_names_str.splitlines()
random.shuffle(full_names_lst)

full_names = [name.split() for name in full_names_lst]

birth_dates_str = '''1984-03-03
1993-01-28
1998-10-21
1993-06-08
1988-10-15
1991-11-15
1999-07-01
1992-06-28
1994-01-11
1991-10-24
1995-05-14
1985-06-11
1989-04-04
1996-12-08
1984-03-16
2000-03-31
1997-09-26
1986-06-17
2000-10-02
1985-02-02
1990-02-14
1996-08-23
1992-02-02
1985-11-06
1997-04-09
1994-10-01
1995-02-20
1984-11-26
1999-08-24
1993-06-23
1985-02-11
1996-07-31
1999-05-06
1997-04-24
1985-01-27
1991-06-23
1985-05-30
1987-07-28
1999-03-30
1991-08-01
1993-11-16
1994-06-03
2001-02-09
1995-03-05
1992-08-17
1993-02-21
1986-06-07
1999-10-11
1987-03-11
1994-03-22
1986-03-08
1986-06-13
1999-10-03
2001-09-22
1998-11-27
1987-09-09
1986-01-15
1999-09-26
1989-04-27
1986-12-26
1996-10-16
1989-08-24
1994-08-19
1991-01-25
1999-06-08
1985-04-16
1993-12-20
1988-03-13
1998-05-05
2000-03-19
1993-09-16
1984-12-04
1997-11-01
1990-07-18
1999-10-24
1991-10-24
1992-02-15
1991-04-02
1996-07-17
1989-01-06
1995-12-31
1996-09-07
1996-02-01
1989-06-08
1989-01-06
1989-09-03
2001-04-30
1992-04-14
1993-03-22
2000-01-29
1988-05-01
2001-06-30
1983-07-11
1985-10-11
1999-12-18
1995-04-30
1995-10-14
1990-04-09
1998-06-23
1999-04-21
1999-05-12
1984-02-01
1983-06-19
1990-10-29
1996-10-04
1993-06-16
1993-02-22
1994-12-21
1998-12-24
1985-11-04
1989-02-12
1995-01-21
1989-01-22
1985-12-08
1997-12-24
1986-09-26
1994-12-01
2000-03-05
1986-10-04
1983-11-24
'''
birth_dates = birth_dates_str.splitlines()
random.shuffle(birth_dates)

data = list()

for i in range(120):
    player = dict()
    player['model'] = 'browser.Player'
    player['pk'] = i + 1

    fields = dict()
    fields['first_name'] = full_names[i][0]
    fields['last_name'] = full_names[i][1]
    fields['birth_date'] = birth_dates[i]
    fields['dress_number'] = random.randint(1, 100)

    if i < 10:
        fields['position'] = 'G'
        fields['team_season'] = [i+1]
    elif i < 50:
        fields['position'] = 'D'
        fields['team_season'] = [(i%10)+1]
    else:
        fields['position'] = 'A'
        fields['team_season'] = [(i%10)+1]

    player['fields'] = fields
    data.append(player)

with open('../players_generated.json', 'w') as outfile:
    json.dump(data, outfile)
