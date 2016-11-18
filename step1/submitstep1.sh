#!/bin/bash

date

echo 'NOMINAL'
python -u makeStep1condor.py nominal

sleep 5

echo "JECUP"
python -u makeStep1condor.py JECup

sleep 5

echo "JECDOWN"
python -u makeStep1condor.py JECdown

sleep 5

echo "JERUP"
python -u makeStep1condor.py JERup

sleep 5

echo "JERDOWN"
python -u makeStep1condor.py JERdown

echo "DONE"

date
