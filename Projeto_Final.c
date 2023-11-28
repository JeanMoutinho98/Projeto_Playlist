#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYLIST_SIZE 100

typedef struct {
    char titulo[50];
    char artista[50];
    int favoritada;
} Musica;

typedef struct {
    Musica musicas[MAX_PLAYLIST_SIZE];
    int tamanho;
} Playlist;

void inserirMusica(Playlist *playlist) {
    if (playlist->tamanho < MAX_PLAYLIST_SIZE) {
        Musica novaMusica;
        printf("Digite o título da música: ");
        scanf(" %[^\n]s", novaMusica.titulo);
        printf("Digite o artista da música: ");
        scanf(" %[^\n]s", novaMusica.artista);
        novaMusica.favoritada = 0; // Inicialmente não favoritada

        playlist->musicas[playlist->tamanho] = novaMusica;
        playlist->tamanho++;

        printf("Música cadastrada com sucesso!\n");
    } else {
        printf("Playlist cheia. Não é possível adicionar mais músicas.\n");
    }
}

void mostrarMusicas(Playlist *playlist) {
    printf("Músicas na playlist:\n");
    for (int i = 0; i < playlist->tamanho; i++) {
        printf("%d. %s - %s", i + 1, playlist->musicas[i].artista, playlist->musicas[i].titulo);
        if (playlist->musicas[i].favoritada) {
            printf(" (Favoritada)");
        }
        printf("\n");
    }
}

void buscarMusica(Playlist *playlist) {
    char busca[50];
    printf("Digite o título ou artista da música a ser buscada: ");
    scanf(" %[^\n]s", busca);

    printf("Resultados da busca:\n");
    for (int i = 0; i < playlist->tamanho; i++) {
        if (strstr(playlist->musicas[i].titulo, busca) != NULL ||
            strstr(playlist->musicas[i].artista, busca) != NULL) {
            printf("%d. %s - %s\n", i + 1, playlist->musicas[i].artista, playlist->musicas[i].titulo);
        }
    }
}

void editarMusica(Playlist *playlist) {
    int indice;
    printf("Digite o número da música que deseja editar: ");
    scanf("%d", &indice);

    if (indice > 0 && indice <= playlist->tamanho) {
        Musica *musica = &playlist->musicas[indice - 1];

        printf("Digite o novo título da música: ");
        scanf(" %[^\n]s", musica->titulo);
        printf("Digite o novo artista da música: ");
        scanf(" %[^\n]s", musica->artista);

        printf("Informações da música editadas com sucesso!\n");
    } else {
        printf("Número de música inválido.\n");
    }
}

void removerMusica(Playlist *playlist) {
    int indice;
    printf("Digite o número da música que deseja remover: ");
    scanf("%d", &indice);

    if (indice > 0 && indice <= playlist->tamanho) {
        for (int i = indice - 1; i < playlist->tamanho - 1; i++) {
            playlist->musicas[i] = playlist->musicas[i + 1];
        }
        playlist->tamanho--;

        printf("Música removida com sucesso!\n");
    } else {
        printf("Número de música inválido.\n");
    }
}

void favoritarMusica(Playlist *playlist) {
    int indice;
    printf("Digite o número da música que deseja favoritar/desfavoritar: ");
    scanf("%d", &indice);

    if (indice > 0 && indice <= playlist->tamanho) {
        Musica *musica = &playlist->musicas[indice - 1];
        musica->favoritada = !musica->favoritada; // Inverte o status de favoritação

        if (musica->favoritada) {
            printf("Música favoritada com sucesso!\n");
        } else {
            printf("Música desfavoritada com sucesso!\n");
        }
    } else {
        printf("Número de música inválido.\n");
    }
}

void salvarPlaylist(Playlist *playlist) {
    FILE *arquivo = fopen("playlist.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < playlist->tamanho; i++) {
        fprintf(arquivo, "%s;%s;%d\n", playlist->musicas[i].titulo, playlist->musicas[i].artista,
                playlist->musicas[i].favoritada);
    }

    fclose(arquivo);
    printf("Playlist salva em playlist.txt\n");
}

int main() {
    Playlist playlist;
    playlist.tamanho = 0;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova música\n");
        printf("2. Mostrar músicas cadastradas\n");
        printf("3. Buscar por uma música\n");
        printf("4. Editar informações de uma música\n");
        printf("5. Remover música\n");
        printf("6. Favoritar música\n");
        printf("7. Salvar playlist em um arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirMusica(&playlist);
                break;
            case 2:
                mostrarMusicas(&playlist);
                break;
            case 3:
                buscarMusica(&playlist);
                break;
            case 4:
                editarMusica(&playlist);
                break;
            case 5:
                removerMusica(&playlist);
                break;
            case 6:
                favoritarMusica(&playlist);
                break;
            case 7:
                salvarPlaylist(&playlist);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}