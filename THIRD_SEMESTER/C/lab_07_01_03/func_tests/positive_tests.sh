#!/bin/bash
../app.exe $(cat pos_"$1"_args.txt) > out.txt
rc=$?

diff pos_out.txt pos_"$1"_out.txt
rc_f=$?

if [ $rc = 0 ] && [ $rc_f = 0 ]
then
  echo -e POSITIVE_"$1": "\e[32mPASSED\e[0m rc == $rc"
else
  diff pos_out.txt pos_"$1"_out.txt > comparison_output.txt
  echo -e POSITIVE_"$1": "\e[31mFAILED\e[0m rc == $rc"
fi

rm out.txt

