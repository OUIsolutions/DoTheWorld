
function Install_dependencies()
    local hasher = darwin.dtw.newHasher()
    hasher.digest_folder_by_content("dependencies")
    local TARGET_HASH = "9ad38a98c965e78ee37a76327af0b95ee5a1dce6cbe41968e2a3cbc7efefbf59"
    if hasher.get_value() == TARGET_HASH then
        return
    end
    local comands = {
        "mkdir -p dependencies",
        "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.c -o dependencies/cJSON.c",
        "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.h -o dependencies/cJSON.h",
        "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.c -o dependencies/sha-256.c  ",
        "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.h -o dependencies/sha-256.h  ",
        "curl -L https://github.com/OUIsolutions/CHashManipulator/releases/download/0.001/CHashManipulator.h -o dependencies/CHashManipulator.h ",
        "curl -L https://raw.githubusercontent.com/kokke/tiny-AES-c/refs/tags/v1.0.0/aes.c -o dependencies/aes.c",
        "curl -L https://raw.githubusercontent.com/kokke/tiny-AES-c/refs/tags/v1.0.0/aes.h -o dependencies/aes.h"
    }
    for _, command in ipairs(comands) do
        os.execute(command)
    end
    local new_hasher = darwin.dtw.newHasher()
    new_hasher.digest_folder_by_content("dependencies")
    print("new hasher is: ", new_hasher.get_value())
end
