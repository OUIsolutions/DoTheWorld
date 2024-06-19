#include "src/one.c"

DtwNamespace dtw;

DtwResource *users;

void mostra_user(DtwResource *user){

    char *nome = dtw.resource.get_string_from_sub_resource(user, "nome");
    char *email = dtw.resource.get_string_from_sub_resource(user, "email");
    char *senha = dtw.resource.get_string_from_sub_resource(user, "senha");

    printf("\n\temail--> %s\n\tnome--> %s\n\tsenha--> %s", email, nome, senha);

}

bool criaUser(char *nome, char *email, char *senha){

    DtwResource *possivel_user = NULL;

    possivel_user = dtw.resource.find_by_primary_key_with_string(users, "email", email);

    if(possivel_user){
        return false;
    }

    possivel_user = dtw.resource.find_by_primary_key_with_string(users, "nome", nome);

    if(possivel_user){
        return false;
    }

    DtwResource *usuario_criado = dtw.resource.new_schema_insertion(users);

    dtw.resource.set_string_in_sub_resource(usuario_criado, "nome", nome);
    dtw.resource.set_string_in_sub_resource(usuario_criado, "email", email);
    dtw.resource.set_string_sha_in_sub_resource(usuario_criado, "senha", senha);

    return true;
}

int main(){
    dtw = newDtwNamespace();
    DtwResource *banco = dtw.resource.newResource("banco");
    DtwSchema *banco_schema = dtw.resource.newSchema(banco);
    DtwSchema *schama_users = dtw.schema.sub_schema(banco_schema, "usuarios");
    dtw.schema.add_primary_key(schama_users, "email");
    dtw.schema.add_primary_key(schama_users, "nome");
    users = dtw.resource.sub_resource(banco,"usuarios");

    bool deu_certo = criaUser("Samuel", "samu@gmail.com", "sa234566");

    if(dtw.resource.error(banco)) {
        printf("%s\n",dtw.resource.get_error_message(banco));
    }
    dtw.resource.commit(banco);

    if(deu_certo){
        printf("\n\tDeu certo, usuario criado.\n\n");
    } else{
        printf("Usuario, já existe ou problema de cod");
    }
}