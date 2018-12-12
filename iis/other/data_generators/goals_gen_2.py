#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import random
import datetime

with open('../matches_2.json') as f:
    matches = json.load(f)

data = []

for i in range(25):
    goal = dict()
    goal['model'] = 'browser.goal'
    goal['pk'] = 450+i+1

    fields = dict()

    min = random.randint(0, 39)
    sec = random.randint(0, 59)
    time = datetime.time(0, min, sec)

    fields['time'] = str(time)
    fields['match'] = random.randint(90, 98)

    for match in matches:
        if match['pk'] == fields['match']:
            home_team = match['fields']['home_team']
            away_team = match['fields']['away_team']
            home_players = match['fields']['home_team_players']
            away_players = match['fields']['away_team_players']

            fields['collect_team'] = random.sample([home_team, away_team], 1)[0]
            if fields['collect_team'] == home_team:
                fields['score_team'] = away_team
                fields['assist_player'] = random.sample(away_players + [None], 1)[0]
                fields['score_player'] = random.sample(away_players, 1)[0]
            else:
                fields['score_team'] = home_team
                fields['assist_player'] = random.sample(away_players + [None], 1)[0]
                fields['score_player'] = random.sample(home_players, 1)[0]

    goal['fields'] = fields

    data.append(goal)

with open('../goals_2.json', 'w') as outfile:
    json.dump(data, outfile)
