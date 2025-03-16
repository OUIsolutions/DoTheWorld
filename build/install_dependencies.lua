
function Install_dependencies()
    local hasher = dtw.newHasher()
    hasher.digest_folder_by_content("dependencies")
    local TARGET_HASH = "bf1f7e84f00fbcee177987c0f8247286ae45de2c04e64cbc1cc997fbeb6a12f6"
    if hasher.get_value() == TARGET_HASH then
        return
    end
    local comands = {
        "mkdir -p dependencies",
        "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.c -o dependencies/cJSON.c",
        "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.h -o dependencies/cJSON.h",
        "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.c -o dependencies/sha-256.c  ",
        "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.h -o dependencies/sha-256.h  ",
        "curl -L https://github.com/OUIsolutions/CHashManipulator/releases/download/0.001/CHashManipulator.h -o dependencies/CHashManipulator.h "
    }
    for _, command in ipairs(comands) do
        os.execute(command)
    end
    local new_hasher = dtw.newHasher()
    new_hasher.digest_folder_by_content("dependencies")
    print("new hasher is: ", new_hasher.get_value())
end
