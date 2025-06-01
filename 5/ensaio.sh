#!/bin/bash

# Caminhos para os executáveis a testar
EXECUTAVEIS=("../../SE2/2/prog22" "../3/prog33" "../4/prog34")

# Textos e ficheiros de palavras
TEXTOS="texto1.txt texto2.txt texto3.txt"
PALAVRAS_VAZIO="palavras_vazio.txt"
PALAVRAS_EXTENSO="palavras_extenso.txt"


echo "Textos usados: $TEXTOS"
echo "Palavras (vazio): $PALAVRAS_VAZIO"
echo "Palavras (extenso): $PALAVRAS_EXTENSO"
echo

for exe in "${EXECUTAVEIS[@]}"; do
    exe_name=$(basename "$exe")
    echo ">>> Testando '$exe_name'..."

    # Teste com ficheiro de palavras vazio
    echo -n "  - Pesquisa com ficheiro vazio:   "
    start=$(date +%s%N)
    "$exe" $TEXTOS < "$PALAVRAS_VAZIO" > "resultados_${exe_name}_vazio.txt"
    end=$(date +%s%N)
    duration=$(bc <<< "scale=6; ($end - $start)/1000000000")
    echo "$duration s"

    # Teste com ficheiro de palavras extenso
    echo -n "  - Pesquisa com ficheiro extenso: "
    start=$(date +%s%N)
    "$exe" $TEXTOS < "$PALAVRAS_EXTENSO" > "resultados_${exe_name}_extenso.txt"
    end=$(date +%s%N)
    duration=$(bc <<< "scale=6; ($end - $start)/1000000000")
    echo "$duration s"

    echo
done
