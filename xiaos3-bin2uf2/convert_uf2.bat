@echo off
set /p file=Please enter the name of the bin file to be converted:
python fw\uf2conv.py -b 0x00 %file%.bin -f ESP32S3 -c -o %file%.uf2