set terminal png

set key
set output "number.png"
plot [0:1490] 'n' u 1 w l t 'Number of units', 'n' u 2 w l t 'Number of edges'

unset key
set size square
set grid

do for[i=0:149]{
DATA = sprintf( "%03d0", i )
set output sprintf( "%03d0.png", i )
set label 1 sprintf( "Updated %03d0 steps", i ) at 6, 1
plot [0:10][0:10] 'src' w p lc 7, DATA w lp lc 3
}
