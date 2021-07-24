#!/usr/bin/gnuplot -c
set grid
set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
set xrange ["0":]
set xlabel  "N (bytes)"



# Gerando figura PNG
set terminal png
#----- tempo
set title   "Tempo de Execução"
set ylabel  "Tempo(s)"
set output "imagens/mrv_tempo.png"
plot 'mrv_tempo.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

set output "imagens/mmr_tempo.png"
plot 'mmr_tempo.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

#----- miss

set title   "L2CACHE"
set ylabel  "L2 Miss Ratio"
set output "imagens/mrv_miss.png"
plot 'mrv_miss.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

set output "imagens/mmr_miss.png"
plot 'mmr_miss.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

#----- bandwidth

set title   "L3 Bandwidth"
set ylabel  "MBytes/s"
set output "imagens/mrv_bandwidth.png"
plot 'mrv_bandwidth.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

set output "imagens/mmr_bandwidth.png"
plot 'mmr_bandwidth.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

#----- dp

set title   "DP"
set ylabel  "MFlops/s"
set output "imagens/mrv_dp.png"
plot 'mrv_dp.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

set output "imagens/mmr_dp.png"
plot 'mmr_dp.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

#----- avx

set title   "AVX DP"
set ylabel  "MFlops/s"
set output "imagens/mrv_avx.png"
plot 'mrv_avx.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output

set output "imagens/mmr_avx.png"
plot 'mmr_avx.dat' using 1:2 title "<sem otimização>" with linespoints, \
     '' using 1:3 title "<com otimização>" with linespoints
replot
unset output