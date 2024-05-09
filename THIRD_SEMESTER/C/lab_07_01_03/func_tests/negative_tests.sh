#!/bin/bash
../app.exe `cat neg_$1_args.txt` > out.txt
rc=$?

diff out.txt neg_00_out.txt
rc_s=$?

if [ $rc_s = 0 ] && [ $rc != 0 ]
then
  echo -e NEGATIVE_"$1": "\e[32mPASSED\e[0m rc == $rc"
else
  diff out.txt neg_00_out.txt
  echo -e NEGATIVE_"$1": "\e[31mFAILED\e[0m rc == $rc"
fi

rm "out.txt"
rm -rf "neg_out.txt"
