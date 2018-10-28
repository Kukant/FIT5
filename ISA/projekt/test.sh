#!/usr/bin/env bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

assert ()
{

  if [ ! $1 -eq $2 ]
  then
    printf "${RED}Assertion failed:  \"$1 == $2\" ${NC}\n"
  else
    printf "${GREEN}OK${NC}\n"
  fi
}

URL='http://www.fit.vutbr.cz/news/news-rss.php'
FEEDFILE='xkukan00__feedfile.txt'

echo "${URL}" > ${FEEDFILE}

echo "Wrong parameters:"
./feedreader -sla -blap > /dev/null 2>&1
assert $? 1

echo "Missing URL or feedfile:"
./feedreader -T -u > /dev/null 2>&1
assert $? 1

echo "With URL:"
./feedreader ${URL} > /dev/null 2>&1
assert $? 0

echo "With feedfile:"
./feedreader -f ${FEEDFILE} > /dev/null 2>&1
assert $? 0

echo "With URL, author, time, URL:"
./feedreader ${URL} -u -T -a > /dev/null 2>&1
assert $? 0

echo "With feedfile, author, time, URL:"
./feedreader -f ${FEEDFILE} -u -T -a > /dev/null 2>&1
assert $? 0


rm ${FEEDFILE}