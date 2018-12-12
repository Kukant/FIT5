#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json


dates = ['2018-3-4']

times = ['8:00:00', '9:00:00', '10:00:00']

data = []

for i in range(98, 101):
    match = dict()
    match['model'] = 'browser.match'
    match['pk'] = i + 1

    fields = dict()
    fields['number'] = i + 1

    fields['date_time'] = dates[0] + 'T' + times[i-98] + 'Z'

    fields['home_team'] = ''
    fields['away_team'] = ''

    fields['round'] = 10
    fields['home_team_players'] = []
    fields['away_team_players'] = []
    match['fields'] = fields
    data.append(match)

with open('../matches_2.json', 'w') as outfile:
    json.dump(data, outfile)
