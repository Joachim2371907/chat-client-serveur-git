# chat-client-serveur-git
# Mini Chat Interactif en C sous Linux

## Description

Ce projet est un mini système de chat interactif développé en langage C sous Linux.

Le système repose sur les mécanismes de communication inter-processus (IPC) avec les FIFO (Named Pipes).  
Il permet à plusieurs clients de communiquer avec un serveur en temps réel directement depuis le terminal Linux.

Le projet intègre également :
- l’authentification utilisateur,
- les threads POSIX,
- la communication bidirectionnelle,
- et un système simple de journalisation des messages.

---

# Fonctionnalités

- Authentification des utilisateurs via `users.txt`
- Communication temps réel Client ↔ Serveur
- Gestion multi-clients
- Utilisation des FIFO (Named Pipes)
- Gestion concurrente avec `pthread`
- Journalisation des messages
- Script Bash pour compilation et exécution automatique

---

# Technologies utilisées

- Langage C
- Linux
- FIFO / Named Pipes
- Threads POSIX (`pthread`)
- Bash scripting
- IPC (Inter Process Communication)

---

# Structure du projet

```text
project/
│
├── serveur/
│   └── main.c
│
├── client/
│   └── main.c
│
├── users.txt
├── log.txt
├── run.sh
└── README.md
