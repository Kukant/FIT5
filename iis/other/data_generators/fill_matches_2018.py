#!/home/vdusek/Dropbox/iis-itu/env/bin/python

import json
import random

with open('../matches_2018_played.json') as f:
    matches = json.load(f)

with open('../players.json') as f:
    players = json.load(f)

players_1 = []
players_2 = []
players_3 = []
players_4 = []
players_5 = []
players_7 = []
players_9 = []
players_10 = []
players_11 = []
players_12 = []
players_13 = []
players_14 = []

for player in players:
    if 11 in player['fields']['team_season']:
        players_1.append(player['pk'])
    if 12 in player['fields']['team_season']:
        players_2.append(player['pk'])
    if 13 in player['fields']['team_season']:
        players_3.append(player['pk'])
    if 14 in player['fields']['team_season']:
        players_4.append(player['pk'])
    if 15 in player['fields']['team_season']:
        players_5.append(player['pk'])
    if 16 in player['fields']['team_season']:
        players_7.append(player['pk'])
    if 17 in player['fields']['team_season']:
        players_9.append(player['pk'])
    if 18 in player['fields']['team_season']:
        players_10.append(player['pk'])
    if 19 in player['fields']['team_season']:
        players_11.append(player['pk'])
    if 20 in player['fields']['team_season']:
        players_12.append(player['pk'])
    if 21 in player['fields']['team_season']:
        players_13.append(player['pk'])
    if 22 in player['fields']['team_season']:
        players_14.append(player['pk'])

new_matches = []

for match in matches:
    if match['fields']['home_team'] == 1:
        match['fields']['home_team_players'] = (random.sample(players_1, len(players_1) - random.randint(0, 3)))
    if match['fields']['home_team'] == 2:
        match['fields']['home_team_players'] = (random.sample(players_2, len(players_2) - random.randint(0, 3)))
    if match['fields']['home_team'] == 3:
        match['fields']['home_team_players'] = (random.sample(players_3, len(players_3) - random.randint(0, 3)))
    if match['fields']['home_team'] == 4:
        match['fields']['home_team_players'] = (random.sample(players_4, len(players_4) - random.randint(0, 3)))
    if match['fields']['home_team'] == 5:
        match['fields']['home_team_players'] = (random.sample(players_5, len(players_5) - random.randint(0, 3)))
    if match['fields']['home_team'] == 7:
        match['fields']['home_team_players'] = (random.sample(players_7, len(players_7) - random.randint(0, 3)))
    if match['fields']['home_team'] == 9:
        match['fields']['home_team_players'] = (random.sample(players_9, len(players_9) - random.randint(0, 3)))
    if match['fields']['home_team'] == 10:
        match['fields']['home_team_players'] = (random.sample(players_10, len(players_10) - random.randint(0, 3)))
    if match['fields']['home_team'] == 11:
        match['fields']['home_team_players'] = (random.sample(players_11, len(players_11) - random.randint(0, 3)))
    if match['fields']['home_team'] == 12:
        match['fields']['home_team_players'] = (random.sample(players_12, len(players_12) - random.randint(0, 3)))
    if match['fields']['home_team'] == 13:
        match['fields']['home_team_players'] = (random.sample(players_13, len(players_13) - random.randint(0, 3)))
    if match['fields']['home_team'] == 14:
        match['fields']['home_team_players'] = (random.sample(players_14, len(players_14) - random.randint(0, 3)))

    if match['fields']['away_team'] == 1:
        match['fields']['away_team_players'] = (random.sample(players_1, len(players_1) - random.randint(0, 3)))
    if match['fields']['away_team'] == 2:
        match['fields']['away_team_players'] = (random.sample(players_2, len(players_2) - random.randint(0, 3)))
    if match['fields']['away_team'] == 3:
        match['fields']['away_team_players'] = (random.sample(players_3, len(players_3) - random.randint(0, 3)))
    if match['fields']['away_team'] == 4:
        match['fields']['away_team_players'] = (random.sample(players_4, len(players_4) - random.randint(0, 3)))
    if match['fields']['away_team'] == 5:
        match['fields']['away_team_players'] = (random.sample(players_5, len(players_5) - random.randint(0, 3)))
    if match['fields']['away_team'] == 7:
        match['fields']['away_team_players'] = (random.sample(players_7, len(players_7) - random.randint(0, 3)))
    if match['fields']['away_team'] == 9:
        match['fields']['away_team_players'] = (random.sample(players_9, len(players_9) - random.randint(0, 3)))
    if match['fields']['away_team'] == 10:
        match['fields']['away_team_players'] = (random.sample(players_10, len(players_10) - random.randint(0, 3)))
    if match['fields']['away_team'] == 11:
        match['fields']['away_team_players'] = (random.sample(players_11, len(players_11) - random.randint(0, 3)))
    if match['fields']['away_team'] == 12:
        match['fields']['away_team_players'] = (random.sample(players_12, len(players_12) - random.randint(0, 3)))
    if match['fields']['away_team'] == 13:
        match['fields']['away_team_players'] = (random.sample(players_13, len(players_13) - random.randint(0, 3)))
    if match['fields']['away_team'] == 14:
        match['fields']['away_team_players'] = (random.sample(players_14, len(players_14) - random.randint(0, 3)))

    new_matches.append(match)


with open('../matches_2018_with_players.json', 'w') as outfile:
    json.dump(new_matches, outfile)

