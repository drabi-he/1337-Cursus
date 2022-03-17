#!/bin/sh
find .  \( -name '.*' -not \( -name ".git" \) -o -name "a.out" \)
git status
git add .
git status
git commit -m "1337 cursus"
git log
git push
