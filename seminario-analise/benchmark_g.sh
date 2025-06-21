#!/bin/bash

# Nome do programa TSP
TSP_PROGRAM="./greedy"

# Número de execuções por grafo
RUNS_PER_GRAPH=5

# Arquivo para salvar os resultados
RESULT_FILE="resultados_tsp_greedy.txt"

# Limpa o arquivo de resultados anterior
echo "Resultados das execuções do TSP Greedy" > $RESULT_FILE
echo "=====================================" >> $RESULT_FILE
echo "" >> $RESULT_FILE

# Função para converter tempo para segundos
convert_to_seconds() {
    local time_str=$1
    # Remove o 'm' e 's' e divide em minutos e segundos
    local minutes=$(echo $time_str | awk -F'm' '{print $1}')
    local seconds=$(echo $time_str | awk -F'm' '{print $2}' | awk -F's' '{print $1}')
    # Calcula o tempo total em segundos
    echo "$minutes * 60 + $seconds" | bc -l
}

# Função para calcular a média dos tempos
calculate_average() {
    local times_file=$1
    local total=0
    local count=0
    
    while read -r line; do
        local time_in_seconds=$(convert_to_seconds "$line")
        total=$(echo "$total + $time_in_seconds" | bc -l)
        ((count++))
    done < "$times_file"
    
    if [ $count -ne 0 ]; then
        echo "scale=3; $total / $count" | bc -l
    else
        echo "0"
    fi
}

# Loop através de todos os grafos (1 a 6)
for graph_num in {1..10}; do
    echo "Executando testes para o Grafo $graph_num..."
    
    # Arquivos temporários
    TEMP_TIMES="temp_times_$graph_num.txt"
    TEMP_RESULTS="temp_results_$graph_num.txt"
    > $TEMP_TIMES
    > $TEMP_RESULTS
    
    # Executa o programa várias vezes
    for ((run=1; run<=$RUNS_PER_GRAPH; run++)); do
        echo "  Execução $run/$RUNS_PER_GRAPH..."
        
        # Executa o programa e captura tanto a saída quanto o tempo
        exec_output=$({ time $TSP_PROGRAM $graph_num ; } 2>&1)
        
        # Extrai e salva o tempo
        echo "$exec_output" | grep real | awk '{print $2}' | tr -d ' \t' >> $TEMP_TIMES
        
        # Extrai e salva os resultados (melhor caminho e distância)
        echo "$exec_output" | grep -E 'Melhor rota:|Distância total:' >> $TEMP_RESULTS
    done
    
    # Calcula a média dos tempos
    # average_time=$(calculate_average $TEMP_TIMES)
    
    # Pega um dos resultados (todos devem ser iguais)
    sample_result=$(head -n 2 $TEMP_RESULTS)
    
    # Salva os resultados no arquivo final
    echo "Grafo $graph_num:" >> $RESULT_FILE
    echo "$sample_result" >> $RESULT_FILE
    echo "Tempos individuais:" >> $RESULT_FILE
    cat $TEMP_TIMES >> $RESULT_FILE
    echo "" >> $RESULT_FILE
    # printf "Tempo médio: %.3f segundos\n" $average_time >> $RESULT_FILE
    echo "---------------------------------" >> $RESULT_FILE
    echo "" >> $RESULT_FILE
    
    # Remove os arquivos temporários
    rm $TEMP_TIMES $TEMP_RESULTS
done

echo "Testes concluídos! Resultados salvos em $RESULT_FILE"
cat $RESULT_FILE
