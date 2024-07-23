
#define DTW_DEBUG_TIME
#include "src/one.c"
DtwNamespace dtw;
DtwRandonizer *randonizer;
void cria_x_usuarios(DtwResource *usuarios,int tamanho) {

    for(int i = 0; i < tamanho; i++) {
        DtwResource  *novo_usuario =  dtw.resource.sub_resource(usuarios,"%d",i);
        char nome_usuario[50]  = {0};
        sprintf(nome_usuario,"usuario%d",i);
        char email[50] = {0};
        sprintf(email,"%d@gmail.com",i);
        dtw.resource.set_string_in_sub_resource(novo_usuario,"nome",nome_usuario);
        dtw.resource.set_string_in_sub_resource(novo_usuario,"email",email);
        int idade = dtw.randonizer.generate_num(randonizer,100);
        dtw.resource.set_long_in_sub_resource(novo_usuario,"idade",idade);

    }
}
int main(){
    dtw = newDtwNamespace();
    randonizer = dtw.randonizer.newRandonizer();

    dtw.remove_any("usuarios");
    DtwResource *usuarios = dtw.resource.newResource("usuarios");
    cria_x_usuarios(usuarios,100);
    dtw.resource.commit(usuarios);
    dtw.resource.free(usuarios);
    dtw.randonizer.free(randonizer);


    //dtw.resource.commit(teste);

}