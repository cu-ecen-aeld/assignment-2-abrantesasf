#/bin/bash

# Obtém o número de argumentos passados para o writer.sh:
nargs=$#

# Verifica se há 2 argumentos obrigatórios:
if [ $nargs -ne 2 ]; then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# Nomes bonitos para o resto do script:
writefile="$1"
writestr="$2"

# Verifica se o 1º argumento é um caminho absoluto para um arquivo:
fchar=$(echo "$writefile" | cut -c1)

if [ "$fchar" != "/" ]; then
    echo "ERROR: '$writefile' is not an ABSOLUTE FULL PATH to a file."
    exit 1
elif [ -d "$writefile" ]; then
    echo "ERROR: '$writefile' is not an ABSOLUTE FULL PATH to a file."
    exit 1
fi

# Obtém o diretório de writefile e cria, se não existir:
dir=$(dirname "$writefile")
mkdir -p "$dir"

# Obtém o nome do arquivo de writefile:
file=$(basename "$writefile")

# Tenta (re)escrever o arquivo e retorna erro se não conseguir:
2>/dev/null echo "$writestr" > "$dir"/"$file"

if [ $? -ne 0 ]; then
    echo "ERROR: file could not be created."
    exit 1
fi

# Termina OK:
exit 0
