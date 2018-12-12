#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import random

with open('../matches_2.json') as f:
    matches = json.load(f)

with open('../players.json') as f:
    players = json.load(f)

players_1 = []
players_2 = []
players_3 = []
players_4 = []
players_5 = []
players_6 = []
players_7 = []
players_8 = []
players_9 = []
players_10 = []

for player in players:
    if player['fields']['team_season'][0] == 1:
        players_1.append(player['pk'])
    if player['fields']['team_season'][0] == 2:
        players_2.append(player['pk'])
    if player['fields']['team_season'][0] == 3:
        players_3.append(player['pk'])
    if player['fields']['team_season'][0] == 4:
        players_4.append(player['pk'])
    if player['fields']['team_season'][0] == 5:
        players_5.append(player['pk'])
    if player['fields']['team_season'][0] == 6:
        players_6.append(player['pk'])
    if player['fields']['team_season'][0] == 7:
        players_7.append(player['pk'])
    if player['fields']['team_season'][0] == 8:
        players_8.append(player['pk'])
    if player['fields']['team_season'][0] == 9:
        players_9.append(player['pk'])
    if player['fields']['team_season'][0] == 10:
        players_10.append(player['pk'])


new_matches = []

for match in matches:
    if match['fields']['home_team'] == 1:
        match['fields']['home_team_players'] = (random.sample(players_1, len(players_1) - random.randint(0,3)))
    if match['fields']['home_team'] == 2:
        match['fields']['home_team_players'] = (random.sample(players_2, len(players_2) - random.randint(0,3)))
    if match['fields']['home_team'] == 3:
        match['fields']['home_team_players'] = (random.sample(players_3, len(players_3) - random.randint(0,3)))
    if match['fields']['home_team'] == 4:
        match['fields']['home_team_players'] = (random.sample(players_4, len(players_4) - random.randint(0,3)))
    if match['fields']['home_team'] == 5:
        match['fields']['home_team_players'] = (random.sample(players_5, len(players_5) - random.randint(0,3)))
    if match['fields']['home_team'] == 6:
        match['fields']['home_team_players'] = (random.sample(players_6, len(players_6) - random.randint(0,3)))
    if match['fields']['home_team'] == 7:
        match['fields']['home_team_players'] = (random.sample(players_7, len(players_7) - random.randint(0,3)))
    if match['fields']['home_team'] == 8:
        match['fields']['home_team_players'] = (random.sample(players_8, len(players_8) - random.randint(0,3)))
    if match['fields']['home_team'] == 9:
        match['fields']['home_team_players'] = (random.sample(players_9, len(players_9) - random.randint(0,3)))
    if match['fields']['home_team'] == 10:
        match['fields']['home_team_players'] = (random.sample(players_10, len(players_10) - random.randint(0,3)))

    if match['fields']['away_team'] == 1:
        match['fields']['away_team_players'] = (random.sample(players_1, len(players_1) - random.randint(0,3)))
    if match['fields']['away_team'] == 2:
        match['fields']['away_team_players'] = (random.sample(players_2, len(players_2) - random.randint(0,3)))
    if match['fields']['away_team'] == 3:
        match['fields']['away_team_players'] = (random.sample(players_3, len(players_3) - random.randint(0,3)))
    if match['fields']['away_team'] == 4:
        match['fields']['away_team_players'] = (random.sample(players_4, len(players_4) - random.randint(0,3)))
    if match['fields']['away_team'] == 5:
        match['fields']['away_team_players'] = (random.sample(players_5, len(players_5) - random.randint(0,3)))
    if match['fields']['away_team'] == 6:
        match['fields']['away_team_players'] = (random.sample(players_6, len(players_6) - random.randint(0,3)))
    if match['fields']['away_team'] == 7:
        match['fields']['away_team_players'] = (random.sample(players_7, len(players_7) - random.randint(0,3)))
    if match['fields']['away_team'] == 8:
        match['fields']['away_team_players'] = (random.sample(players_8, len(players_8) - random.randint(0,3)))
    if match['fields']['away_team'] == 9:
        match['fields']['away_team_players'] = (random.sample(players_9, len(players_9) - random.randint(0,3)))
    if match['fields']['away_team'] == 10:
        match['fields']['away_team_players'] = (random.sample(players_10, len(players_10) - random.randint(0,3)))

    new_matches.append(match)


with open('../matches_2_with_players.json', 'w') as outfile:
    json.dump(new_matches, outfile)
