#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

char nom[50];

// ==========================
// THREAD RECEPTION
// ==========================
void *recevoir()
{
    char message[200];

    int fd;

    // Ouverture canal serveur
    fd = open("canal_serveur", O_RDONLY);

    while(1)
    {
        // Lecture message serveur
        if(read(fd, message, sizeof(message)) > 0)
        {
            printf("\nSERVEUR : %s\n", message);

            printf("%s : ", nom);

            fflush(stdout);
        }
    }

    close(fd);

    pthread_exit(NULL);
}

int main()
{
    // ==========================
    // VARIABLES AUTHENTIFICATION
    // ==========================

    char password[50];

    char ligne[100];

    char userfile[50];

    char passfile[50];

    int trouve = 0;

    FILE *f;

    printf("====================================\n");
    printf(" AUTHENTIFICATION CLIENT\n");
    printf("====================================\n");

    // Saisie nom
    printf("Nom : ");

    fgets(nom, sizeof(nom), stdin);

    nom[strcspn(nom, "\n")] = 0;

    // Saisie mot de passe
    printf("Mot de passe : ");

    fgets(password, sizeof(password), stdin);

    password[strcspn(password, "\n")] = 0;

    // Ouverture fichier users
    f = fopen("user.txt", "r");

    if(f == NULL)
    {
        printf("Erreur users.txt\n");

        return 1;
    }

    // Lecture ligne par ligne
    while(fgets(ligne, sizeof(ligne), f))
    {
        sscanf(ligne,
               "%[^:]:%s",
               userfile,
               passfile);

        // Verification login/password
        if(strcmp(nom, userfile) == 0 &&
           strcmp(password, passfile) == 0)
        {
            trouve = 1;

            break;
        }
    }

    fclose(f);

    // Verification acces
    if(trouve == 0)
    {
        printf("\nAcces refuse\n");

        return 1;
    }

    printf("\nConnexion reussie\n");

    // ==========================
    // PARTIE CHAT
    // ==========================

    char texte[100];

    char message[200];

    int fd;

    pthread_t thread_reception;

    // Creation thread reception
    pthread_create(&thread_reception,
                   NULL,
                   recevoir,
                   NULL);

    while(1)
    {
        printf("%s : ", nom);

        fgets(texte, sizeof(texte), stdin);

        // Construction message
        sprintf(message,
                "%s : %s",
                nom,
                texte);

        // Ouverture canal client
        fd = open("canal_client", O_WRONLY);

        // Envoi message serveur
        write(fd,
              message,
              sizeof(message));

        close(fd);

        // Deconnexion
        if(strncmp(texte, "stop", 4) == 0)
        {
            printf("\nDeconnexion...\n");

            break;
        }
    }

    pthread_join(thread_reception, NULL);

    return 0;
}
