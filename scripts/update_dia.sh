#!/bin/sh

git fetch --all
git checkout origin/master -- src/state.dia
git add -A
git commit -m "state.dia pulled for updated"