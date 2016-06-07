#include <stdio.h>
#include <stdlib.h>

#define VTSZ 1024

int vet[VTSZ];

int main()
{
	int i, j;
	char *fileName = "vet.bin";

	// Abrindo o arquivo, para escrita
	FILE *fp;
	if ( (fp=fopen(fileName, "w")) == NULL)
	{
		perror("fopen ");
		exit(1);
	}

	// Inicializando o vetor com numeros randomicos
	srand(time(NULL));
	for(i=0; i < VTSZ; i++)
	{
		vet[i] = rand() % 100;
	}

	// Escrevendo o conteudo do array no arquivo (obs.: o ponteiro do arquivo se desloca para o fim)
	fwrite(vet, sizeof(int), VTSZ, fp);

	// Retorna para a posicao inicial do arquivo
	fseek(fp, 0, SEEK_SET);
	fclose(fp);

	// Abrindo novamente o arquivo, agora para leitura e escrita
	if ( (fp=fopen(fileName, "r+")) == NULL)
	{
		perror("fopen ");
		exit(1);
	}
	
	// Bubble sort com os valores do arquivo
	int x, y;
	for (i = 0; i < (VTSZ - 1); i++)
	{
		for (j = 0; j < VTSZ - i - 1; j++)
		{
			//Le o primeiro valor
			fseek(fp, j*sizeof(int), SEEK_SET);
			fread(&x, sizeof(int), 1, fp);
			
			//Le o segundo valor
			fseek(fp, (j+1)*sizeof(int), SEEK_SET);
			fread(&y, sizeof(int), 1, fp);

			if(x > y)
			{
				// Faz swap dos valores
				fseek(fp, (j+1)*sizeof(int), SEEK_SET);
				fwrite(&x, sizeof(int), 1, fp);

				fseek(fp, j*sizeof(int), SEEK_SET);
				fwrite(&y, sizeof(int), 1, fp);
			}
		}
	}

	// Retorna para a posicao inicial do arquivo
	fseek(fp, 0, SEEK_SET);

	// Le todo o arquivo novamente e salva no vetor
	fread(vet, sizeof(int), VTSZ, fp);

	// Escreve o vetor no console
	for (i=0; i < VTSZ; i++)
	{
		printf("%d ", vet[i]);
	}

	fclose(fp);
}
