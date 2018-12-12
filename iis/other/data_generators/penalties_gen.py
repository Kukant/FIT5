#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import random
import datetime

with open('../matches.json') as f:
    matches = json.load(f)

data = []

pen_len = [2,2,2,2,2,2,2,2,2,5]
random.shuffle(pen_len)

for i in range(200):
    penalty = dict()
    penalty['model'] = 'browser.penalty'
    penalty['pk'] = i+1

    fields = dict()
    fields['length'] = random.sample(pen_len, 1)[0]

    min = random.randint(0, 39)
    sec = random.randint(0, 59)
    time = datetime.time(0, min, sec)

    fields['time'] = str(time)
    fields['match'] = random.randint(1, 90)

    for match in matches:
        if match['pk'] == fields['match']:
            players = match['fields']['home_team_players'] + match['fields']['away_team_players']
            fields['player'] = random.sample(players, 1)[0]

    penalty['fields'] = fields

    data.append(penalty)

with open('../penalties_generated.json', 'w') as outfile:
    json.dump(data, outfile)
