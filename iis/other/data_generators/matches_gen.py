#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import itertools
import random

data = []

dates = ['2017-10-22', '2017-11-11', '2017-11-26', '2017-12-16', '2018-1-7',
         '2018-1-13', '2018-1-28', '2018-2-4', '2018-2-18']

times = ['8:00:00', '9:00:00', '10:00:00', '11:00:00', '12:00:00',
         '13:00:00', '14:00:00', '15:00:00', '16:00:00', '17:00:00']

matches_p1 = [i for i in itertools.combinations(range(1, 11), 2)]
matches_p2 = [i for i in itertools.combinations(range(10, 0, -1), 2)]
print(matches_p1)
print(matches_p2)
random.shuffle(matches_p1)
random.shuffle(matches_p2)
print(matches_p1)
print(matches_p2)
matches = matches_p1 + matches_p2
random.shuffle(matches)
print(matches)

date_cnt = 0
rnd_cnt = 1
for i in range(90):
    match = dict()
    match['model'] = 'browser.match'
    match['pk'] = i+1

    fields = dict()
    fields['number'] = i+1

    if i % 10 == 0 and i != 0:
        date_cnt += 1
        rnd_cnt += 1

    fields['date_time'] = dates[date_cnt%9] + 'T' + times[i%10] + 'Z'
    fields['home_team'] = matches[i-1][0]
    fields['away_team'] = matches[i-1][1]
    fields['round'] = rnd_cnt
    fields['home_team_players'] = []
    fields['away_team_players'] = []
    match['fields'] = fields
    data.append(match)


with open('matches_generated.json', 'w') as outfile:
    json.dump(data, outfile)
