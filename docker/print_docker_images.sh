docker images |head -n 5 | tail -n 4| awk '{print "name :   " $1, "       tag :   " $2}'
