#!/usr/bin/env bash

# this will start the application server as daemon process
cd /home/kuky/iis/src && gunicorn oafl.wsgi  --bind 0.0.0.0:8000 --daemon