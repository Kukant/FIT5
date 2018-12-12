#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import itertools
import random

dates = ['2018-10-13', '2018-10-28', '2018-11-10', '2018-11-25', '2018-12-11']

times = ['8:00:00', '9:00:00', '10:00:00', '11:00:00', '12:00:00', '13:00:00',
         '14:00:00', '15:00:00', '16:00:00', '17:00:00', '18:00:00', '19:00:00']

matches_p1_lst = [1,2,3,4,5,7,9,10,11,12,13,14]
matches_p2_lst = [1,2,3,4,5,7,9,10,11,12,13,14]
matches_p2_lst.reverse()
matches_p1 = [i for i in itertools.combinations(matches_p1_lst, 2)]
matches_p2 = [i for i in itertools.combinations(matches_p2_lst, 2)]
random.shuffle(matches_p1)
random.shuffle(matches_p2)
matches = matches_p1 + matches_p2
random.shuffle(matches)

data = list()
date_cnt = 0
rnd_cnt = 13
for i in range(60):
    match = dict()
    match['model'] = 'browser.match'
    match['pk'] = 108+i+1

    fields = dict()
    fields['number'] = i+1

    if i % 12 == 0 and i != 0:
        date_cnt += 1
        rnd_cnt += 1

    fields['date_time'] = dates[date_cnt%5] + 'T' + times[i%12] + 'Z'
    fields['home_team'] = matches[i-1][0]
    fields['away_team'] = matches[i-1][1]
    fields['round'] = rnd_cnt
    fields['home_team_players'] = []
    fields['away_team_players'] = []
    match['fields'] = fields
    data.append(match)

with open('../matches_2018.json', 'w') as outfile:
    json.dump(data, outfile)
