set size square
unset key
set terminal eps

set output "src1.eps"
plot [-2:12][-2:12] 'src_u'
set output "src2.eps"
plot [-2:12][-2:12] 'src_ux'
set output "src3.eps"
plot [-2:12][-2:12] 'src_n'

set output "k1.eps"
plot [-2:12][-2:12] 'k1_0','k1_1','k1_2','k1_3','k1_4','k1_5'
set output "k2.eps"
plot [-2:12][-2:12] 'k2_0','k2_1','k2_2','k2_3','k2_4'
set output "k3.eps"
plot [-2:12][-2:12] 'k3_0','k3_1','k3_2','k3_3','k3_4','k3_5'

set output "x1.eps"
plot [-2:12][-2:12] 'x1_0','x1_1','x1_2','x1_3'
set output "x2.eps"
plot [-2:12][-2:12] 'x2_0'
set output "x3.eps"
plot [-2:12][-2:12] 'x3_0','x3_1','x3_2','x3_3','x3_4','x3_5','x3_6','x3_7','x3_8','x3_9','x3_10','x3_11','x3_12','x3_13','x3_14','x3_15','x3_16','x3_17','x3_18'

set output "xb1.eps"
plot [-2:12][-2:12] 'xb1_0'
set output "xb2.eps"
plot [-2:12][-2:12] 'xb2_0', 'xb2_1'
set output "xb3.eps"
plot [-2:12][-2:12] 'xb3_0', 'xb3_1', 'xb3_2'

set output "gmm1_bic.eps"
plot 'gmm1_bic' u 1:2 w lp, 'gmm1_bic' u 1:3 w lp
set output "gmm2_bic.eps"
plot 'gmm2_bic' u 1:2 w lp, 'gmm2_bic' u 1:3 w lp
set output "gmm3_bic.eps"
plot 'gmm3_bic' u 1:2 w lp, 'gmm3_bic' u 1:3 w lp

set output "gmm1.eps"
load 'gmm1_6'
set output "gmm2.eps"
load 'gmm2_6'
set output "gmm3.eps"
load 'gmm3_6'
