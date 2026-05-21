#!/bin/bash

echo "====================================="
echo " COMPILATION DES PROGRAMMES "
echo "====================================="

# Compilation du serveur
gcc serveur/main.c -o serveur/serveur

# Compilation du client avec pthread
gcc client/main.c -o client/client -lpthread

echo ""
echo "Compilation terminee"
echo ""

echo "====================================="
echo " LANCEMENT DU CHAT "
echo "====================================="

# Lancement du serveur
gnome-terminal --title="SERVEUR" -- bash -c "./serveur/serveur; exec bash"

# Attente de 2 secondes
sleep 2

# Lancement de plusieurs clients
gnome-terminal --title="CLIENT" -- bash -c "./client/client; exec bash"

