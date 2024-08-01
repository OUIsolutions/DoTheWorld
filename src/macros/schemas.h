
#define DtwSchemaRebase self->root_props->schema_unsafe =old;
#define DtwSchemaUnsafe(scope){\
    bool old = self->root_props->schema_unsafe;\
    self->root_props->schema_unsafe = true;\
    scope;\
    DtwSchemaRebase\
}
