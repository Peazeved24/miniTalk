#!/bin/bash
# mega_test_bonus.sh
# PID do server como argumento
SERVER_PID=$1

# Strings para testar
STR1="Ola, este é um teste gigante! $(yes | head -n 100 | tr -d '\n')"
STR2="Outra mensagem enorme, vamos ver se o server aguenta! $(yes | head -n 100 | tr -d '\n')"

echo "Enviando mensagens rápidas para o server $SERVER_PID..."

# Enviar a primeira string 5 vezes rapidinho
for i in {1..5}; do
    ./clientbonus $SERVER_PID "$STR1"
done

# Enviar a segunda string 5 vezes rapidinho
for i in {1..5}; do
    ./clientbonus $SERVER_PID "$STR2"
done

echo "Test completo!"

