
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
### Obtendo Tipo de Entidade 
Podemos obter o tipo de entidade através da função **dtw_entity_type**

~~~c
#include "doTheWorld.h"

int main(){ 
  
  int tipo = dtw_entity_type("exemples");

  if(tipo == DTW_NOT_FOUND){
      printf("Não existe\n");
  }

  if(tipo == DTW_FOLDER_TYPE){
      printf("é uma pasta\n");
  }
  
  if(tipo == DTW_FILE_TYPE){
      printf("é um arquivo\n");
  }

}
~~~

### Fazendo uma conversão Binária para  Base64
Caso precise transformar um blob em string pode facilmente fazer 
uma conversão para base64
~~~c 
#include "doTheWorld.h"

int main(){ 
  
  int tamanho;
  unsigned char * conteudo = dtw_load_binary_content(
    "output_folder/deer.jpg",
    &tamanho
  );
  const char *em_base64 = dtw_base64_encode(conteudo,tamanho);
  printf("%s",em_base64);
}

~~~
## Reconversão de Base64 para blob 



### Copiando qualquer coisa
como ja dito anteriormente a lib não diferencia pastas de arquivos, então 
para copiar algo, basta chamar a função **dtw_copy_any**

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

### Movendo qualquer coisa 
Da mesma forma também é possível mover qualquer coisa em C usando a função
**dtw_move_any**
~~~c
#include "doTheWorld.h"

int main(){ 
  //copia arquivos
  bool consseguiu_arquivo = dtw_move_any(
      "README.md",
      "saida.md",
      DTW_NOT_MERGE
  );
  printf("resultado arquivo :%s\n",consseguiu_arquivo? "positivo":"negativo");

    //copia arquivos
  bool consseguiu_pasta = dtw_move_any(
      "output_folder",
      "saida",
      DTW_NOT_MERGE
  );
  printf("resultado pasta :%s\n",consseguiu_pasta? "positivo":"negativo");
}
~~~

### Removendo arquivos

Da mesma forma é plenamente possível remover arquivos usando a do TheWorld
através da função **dtw_remove_any**

~~~c

#include "doTheWorld.h"

int main(){ 
  //removendo arquivos
  bool consseguiu_arquivo = dtw_remove_any(
    "teste.txt"
  );
  printf("resultado arquivo :%s\n",consseguiu_arquivo? "positivo":"negativo");

  //removendo pastas
  bool consseguiu_pasta = dtw_remove_any(
    "saida4"
  );
  printf("resultado pasta :%s\n",consseguiu_pasta? "positivo":"negativo");
}
~~~

### Listagem 

### Listagem de arquivos 
Esse exemplo irá lista todos os arquivos de uma pasta de maneira não recursiva
ele irá retornar um objeto da classe **DtwStringArray** aonde podemos iterar com for
~~~c
#include "doTheWorld.h"

int main(){ 
  //copia arquivos
  bool concatenar_path = true;
  DtwStringArray *conteudo = dtw_list_files("exemple_folder",concatenar_path);
  
  for(int i = 0; i < conteudo->size; i++){
    printf("%s\n",conteudo->strings[i]);
  }
  conteudo->free(conteudo);

}
~~~

### Listagem de Pasta

Podemos também listar pastas dentro determinada pasta através da função 
**dtw_list_dirs**

~~~c
#include "doTheWorld.h"

int main(){ 
  //copia arquivos
  bool concatenar_path = true;
  DtwStringArray *conteudo = dtw_list_dirs("exemples",concatenar_path);
  
  for(int i = 0; i < conteudo->size; i++){
    printf("%s\n",conteudo->strings[i]);
  }
  conteudo->free(conteudo);

}
~~~

### Listando tudo 

Podemos listar qualquer tipo de arquivo através da função **dtw_list_all**

~~~c
#include "doTheWorld.h"

int main(){ 
  //copia arquivos
  bool concatenar_path = true;
  DtwStringArray *conteudo = dtw_list_all("exemples",concatenar_path);
  
  for(int i = 0; i < conteudo->size; i++){
    printf("%s\n",conteudo->strings[i]);
  }
  conteudo->free(conteudo);

}
~~~

### Listagem Recursiva 

Adicionando o sulfixo **recursively** em qualquer uma das 3 listagens anteriores
a listagem ocorrerá de maneira recursiva (iterando pastas sobre pastas)

~~~c
#include "doTheWorld.h"

int main(){ 
  //copia arquivos
  bool concatenar_path = true;
  DtwStringArray *conteudo = dtw_list_all_recursively("exemples",concatenar_path);
  
  for(int i = 0; i < conteudo->size; i++){
    printf("%s\n",conteudo->strings[i]);
  }
  conteudo->free(conteudo);

}
~~~