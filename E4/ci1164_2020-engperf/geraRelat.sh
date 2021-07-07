#!/bin/bash
# =========================================== #
#                                             #
#            Exercício 04 - LIKWID            #
#                                             #
#               Jorge Jabczenski              #
#                    jlvj19                   #
#                  GRR20190372                #
#                    06/7/21                  #
#                                             #
# =========================================== #
#
# Grupos:
# - L3 -------> "Memory bandwidth [MBytes/s]"
# - L2CACHE --> "data cache miss ratio"
# - FLOPS_DP -> reportar FLOPS_DP e FLOPS_AVX 
#               como duas colunas separadas na mesma tabela, em "MFLOP/s"
#
# Parâmetros de Tamanho:
# -   64
# -  100
# -  128
# - 2048
#  
# 
# [x] Incluir as tags do LIKWID em matmult.c 
# [x] Incluir as flags no Makefile           
# [ ] Para cada grupo, rodar com os 4 tamanhos e gerar uma tabela
# [ ] 
# 
# 
# ============================================== #
#                    Variáveis                   #
# ============================================== #

TAMANHO=(64 100 128 2048)
GRUPO=(L3 L2CACHE FLOPS_DP)
FUNCS=(multMatPtrVet multMatRowVet multMatMatPtr multMatMatRow)

# ============================================== #
#               Relatórios Gerais                #
# ============================================== #

for I in "${TAMANHO[@]}"
do
    for G in "${GRUPO[@]}"
    do
        echo $I-$G 
        likwid-perfctr -C 3 -g $G -m ./matmult -n $I > Resultados/$G-$I.out
    done
done

# ============================================== #
#             Relatórios por FUNÇÃO              #
# ============================================== #

# for F in "${FUNCS[@]}"
# do
#     for G in "${GRUPO[@]}"
#     do
#         for FILE in Resultados/$G-*.out
#         do
#             cat
#         done 
#     done
# done