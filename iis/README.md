# Informacni system OAFL

### Projekt do predmetu IIS a ITU  


## ToDo list:

### Vlada
- [ ] VPS
- [x] Napsat dokumentacni stranku
- [ ] Use case diagram (?)
- [x] Pripravit archiv pro odevzdani (komprese obrazku, smazat cache)
- [x] Vytvorit command pro naplneni databaze

### Kuky
- [x] Pri zmene sezony zustat na soucasne strance
- [ ] V hlavicce text "Orlicka Amaterska Florbalova Liga" vertikalne na stred
- [x] Stranka tymu: Odehrane sezony, Nejlepsi umisteni - pouze do soucasne, ne sezony celkove!
- [x] Tlacitko "Prihlaseni" presmeruje na "registrace-tymu/prihlaseni/" a "Registrace" na "registrace-tymu/registrace/"
- [x] Pri prihlaseni se tlacitka zmeni na "Jmeno uzivatele" (registrace-tymu/) a "Odhlasit"

### Dalsi ukoly
- [ ] V tabulkach (Tabulka, Statistiky) pridat moznost razeni podle hodnot v ruznych sloupcich. Napr. u hracu podle tresnych minut, u tymu podle vstrelenych golu, ...
- [ ] Clean URL pri pagingu (/1, /2, ...)
- [ ] Omezit mozne hodnoty casovych fieldu
    - Model Goal, Penalty : pouze minuty a vteriny, hodiny me nezajimaji
	- Model Match : pouze hodiny a minuty, vteriny me nezajimaji
- [ ] Udelat ze vsech entit krome Player, Team, Season weak
- [ ] Detail zapasu zahrnout do URL
- [ ] Na domovske strance, moznost zoomnout obrazky po kliknuti
- [ ] Sezony v dropdownu radit podle roku (ne podle pk)
- [ ] Optimalizovat vykon, porad nektere stranky nacitaji prilis dlouho
- [ ] Nastavit maximalni pocet hracu v tymu (17)
- [ ] Omezit mozne hodnoty FK/M2M fieldu, mozna pomoci validatoru
    - Model Goal
        - collect_team, score_team : pouze tymy ktere hraji zapas a ne ti sami
		- assist_player, score_player : pouze hraci kteri hraji zapas a ne ti sami
    - Model Penalty
		- player : pouze hrac ktery dany zapas
    - Model Match
		- home_team, away_team : pouze tymy ktere hraji sezonu ve ktere se hraje zapas
		- players : pouze z home_team nebo away_team
- [ ] Zmenil bych stranku tymu, respektive pridal dalsi informace. Napriklad vysledek v
sezone (je li odehrana), protoze toto zatim neni nikde zverejneno, celkove poradi!

## Manage project

**Make migrations**
```
$ python manage.py makemigrations
```

**Migrate**
```
$ python manage.py migrate
```

**Run server**
```
$ python manage.py runserver
```

**Create super user**
```
$ python manage.py createsuperuser
```

**Command for fill database**
```
$ python manage.py fill_db
```

**Command for clean database**
```
$ python manage.py clean_db
```

**Fill database with fixtures/data.json by fixture**
```
$ python manage.py loaddata data.json
```

**Dumpdata from database**
```
$ python manage.py dumpdata
```



## Requirements

### Virtual enviroment

#### Start
```
$ virtualenv env
```

#### Activate
```
$ source env/bin/activate
```

#### Deactivate
```
(env) $ deactivate
```

### Install dependencies
```
# pip install django
# pip install psycopg2
# dnf install postgresql-server
# dnf install postgresql-contrib
```

### Postgresql database

#### Database initialization
```
# postgresql-setup --initdb --unit postgresql
```

#### Configuration, set local connections as trust
```
# vim /var/lib/pgsql/data/pg_hba.conf
```
```
local   all             all                                     trust
host    all             all             127.0.0.1/32            trust
```

#### Start service
```
# systemctl start postgresql
```

#### Check service status
```
# systemctl status postgresql.service
```

#### Manage the database
```
$ psql -d postgres -U postgres
```

#### Drop database
```
$ dropdb -U postgres -W postgres
```

#### Create database
```
$ createdb
```

### Resources
- https://fedoraproject.org/wiki/PostgreSQL  
