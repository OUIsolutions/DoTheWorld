
Manipulação de arquivos em C usando a doTheWorld,
nesse artigo você irá aprender a fazer manipulações de arquivos em
C de maneira fácil e intuitiva.


### Instalação:
a doTheWorld é uma lib single header, o que significa  que para instalar basta 
incluir o arquivo **doTheWord.h** presente no repositório:
(aproveita e da uma estrelinha pra nois lá kkkk)

https://github.com/OUIsolutions/DoTheWorld 

 dentro da sua pasta que esta trabalhando 

Se isso funcionar, significa que a lib esta rodando 
~~~c

#include "doTheWorld.h"

int main(){ 
    

}
~~~

### Leitura e escrita 

#### Leitura de Plain Text 
para ler arquivos em plain text , é muito simples, basta chamar a
função **dtw_load_string_file_content**

~~~c
#include "doTheWorld.h"

int main(){ 

  char *valor = dtw_load_string_file_content("test.txt");
  printf("%s\n",valor);
  free(valor);
}
~~~
### Leitura de blobs
para ler arquivos  não assci usando a lib você pode usar a função 
**dtw_load_binary_content**,  note que é nescessário passar um ponteiro int 
para armazenar o valor do binário, e o resultado do binário (não imprimível)
ficará armazenado na variável test (unsigned char)

~~~c
#include "doTheWorld.h"

int main(){ 
  int tamanho;
  unsigned char *valor = dtw_load_binary_content("my_image.jpg",&tamanho);
  printf("tamanho %d",tamanho);
  free(valor);
}
~~~
### Leitura de Arquivos indefinidos

Caso voce tenha arquivos que você não saiba exatamente que tipo de 
arquivo você está lidando você pode usar a função 
**dtw_load_any_content**
~~~c

#include "doTheWorld.h"

int main(){ 
  int tamanho;
  bool e_binario;
  unsigned char *valor = dtw_load_any_content("deer.jpg",&tamanho,&e_binario);
  printf("tamanho: %d\n",tamanho);
  printf("é binário: %s\n",e_binario? "Sim" : "Não" );
  if(e_binario == false){
    printf("Conteudo :%s",valor);
  }

  free(valor);
}
~~~

### Escrita de arquivos 

Para escrever arquivos não binários basta chamar a função 
**dtw_write_string_file_content**, não precisa se preocupar 
se o diretório existe ou não, a doTheWorld segue o modelo 
de diretório infinito (semelhante a s3), se a pasta não existir 
ela irá criar automaticamente 
~~~c
#include "doTheWorld.h"

int main(){ 
  
  dtw_write_string_file_content("teste.txt","meu conteudo");
}
~~~
#### Escrita binária 
também é possível fazer escrita binária através da doo the world 
porém você precisa informar o tamanho da escrita que quer gerar 


~~~c
include "doTheWorld.h"
int main(){ 
  char * conteudo = "meu conteudo";
  int tamanho = strlen(conteudo);
  dtw_write_any_content("teste.txt",conteudo,tamanho);
}
~~~

### Copiando qualquer coisa
como ja dito anteriormente a lib não diferencia pastas de arquivos, então 
para copiar algo, basta chamar a função **dtw_copy_any**

Copiando arquivos
~~~c
  #include "doTheWorld.h"

int main(){ 
  //copia arquivos
  bool consseguiu_arquivo = dtw_copy_any(
    "test.txt",
    "saida.json",
    DTW_NOT_MERGE
  );
  printf("resultado arquivo :%s\n",consseguiu_arquivo? "positivo":"negativo");

  //copia pasta
  bool consseguiu_pasta = dtw_copy_any(
    "output_folder",
    "saida",
    DTW_NOT_MERGE
  );
  printf("resultado pasta :%s\n",consseguiu_pasta? "positivo":"negativo");
}
~~~

