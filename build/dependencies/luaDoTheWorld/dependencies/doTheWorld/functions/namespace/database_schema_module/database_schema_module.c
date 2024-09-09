
#include "../unique.definition_requirements.h"

DtwDatabaseSchemaModule newDtwDatabaseSchemaModule(){
    DtwDatabaseSchemaModule  self = {0};
    self.sub_schema = DtwDtatabaseSchema_new_subSchema;
    return  self;
}
