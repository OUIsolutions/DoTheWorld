import json 
import base64
with open("exemples.json") as f:
    data = json.load(f)

for d in data:

        full_name = d.get('full_name')
        name = d.get('name')
        if name != 'deer':
            continue
        full_name = full_name.replace(name, name +'generated')
        content  = d.get('content')
        #convert content from bas64 to bytes
        content = base64.b64decode(content)
        with open(full_name, 'wb') as f:
            f.write(content)