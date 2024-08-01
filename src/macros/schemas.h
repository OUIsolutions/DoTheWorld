#define DtwResourceSchemaUnsafe(scope){\
    bool old = self->root_props->schema_unsafe;\
    self->root_props->schema_unsafe = true;\
    scope;\
    self->root_props->schema_unsafe =old;\
}
#define DtwResourceSchemaSafe(scope){\
    bool old = self->root_props->schema_unsafe;\
    self->root_props->schema_unsafe = false;\
    scope;\
    self->root_props->schema_unsafe =old;\
}
