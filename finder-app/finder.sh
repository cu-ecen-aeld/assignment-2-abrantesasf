#/bin/bash

# Obtém o número de argumentos passados para o finder.sh:
nargs=$#

# Verifica se há 2 argumentos obrigatórios:
if [ $nargs -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

# Nomes bonitos para o resto do script:
filesdir=$1
searchstr=$2

# Verifica se o 1º argumento é um diretório:
if [ ! -d $filesdir ]; then
    echo "ERROR: directory '$filesdir' does not exist!"
    exit 1
fi

# Contagem de arquivos em "filesdir", incluindo subdiretórios. a contagem
# inclui todos os arquivos do tipo FILE, incluindo arquivos ocultos. Não inclui
# coisas como links simbólicos e outros arquivos especiais.
nfiles=$(find $filesdir -type f | wc -l)

# Contagem de arquivos em "filesdir", incluindo subdiretórios, que contém
# a string "searchstr". Essa contagem EXCLUI arquivos binários:
nmatches=$(grep -r -I $searchstr $filesdir | wc -l)

# Imprime resultados:
echo "The number of files are $nfiles and the number of matching lines are $nmatches"
