#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import random
import datetime

with open('../matches.json') as f:
    matches = json.load(f)

data = []

# {
#     "model": "browser.goal",
#     "pk": 1,
#     "fields": {
#         "time": "00:01:12",
#         "match": 1,
#         "assist_player": 4,
#         "score_player": 5,
#         "collect_team": 13,
#         "score_team": 1
#     }
# },

for i in range(450):
    goal = dict()
    goal['model'] = 'browser.goal'
    goal['pk'] = i+1

    fields = dict()

    min = random.randint(0, 39)
    sec = random.randint(0, 59)
    time = datetime.time(0, min, sec)

    fields['time'] = str(time)
    fields['match'] = random.randint(1, 90)

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

with open('../goals_generated.json', 'w') as outfile:
    json.dump(data, outfile)
