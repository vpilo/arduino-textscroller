#!/bin/bash

ROWS=8
COLS=15

VALUES=(0 1 2 3 4 5 6 7 8 9 A B C D E F)
cur=0

# frames
while true
do
    # rows
    for row in $( seq 1 $ROWS )
    do
        # columns
        for col in $( seq 1 $COLS )
        do
            # colors
            for px in 0 1 2
            do
                echo -n "${VALUES[$cur]}${VALUES[$cur]}"
                rand=$(($RANDOM % 3))
                cur=$(( cur + $rand ))
                [ $cur -ge ${#VALUES[*]} ] && cur=0
            done
        done
    done

    # end of display
    echo
done
