#!/bin/sh

rm -f *.png

for n in `seq 1 7`
do
    name=algorithm${n}
    platex ${name}.tex
    platex ${name}.tex
    dvips -E ${name}.dvi
    epstopdf ${name}.ps ${name}.pdf
    pdftoppm -png ${name}.pdf > ${name}.png
    rm ${name}.ps ${name}.pdf
done

ls fig/*.svg | xargs -i inkscape --export-type=png -D -b white {}
ls fig/*.svg | xargs -i inkscape --export-type=eps -D {}
