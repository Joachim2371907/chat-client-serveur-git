#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char message[200];

    char reponse[200];

    mkfifo("canal_client", 0666);

    mkfifo("canal_serveur", 0666);

    int fd_client;
    int fd_serveur;

    fd_client = open("canal_client", O_RDONLY | O_NONBLOCK);

    fd_serveur = open("canal_serveur", O_WRONLY);

    printf("====================================\n");
    printf(" SERVEUR CHAT INTERACTIF\n");
    printf("====================================\n");

    while(1)
    {
        // Reception message client
        if(read(fd_client, message, sizeof(message)) > 0)
        {
            printf("\nCLIENT : %s\n", message);

            // Reponse du serveur
            printf("Serveur : ");

            fgets(reponse, sizeof(reponse), stdin);

            // Envoi vers clients
            write(fd_serveur,
                  reponse,
                  sizeof(reponse));
        }

        sleep(1);
    }

    close(fd_client);

    close(fd_serveur);

    return 0;
}
