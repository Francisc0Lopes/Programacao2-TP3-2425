#!/bin/bash
# filepath: ensaio.sh

# Defina os nomes dos executáveis e ficheiros de teste
EXECUTAVEIS=("prog22" "prog33" "prog34")
TEXTOS="texto1 texto2 texto3"
PALAVRAS_VAZIO="palavras_vazio.txt"
PALAVRAS_EXTENSO="palavras_extenso.txt"

echo "== Ensaio comparativo de desempenho =="

for exe in "${EXECUTAVEIS[@]}"; do
    echo "---- $exe: índice + pesquisa (palavras vazio) ----"
    /usr/bin/time -f "$exe vazio: %e s" ./$exe $TEXTOS < $PALAVRAS_VAZIO > resultados_${exe}_vazio.txt

    echo "---- $exe: índice + pesquisa (palavras extenso) ----"
    /usr/bin/time -f "$exe extenso: %e s" ./$exe $TEXTOS < $PALAVRAS_EXTENSO > resultados_${exe}_extenso.txt
done